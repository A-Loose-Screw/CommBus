#include <iostream>
#include <thread>
#include <string>
#include <chrono>

// #include "nng/compat/nanomsg/nn.h"
#include "nng/compat/nanomsg/bus.h"
#include "CommBus.h"

#include "bitsery/bitsery.h"
#include "bitsery/adapter/buffer.h"
#include "bitsery/traits/string.h"
#include "bitsery/traits/vector.h"

// #define SOCKET_BUS_ADDR_INPROC "inproc://bus"
#define SOCKET_BUS_LOCAL_ADDR "tcp://0.0.0.0:1905"
#define SOCKET_BUS_SERVER_ADDR COMMBUS_LOCAL_ADDR

using namespace std::literals::chrono_literals;
using d_micro = std::chrono::duration<double, std::micro>;

using namespace CommBus::Models;

using Buffer = std::vector<uint8_t>;
using OutputAdapter = bitsery::OutputBufferAdapter<Buffer>;
using InputAdapter = bitsery::InputBufferAdapter<Buffer>;

int main() {

  Model md;
  md.getTable("Drivetrain")->getEntry("Entry")->set("Test from drivetrain entry");

  Data::Datagram dt = md.getTable("Drivetrain")->getEntry("Entry")->getDatagram();
  Data::Datagram recv;

  // auto start = std::chrono::high_resolution_clock::now();

  Buffer buffer;
  auto writtenSize = bitsery::quickSerialization<OutputAdapter>(buffer, dt);
  std::cout << "Size: " << writtenSize << std::endl;
  auto state = bitsery::quickDeserialization<InputAdapter>({buffer.begin(), writtenSize}, recv);

  md.getTable("Drivetrain")->getEntry("Entry2")->setFromDatagram(recv);

  std::cout << "From buffer dt: " << md.getTable("Drivetrain")->getEntry("Entry2")->get("") << std::endl;;

  // auto stop = std::chrono::high_resolution_clock::now();

  // std::cout << "Received Data:" << std::endl;
  // std::cout << receiver.location << std::endl;
  // std::cout << receiver.payload << std::endl;
  // std::cout << "Execution time: " << std::chrono::duration_cast<d_micro>(stop-start).count() << std::endl;

  // auto bus1 = nng::bus::open();
  // auto bus2 = nng::bus::open();

  // bus1.listen(SOCKET_BUS_SERVER_ADDR);
  // bus2.dial("tcp://127.0.0.1:1905");

  

  // bus1.send("test");

  // std::cout << "Data: " << bus2.recv().data<char>() << std::endl;
  return 0;
}