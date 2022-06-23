#ifndef COMMBUS_SERVER_H
#define COMMBUS_SERVER_H

#include <thread>
#include <vector>
#include "modbus/modbus.h"

namespace CommBus {
  
  class Server {
   public:
    struct ModbusMap {
      int n_bits = 500, n_input_bits = 500, n_registers = 500, n_input_registers = 500;
      int n_clients = 247;
    };

    Server(const char *ip = "0.0.0.0", int port = 1502);
    ~Server();

    void start();
    void stop();

    void setMap(ModbusMap map) {
      _map = map;
    }

   private:
    int _n_clients;
    bool _async_run = false;
    bool _stoppable = false;
    void loop();
    std::thread loop_t;
    void client_handler(int cli_sock);
    std::vector<std::thread> _client_handler_threads;
    ModbusMap _map;
    modbus_t *_mb;
    modbus_mapping_t *_mbMap;
    int _server_sock = -1;
  };
}

#endif