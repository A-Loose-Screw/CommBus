#ifndef COMMBUS_NETWORK
#define COMMBUS_NETWORK

#include <string>
#include <functional>
#include <chrono>

#include "nngpp/nngpp.h"
#include "CommBusCommon.h"
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

    Network(Type type, std::string address = COMMBUS_LOCAL_ADDR);

    /**
     * @brief Start the service
     * 
     * @param retryLoop // keep retrying if connection does not succeed (loops and halts program)
     * @return int -1 for fail. 0 for success
     */
    int start(bool retryLoop = false);

    /**
     * @brief Update the sender, (checks entries for changes and sends the changes)
     * 
     */
    void senderUpdate(bool noBlock = false);

    /**
     * @brief Checks network for sent changes, and changes local network model when prompted
     * 
     */
    void receiverUpdate(bool noBlock = false);

    /**
     * @brief Return data model
     * 
     * @return std::shared_ptr<Models::Model> 
     */
    std::shared_ptr<Models::Model> getModel();

   private:
    Type _type = { Type::NODE };
    bool _connected = false;
    std::string _addr;
    nng::socket _socket;
    std::shared_ptr<Models::Model> _model = std::make_shared<Models::Model>();
  };
}

#endif