#include <iostream>
#include <thread>
#include <string>
#include <chrono>

// #include "nng/compat/nanomsg/nn.h"
// #include "nng/compat/nanomsg/bus.h"
#include "CommBus.h"
#include "Model/Entry.h"
#include "Model/Data/DataValue.h"

// #define SOCKET_BUS_ADDR_INPROC "inproc://bus"
#define SOCKET_BUS_ADDR "inproc://bus"

// #define CLIENT_RECV_IMPL(x,y) try {y=x;} catch(const std::exception& e) {std::cerr << e.what() << '\n';}
// #define CLIENT_RECV(x)  try {x;} catch(const std::exception& e) {std::cerr << e.what() << '\n';}

int main() {
  CommBus::Model::Data::DataValue value("Test");
  std::cout << (int)value.type << std::endl;
  std::cout << "bytes: " << sizeof(value) << std::endl;
  std::cout << value.COMMBUS_DATA_STRING_S << std::endl;

  CommBus::Model::Entry entry("robot");

  entry.set(0.5);
  entry.set("test");

  std::cout << entry.get("") << std::endl;

  // auto v = std::get<std::string>(entry.get());
  // std::cout << v << std::endl;

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