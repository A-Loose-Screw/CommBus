#include <iostream>
#include <thread>
#include <string>
#include <chrono>

// #include "nng/compat/nanomsg/nn.h"
// #include "nng/compat/nanomsg/bus.h"
#include "CommBus.h"

// #define SOCKET_BUS_ADDR_INPROC "inproc://bus"
#define SOCKET_BUS_ADDR "inproc://bus"

// #define CLIENT_RECV_IMPL(x,y) try {y=x;} catch(const std::exception& e) {std::cerr << e.what() << '\n';}
// #define CLIENT_RECV(x)  try {x;} catch(const std::exception& e) {std::cerr << e.what() << '\n';}

int main() {
  CommBus::Models::Model model;

  model.getTable("HID")->getEntry("Xbox_X")->set(0.3);
  auto xbox = model.getTable("HID")->getEntry("Entry");

  xbox->set(3.1);
  std::cout << "Xbox: " << xbox->get(0.0) << std::endl;

  xbox->set('c');
  std::cout << "Xbox: " << xbox->get(' ') << std::endl;

  xbox->set(true);
  std::cout << "Xbox: " << xbox->get(false) << std::endl;

  xbox->set(3);
  std::cout << "Xbox: " << xbox->get(0) << std::endl;

  xbox->set((std::string)"Test");
  std::cout << "Xbox: " << xbox->get((std::string)"") << std::endl;

  xbox->set("Test");
  std::cout << "Xbox: " << xbox->get("") << std::endl;

  xbox->set(std::vector<int>{3,2,1});
  std::cout << "Xbox: " << xbox->get(std::vector<int>{0})[0] << std::endl;

  xbox->set(std::vector<double>{3.2,2.2,1});
  std::cout << "Xbox: " << xbox->get(std::vector<double>{0})[0] << std::endl;

  xbox->set(std::vector<bool>{true,false,false});
  std::cout << "Xbox: " << xbox->get(std::vector<bool>{0})[0] << std::endl;
  

  // model.getTable("HID")->getEntry("Xbox_X")->set(0.3);
  // std::cout << "Type: " << (int)model.getTable("HID")->getEntry("Xbox_X")->getType() << std::endl;
  // std::cout << model.getTable("HID")->getEntry("Xbox_X")->get(0.0) << std::endl;
  /**
   * @brief PubSub
   * 
   */
  // auto server = nng::pub::open();
  // // server.dial(SOCKET_BUS_ADDR);
  // server.listen(SOCKET_BUS_ADDR);

  // auto client1 = nng::sub::open();
  // auto client2 = nng::sub::open();

  // nng::set_opt_recv_timeout(client1, 100);
  // nng::set_opt_recv_timeout(client2, 100);

  // nng::sub::set_opt_subscribe(client1, {"DATE:", 5});
  // nng::sub::set_opt_subscribe(client2, {"TIME:", 5});

  // client1.dial(SOCKET_BUS_ADDR);
  // client2.dial(SOCKET_BUS_ADDR);

  // server.send("DATE: it's actually not a date");
  // server.send("TIME: but more");

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
// catch( const nng::exception& e ) {
//   // who() is the name of the nng function that produced the error
//   // what() is a description of the error code
//   printf( "%s: %s\n", e.who(), e.what() );
//   return 1;
// }