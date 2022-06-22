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
  stop();
  modbus_mapping_free(_mbMap);
  modbus_close(_mb);
  modbus_free(_mb);
}

void Server::client_handler(int cli_sock) {
  std::cout << "Client Connection Created: " << cli_sock  << std::endl;
  while (_async_run) {
    uint8_t query[MODBUS_TCP_MAX_ADU_LENGTH];
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
  int server_sock = -1;
  server_sock = modbus_tcp_listen(_mb, _n_clients);

  if (server_sock == -1) {
    fprintf(stderr, "Unable to listen TCP connection\n");
    modbus_free(_mb);
    return;
  }

  std::cout << "Server Listening..." << std::endl;

  while (_async_run) {
    int cli_sock = modbus_tcp_accept(_mb, &server_sock);
    if (cli_sock < 0) {
      perror("Error accepting client");
      continue;
    }

    std::cout << "Accepted Client: " << cli_sock << std::endl;
    _client_handler_threads.emplace_back([&](){&Server::client_handler, cli_sock, this;});
  }

  for (auto &client_handler : _client_handler_threads) {
    client_handler.join();
  }
}

void Server::start() {
  _async_run = true;
  std::cout << "Starting Server" << std::endl;
  loop_t = std::thread(&Server::loop, this);
}

void Server::stop() {
  _async_run = false;
  loop_t.join();
}