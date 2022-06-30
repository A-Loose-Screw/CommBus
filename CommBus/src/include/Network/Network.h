#ifndef COMMBUS_NETWORK
#define COMMBUS_NETWORK

#include <string>
#include <functional>
#include <chrono>

#include "CommBusCommon.h"
#include "nngpp/nngpp.h"
#include "nngpp/protocol/bus0.h"
#include "Model/Model.h"

namespace CommBus {
  class Network {
   public:

    /**
     * @brief Type of network, server/host or node/client
     * 
     */
    enum class Type {
      SERVER = 0,
      NODE
    };

    Network(Type type, std::string address = COMMBUS_LOCAL_ADDR) {
      _type = type;
      _addr = address;

      _socket = nng::bus::open();
    }

    void start() {
      switch (_type) {
        case Type::SERVER: _socket.listen(_addr.c_str()); break;
        case Type::NODE: _socket.dial(_addr.c_str()); break;
      }
    }

    void update() {
      std::vector<std::shared_ptr<Models::Entry>> changedEntries;

      for (auto &table : getModel()->getTables()) {
        for (auto &entry : table->getEntries()) {
          // check if it's been updated
          if (entry->_hasChanged) {
            changedEntries.push_back(entry);
            entry->_hasChanged = false;
          }
        }
      }

      // @TODO send the changed entries (with the table name)
    }

    /**
     * @brief Return data model
     * 
     * @return std::shared_ptr<Models::Model> 
     */
    std::shared_ptr<Models::Model> getModel() {
      return _model;
    }

   private:
    Type _type = { Type::NODE };
    std::string _addr;
    nng::socket _socket;
    std::shared_ptr<Models::Model> _model = std::make_shared<Models::Model>();
  };
}

#endif