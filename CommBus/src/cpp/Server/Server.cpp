#include <stdio.h>
#include <iostream>
#include "Server/Server.h"

using namespace CommBus;

Server::Server(const char *ip, int port) {
  _mb = modbus_new_tcp(ip, port);
  _mbMap = modbus_mapping_new(_map.n_bits, _map.n_input_bits, _map.n_registers, _map.n_input_registers);
  _n_clients = _map.n_clients;

  if (_mbMap == NULL) {
    perror("Failed to allocate mapping");
  }
}

Server::~Server() {
  if (_stoppable) {
    stop();
  }
  modbus_mapping_free(_mbMap);
  modbus_close(_mb);
  modbus_free(_mb);
  std::cout << "CommBus Server Deconstructed" << std::endl;
}

void Server::client_handler(int cli_sock) {
  std::cout << "Client Connection Created: " << cli_sock  << std::endl;
  while (_async_run) {
    uint8_t query[MODBUS_TCP_MAX_ADU_LENGTH];
    uint16_t tab_reg[2];
    int rc;

    rc = modbus_receive(_mb, query);
    if (rc > 0) {
      // Reply, (rc being the query size)
      modbus_reply(_mb, query, rc, _mbMap);

    } else if (rc == -1) {
      // Connection closed
      break;
    }
  }

  std::cout << "Client Connection lost" << std::endl;
  if (cli_sock != -1) {
    close(cli_sock);
  }
}

void Server::loop() {
  _server_sock = modbus_tcp_listen(_mb, _n_clients);

  if (_server_sock == -1) {
    fprintf(stderr, "Unable to listen TCP connection\n");
    modbus_free(_mb);
    return;
  }

  std::cout << "Server Listening..." << std::endl;

  while (_async_run) {
    sleep(1);
    int cli_sock = modbus_tcp_accept(_mb, &_server_sock);
    if (cli_sock < 0) {
      if (errno != EWOULDBLOCK) {
        perror("Error accepting client");
      }
      continue;
    }

    auto cli_t = std::thread([this, cli_sock]() {
      client_handler(cli_sock);
    });

    _client_handler_threads.push_back(std::move(cli_t));
  }

  std::cout << " -- Closing Threads -- " << std::endl;

  for (auto &client_handler : _client_handler_threads) {
    client_handler.join();
  }

  if (_server_sock != -1) {
    close(_server_sock);
    std::cout << "Closed server sock" << std::endl;
  }
}

void Server::start() {
  _stoppable = true;
  _async_run = true;
  std::cout << "Starting Server" << std::endl;
  loop_t = std::thread(&Server::loop, this);
}

void Server::stop() {
  _async_run = false;
  loop_t.join();
  _stoppable = false;
}