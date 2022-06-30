#ifndef COMMBUS_NETWORK
#define COMMBUS_NETWORK

#include <string>
#include <functional>
#include <chrono>

#include "CommBusCommon.h"
#include "nngpp/nngpp.h"
#include "Model/Model.h"

// struct nng::socket;

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

    Network(Type type, std::string address = COMMBUS_LOCAL_ADDR);

    /**
     * @brief Start the service
     * 
     */
    void start();

    /**
     * @brief Update the sender, (checks entries for changes and sends the changes)
     * 
     */
    void senderUpdate();

    /**
     * @brief Checks network for sent changes, and changes local network model when prompted
     * 
     */
    void receiverUpdate();

    /**
     * @brief Return data model
     * 
     * @return std::shared_ptr<Models::Model> 
     */
    std::shared_ptr<Models::Model> getModel();

   private:
    Type _type = { Type::NODE };
    std::string _addr;
    nng::socket _socket;
    std::shared_ptr<Models::Model> _model = std::make_shared<Models::Model>();
  };
}

#endif