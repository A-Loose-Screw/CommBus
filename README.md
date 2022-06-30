# CommBus
Communication bus network. Using the [NNG](https://github.com/nanomsg/nng) bus protocol serialized using [bitsery](https://github.com/fraillt/bitsery). For communication with distributed dictionary networks

- Note this library is a C++17 implementation

[![Build Status](https://dev.azure.com/ConnorBuchel0890/A-Loose-Screw/_apis/build/status/A-Loose-Screw.CommBus?branchName=master)](https://dev.azure.com/ConnorBuchel0890/A-Loose-Screw/_build/latest?definitionId=23&branchName=master)

## Usage
- CommBus is a entry based self monitoring network solution which can be spread across multiple .
- Each entry can be dynamically set between the following types `(char, int, float, bool, string, char*, int vector, double vector, bool vector)`
- Multiple entries can exist under a table with a given name specified by the user
- Multiple tables can exist under a network model. With their own names given to by the user.

### Setting/Getting Entries
```cpp
#include <vector>
#include "CommBus.h"

using namespace CommBus;

int main() {
  Network myNetwork(Network::Type::SERVER); // default address is `tcp://0.0.0.0:1905`

  auto student_table = myNetwork.getModel()->getTable("Student"); // creates table named Student, if one does not already exists

  student_table->getEntry("Name")->set("CJ"); // creates entry called Name if it doesn't already exist and sets it to a const char* with the value CJ
  student_table->getEntry("Age")->set(20); // create entry named Age and set it to an integer holding 20
  student_table->getEntry("Height")->set(5.3); // create height and set to a double

  std::string name = student_table->getEntry("Name")->get(""); // get name, and provide the default value if not found (also used to determine datatype)
  int age = student_table->getEntry("Age")->(0); // get age
  int hieght = student_table->getEntry("Height")->(0.0); // get height. Note that it needs 0.0 not just for default but also to determine double value

  /**
   * We can also create multiple tables within the model, and store more than just primitives
   */
  auto teacher_table = myNetwork.getModel()->getTable("Teacher"); // create new table

  teacher_table->getEntry("Student Grades")->set(std::vector<double>{50.3, 84.8, 17.002}); // set vector

  std::vector<double> grades = teacher_table->getEntry("Student Grades")->get(std::vector<double>{});

  return 0;
}
```

### Sending/Receiving Data
- Inside a network, at least one server must exist. And all nodes must point to that servers address

Server
```cpp
#include <vector>
#include "CommBus.h"

using namespace CommBus;

int main() {
  Network myServer(Network::Type::SERVER); // default address is `tcp://0.0.0.0:1905`
  myServer.start(); // opens the socket and starts listening for nodes

  myServer.getModel()->getTable("Weather")->getEntry("Temp")->set(27.5); // set data in the table

  /**
   * Update the sender,
   * searches for any entries that have been changed
   * And sends them over the network
   */
  myServer.senderUpdate(); // note that by default senderUpdate is in blocking mode. set to blocking using `myServer.senderUpdate(true)`

  return 0;
}
```

Node
```cpp
#include <vector>
#include "CommBus.h"

using namespace CommBus;

int main() {
  Network myNode(Network::Type::NODE, COMMBUS_GET_EXTERNAL_IP("192.168.178.127")); // you can also directly set the address to `tcp://192.168.178.127:1905` 
  myNode.start(); // opens the socket

  /**
   * Update the receiver
   * Will grab any incoming messages, and create/modify entries based on received data
   * By default it is set to blocking mode. And will halt program until data is received
   */
  myNode.receiverUpdate(); // Set to non blocking via `myNode.receiverUpdate(true);`

  double temp = myNode.getModel()->getTable("Weather")->getEntry("Temp")->get(0.0); // set data in the table

  std::cout << "Temp from server: " << temp << std::endl;
  return 0;
}
```

- Output: `Temp from server: 27.5`

### Notes
- The network is simple and has a very fast speed using basic types. around 0.5-20ms
- The network allows for both sending and receiving for nodes and servers. And is designed for large networks where each device needs to both send and receive data.
- It's scalable and allows for dynamic change in data for an entry as everything is stored in variants and unions, this means it can change from being a std::string to double with little effort
- However, only *one* type of data is allowed at a time per entry. When the datatype changes, it overwrites the previous memory address. [Union-Type](https://en.cppreference.com/w/cpp/language/union)