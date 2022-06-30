#include <iostream>
#include <thread>
#include <string>
#include <chrono>
#include <algorithm>

// #include "nng/compat/nanomsg/nn.h"
#include "nng/compat/nanomsg/bus.h"
#include "CommBus.h"

#include "Network/Network.h"

// #define SOCKET_BUS_ADDR_INPROC "inproc://bus"
#define SOCKET_BUS_LOCAL_ADDR "tcp://0.0.0.0:1905"
#define SOCKET_BUS_SERVER_ADDR COMMBUS_LOCAL_ADDR

using namespace std::literals::chrono_literals;
using d_micro = std::chrono::duration<double, std::micro>;

using namespace CommBus::Models;

int main() {

  Model md;
  md.getTable("Drivetrain")->getEntry("Entry")->set("Test from drivetrain entry");

  CommBus::Network server(CommBus::Network::Type::SERVER);
  CommBus::Network node(CommBus::Network::Type::NODE);

  server.start();
  node.start();

  server.getModel()->getTable("Drivetrain")->getEntry("Test")->set(std::vector<double>{3.04, 1.001, 0.45});

  server.senderUpdate();

  std::this_thread::sleep_for(3s);

  node.receiverUpdate();


  auto entry = node.getModel()->getTable("Drivetrain")->getEntry("Test")->get(std::vector<double>{});

  for (auto v : entry) {
    std::cout << v << std::endl;
  }

  return 0;
}