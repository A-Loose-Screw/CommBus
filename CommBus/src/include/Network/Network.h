// #ifndef COMMBUS_SERVER_H
// #define COMMBUS_SERVER_H

// #include "CommBusCommon.h"

// #include "nng/nng.h"
// #include "nngpp/protocol/pub0.h"
// #include "Model/Model.h"

// /**
//  * @brief Defined protocol
//  * 
//  * Client:
//  * Message consists of table access -> entry access -> (set or get)
//  * 
//  * Server:
//  * Server listens for type of model access.
//  */

// namespace CommBus {
//   class Server {
//    public:
//     Server() {
//       _socket = nng::pub::open();
//     }

//     void start(const char *addr = COMMBUS_LOCAL_ADDR) {
//       _socket.listen(addr);
//     }

//     std::shared_ptr<Models::Model> getModel() {
//       return _model;
//     }

//     void update() {
      
//     }

//    private:
//     nng::socket _socket;
//     std::shared_ptr<Models::Model> _model = std::make_shared<Models::Model>();
//   };
// }

// #endif