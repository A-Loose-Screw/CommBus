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

int main() try {
  CommBus::Network server(CommBus::Network::Type::SERVER);
  CommBus::Network node(CommBus::Network::Type::NODE, COMMBUS_GET_EXTERNAL_IP("127.0.0.1"));

  server.start();
  node.start();

  /**
   * @brief Seralize/sender
   * 
   */
  auto start = std::chrono::high_resolution_clock::now();
  server.getModel()->getTable("Drivetrain")->getEntry("Test")->set(std::vector<double>{3.04, 1.001, 0.45});

  server.senderUpdate(true);
  auto stop = std::chrono::high_resolution_clock::now();
  double sender_time = std::chrono::duration_cast<d_micro>(stop-start).count();


  std::this_thread::sleep_for(3s);


  /**
   * @brief Deserializer/receiver
   * 
   */
  start = std::chrono::high_resolution_clock::now();
  node.receiverUpdate(true);

  auto entry = node.getModel()->getTable("Drivetrain")->getEntry("Test")->get(std::vector<double>{});
  stop = std::chrono::high_resolution_clock::now();
  double receiver_time = std::chrono::duration_cast<d_micro>(stop-start).count();


  /**
   * @brief Results
   * 
   */
  std::cout << "Serialized Send Time (us): " << sender_time << std::endl;
  std::cout << "Deserialized Receive Time (us): " << receiver_time << std::endl;
  std::cout << "Simulated Respones Time (us): " << sender_time+receiver_time << std::endl;

  std::cout << "Result data" << std::endl;
  for (auto v : entry) {
    std::cout << v << std::endl;
  }

  return 0;
} catch (const std::exception& e) {
  std::cerr << e.what() << '\n';
  return 0;
}