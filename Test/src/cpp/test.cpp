#include <iostream>
#include <thread>
#include <string>
#include <chrono>

// #include "nng/compat/nanomsg/nn.h"
#include "nng/compat/nanomsg/bus.h"
#include "CommBus.h"

// #define SOCKET_BUS_ADDR_INPROC "inproc://bus"
// #define SOCKET_BUS_LOCAL_ADDR "tcp://0.0.0.0:1905"
#define SOCKET_BUS_SERVER_ADDR COMMBUS_LOCAL_ADDR

// #define CLIENT_RECV_IMPL(x,y) try {y=x;} catch(const std::exception& e) {std::cerr << e.what() << '\n';}
// #define CLIENT_RECV(x)  try {x;} catch(const std::exception& e) {std::cerr << e.what() << '\n';}

int main() {
  // auto bus1 = nng::bus::open();
  // auto bus2 = nng::bus::open();
  // auto bus3 = nng::bus::open();

  // bus1.listen(SOCKET_BUS_LOCAL_ADDR);
  // bus2.dial(SOCKET_BUS_ADDR);
  // bus3.dial(SOCKET_BUS_ADDR);

  // bus1.send("test");

  // std::cout << "Data: " << bus2.recv().data<char>() << std::endl;
  // std::cout << "Data: " << bus3.recv().data<char>() << std::endl;


  /**
   * @brief pub sub
   * 
   */
  // auto server = nng::pub::open();
  // // server.dial(SOCKET_BUS_ADDR);
  // server.listen(SOCKET_BUS_SERVER_ADDR);

  // auto client1 = nng::sub::open();
  // auto client2 = nng::sub::open();
  // // auto client_sender = nng::sub::open();

  // nng::set_opt_recv_timeout(client1, 100);
  // nng::set_opt_recv_timeout(client2, 100);

  // nng::sub::set_opt_subscribe(client1, {"DATE:", 5});
  // nng::sub::set_opt_subscribe(client2, {"TIME:", 5});

  // client1.dial(SOCKET_BUS_SERVER_ADDR);
  // client2.dial(SOCKET_BUS_SERVER_ADDR);
  // // client_sender.dial(SOCKET_BUS_SERVER_ADDR);

  // // server.send("DATE: it's actually not a date");
  // server.send("TIME: but more");

  // // client2.send("Test");

  // nng::buffer buffer1;
  // try {
  //   buffer1 = client1.recv(NNG_FLAG_NONBLOCK);
  //   if (buffer1.data() != NULL) {
  //     std::cout << "Client 1 recv " << buffer1.data<char>() << std::endl;
  //   }
  // } catch(const std::exception& e) {
  //   // std::cerr << e.what() << '\n';
  //   std::cout << e.what() << std::endl;
  // }

  // nng::buffer buffer2;
  // try {
  //   buffer2 = client2.recv(NNG_FLAG_NONBLOCK);
  //   if (buffer2.data() != NULL) {
  //     std::cout << "Client 2 recv " << buffer2.data<char>() << std::endl;
  //   }
  // } catch(const std::exception& e) {
  //   // std::cerr << e.what() << '\n';
  //   std::cout << e.what() << std::endl;
  // }
  return 0;
}