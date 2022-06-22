#include <iostream>
#include "CommBus.h"



int main() {
  std::cout << "Starting CommBus test..." << std::endl;

  CommBus::Server server;
  server.start();

  while (true);
  return 0;
}