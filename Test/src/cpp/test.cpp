#include <iostream>
#include <thread>
#include <chrono>
#include "CommBus.h"

#ifdef COMMBUS_PLATFORM_UNIX
#include <unistd.h>
#endif

void client_sender() {
  std::cout << "Client Sender Starting" << std::endl;
  modbus_t *mb;
  uint16_t tab_reg[2];


  mb = modbus_new_tcp("127.0.0.1", 1502);
  // modbus_set_debug(mb, true);

  while (modbus_connect(mb) == -1) {
    fprintf(stderr, "Connection failed: %s\n", modbus_strerror(errno));
  }

  int count = 0;

  while (true) {
    modbus_set_float_abcd(10.3f, tab_reg);
    if (modbus_write_registers(mb, 2, 2, tab_reg) == -1) {
      // std::cout << "Reconnecting" << std::endl;
      fprintf(stderr, "Test side: Connection failed: %s\n", modbus_strerror(errno));
      modbus_close(mb);
      modbus_flush(mb);
      modbus_free(mb);
      mb = modbus_new_tcp("127.0.0.1", 1502);
      std::this_thread::sleep_for(std::chrono::seconds(2));
      if (modbus_connect(mb) == -1) {
        fprintf(stderr, "Test side: Reconnect failed: %s\n", modbus_strerror(errno));
      }
    } else {
      std::cout << "Write data" << std::endl;
    }

    if (count > 5) {
      std::cout << "Thread wait triggered" << std::endl;
      std::this_thread::sleep_for(std::chrono::seconds(5));
      count = 0;
    }

    count++;
  }
  

  modbus_close(mb);
  modbus_free(mb);
  std::cout << "Client Sender Complete" << std::endl;
}

int main() {
  std::cout << "Starting CommBus test..." << std::endl;

  CommBus::Server server;
  server.start();

  std::this_thread::sleep_for(std::chrono::seconds(5));
  CommBus::Client client("127.0.0.1");
  client.start();

  // client_sender();
  
  std::this_thread::sleep_for(std::chrono::seconds(5));
  #ifndef COMMBUS_TEST
  while (true);
  #endif

  std::cout << "Program End" << std::endl;
  return 0;
}