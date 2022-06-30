#include "Network/Network.h"

#include "bitsery/bitsery.h"
#include "bitsery/adapter/buffer.h"
#include "bitsery/traits/string.h"
#include "bitsery/traits/vector.h"

#include "nngpp/protocol/bus0.h"

using namespace CommBus;

using Buffer = std::string;
using OutputAdapter = bitsery::OutputBufferAdapter<Buffer>;
using InputAdapter = bitsery::InputBufferAdapter<Buffer>;

Network::Network(Type type, std::string address) {
  _type = type;
  _addr = address;

  _socket = nng::bus::open();
}

void Network::start() {
  switch (_type) {
    case Type::SERVER: _socket.listen(_addr.c_str()); break;
    case Type::NODE: _socket.dial(_addr.c_str()); break;
  }
}

void Network::senderUpdate() {
  std::vector<Models::Data::Datagram> changedEntries;
  for (auto &table : getModel()->getTables()) {
    for (auto &entry : table->getEntries()) {
      // check if it's been updated
      if (entry->_hasChanged) {
        Models::Data::Datagram d = entry->getDatagram();
        d.location = (table->getName() + "/" + entry->getName());
        changedEntries.push_back(d);
        entry->_hasChanged = false;
      }
    }
  }

  // @TODO send the changed entries (with the table name)
  for (auto &entryDatagram : changedEntries) {
    Buffer buffer;
    auto writtenSize = bitsery::quickSerialization<OutputAdapter>(buffer, entryDatagram);
    const char *sendBuffer = reinterpret_cast<char *>(buffer.data());
    _socket.send({sendBuffer, writtenSize});
    std::cout << "Sent data" << std::endl; // debug tmp
  }
}

void Network::receiverUpdate() {
  Models::Data::Datagram changedEntry;
  nng::buffer receiveBuffer = _socket.recv();
  Buffer buffer(receiveBuffer.data<char>(), receiveBuffer.size());
  auto state = bitsery::quickDeserialization<InputAdapter>({buffer.begin(), receiveBuffer.size()}, changedEntry);

  if (state.first == bitsery::ReaderError::NoError) {
    std::string delimiter = "/";
    std::vector<std::string> tokens;
    
    auto start = 0U;
    auto end = changedEntry.location.find(delimiter);

    tokens.push_back(changedEntry.location.substr(start, end));
    start = end + delimiter.length();
    end = changedEntry.location.length();
    tokens.push_back(changedEntry.location.substr(start, end));

    _model->getTable(tokens[0])->getEntry(tokens[1])->setFromDatagram(changedEntry); // creates entry automatically
  }
}

std::shared_ptr<Models::Model> Network::getModel() {
  return _model;
}