#ifndef COMMBUS_CLIENT_H
#define COMMBUS_CLIENT_H

#include <thread>
#include "modbus/modbus.h"

namespace CommBus {
  class Client {
   public:
    Client(const char *ip, int port = 1502);
    ~Client();

    void start();
    void stop();

   private:
    const char *_ip;
    int _port;
    bool _async_run = false;
    bool _stoppable = false;
    bool _connected = false;
    int connect();
    void loop();
    std::thread loop_t;
    modbus_t *_mb;
  };
}

#endif