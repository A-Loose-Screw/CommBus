#ifndef COMMBUS_SERVER_H
#define COMMBUS_SERVER_H

#include <thread>
#include <vector>
#include "modbus/modbus.h"

namespace CommBus {
  
  class Server {
   public:
    struct ModbusMap {
      int n_bits = MODBUS_MAX_READ_BITS, 
          n_input_bits = 0, 
          n_registers = MODBUS_MAX_READ_REGISTERS, 
          n_input_registers = 0;
      int n_clients = 10;
    };

    /**
     * @brief Create Server object for CommBus
     * 
     * @param ip 
     * @param port 
     */
    Server(const char *ip = "0.0.0.0", int port = 1502);
    ~Server();

    /**
     * @brief Starts the server on a separate thread
     * 
     */
    void start();

    /**
     * @brief Stops all server  threads and closes sockets
     * 
     */
    void stop();

    /**
     * @brief Set custom modbus map for server
     * 
     * @param map 
     */
    void setMap(ModbusMap map) {
      _map = map;
    }

   private:
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