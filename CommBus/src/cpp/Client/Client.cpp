#include <iostream>

#include "Client/Client.h"

using namespace CommBus;

Client::Client(const char *ip, int port) {
  _ip = ip;
  _port = port;
  std::cout << ip << std::endl;
  // _mb = modbus_new_tcp(_ip, _port);
  // modbus_set_slave(_mb, slave_id);
}

Client::~Client() {
  if (_stoppable) {
    stop();
  }

  modbus_close(_mb);
  modbus_free(_mb);
  std::cout << "Client Deconstructed" << std::endl;
}

int Client::connect() {
  if (_connected) {
    modbus_close(_mb);
    modbus_flush(_mb);
    modbus_free(_mb);
  }
  _mb = modbus_new_tcp(_ip, _port);
  std::this_thread::sleep_for(std::chrono::seconds(2));
  return modbus_connect(_mb);
}

void Client::loop() {
  if (connect() == -1) {
    fprintf(stderr, "Connection failed: %s\n", modbus_strerror(errno));
  }
  _connected = true;

  while (_async_run) {
    /**
     * @brief Do main communication to and from server/host
     * 
     */
    std::this_thread::sleep_for(std::chrono::seconds(1));
    float value = 0.2f;
    uint16_t reg[2];
    modbus_set_float_abcd(value, reg);
    if (modbus_write_registers(_mb, 1, 2, reg) == -1) {
      std::cout << "Reconnecting" << std::endl;
      connect();
    } else {
      std::cout << "Write data" << std::endl;
    }
  }

  _connected = false;
  std::cout << "Client Complete" << std::endl;
}

void Client::start() {
  _stoppable = true;
  _async_run = true;
  std::cout << "Starting client handle" << std::endl;
  loop_t = std::thread(&Client::loop, this);
}

void Client::stop() {
  _async_run = false;
  if (loop_t.joinable()) {
    loop_t.join();
  }
  _stoppable = false;
}