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
  // modbus_set_debug(mb, TRUE);
  modbus_set_slave(mb, 1);
  while (modbus_connect(mb) == -1) {
    fprintf(stderr, "Connection failed: %s\n", modbus_strerror(errno));
    modbus_free(mb);
    return;
  }

  
  modbus_set_float_abcd(10.3f, tab_reg);
  modbus_write_registers(mb, 2, 2, tab_reg);
  

  modbus_close(mb);
  modbus_free(mb);
  std::cout << "Client Sender Complete" << std::endl;
}

int main() {
  std::cout << "Starting CommBus test..." << std::endl;

  CommBus::Server server;
  server.start();

  std::this_thread::sleep_for(std::chrono::seconds(5));
  client_sender();
  server.stop();
  // while (true);
  std::cout << "Program End" << std::endl;
  return 0;
}