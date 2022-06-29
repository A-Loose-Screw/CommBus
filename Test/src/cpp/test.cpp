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

using namespace std::literals::chrono_literals;
using d_micro = std::chrono::duration<double, std::micro>;

// #define CLIENT_RECV_IMPL(x,y) try {y=x;} catch(const std::exception& e) {std::cerr << e.what() << '\n';}
// #define CLIENT_RECV(x)  try {x;} catch(const std::exception& e) {std::cerr << e.what() << '\n';}

int main() {
  CommBus::Network nt(CommBus::Network::Type::SERVER);

  std::cout << "Timing start" << std::endl;
  auto start = std::chrono::high_resolution_clock::now();
  nt.getModel()->getTable("test")->getEntry("entry")->set(0.0);
  auto stop = std::chrono::high_resolution_clock::now();

  std::cout << "Execution time: " << std::chrono::duration_cast<d_micro>(stop-start).count() << std::endl;
  nt.update();
  nt.update();
  nt.getModel()->getTable("test")->getEntry("entry")->set(1.0);
  nt.update();
  nt.update();


  // auto bus1 = nng::bus::open();
  // auto bus2 = nng::bus::open();
  // auto bus3 = nng::bus::open();

  // bus1.listen(SOCKET_BUS_LOCAL_ADDR);
  // bus2.dial(SOCKET_BUS_ADDR);
  // bus3.dial(SOCKET_BUS_ADDR);

  // bus1.send("test");

  // std::cout << "Data: " << bus2.recv().data<char>() << std::endl;
  // std::cout << "Data: " << bus3.recv().data<char>() << std::endl;
  return 0;
}