#include <thread>

#include "Network/Network.h"

#include "bitsery/bitsery.h"
#include "bitsery/adapter/buffer.h"
#include "bitsery/traits/string.h"
#include "bitsery/traits/vector.h"

#include "nngpp/nngpp.h"
#include "nngpp/protocol/bus0.h"

using namespace CommBus;
using namespace std::literals::chrono_literals;
using d_micro = std::chrono::duration<double, std::micro>;

using Buffer = std::string;
using OutputAdapter = bitsery::OutputBufferAdapter<Buffer>;
using InputAdapter = bitsery::InputBufferAdapter<Buffer>;

Network::Network(Type type, std::string address) {
  _type = type;
  _addr = address;

  _nng_socket = std::make_shared<nng::socket>(nng::bus::open());  
}

int Network::start(bool retryLoop) {
  do {
    if (_connected) break;
    try {
      switch (_type) {
        case Type::SERVER: std::static_pointer_cast<nng::socket>(_nng_socket)->listen(_addr.c_str()); break;
        case Type::NODE: std::static_pointer_cast<nng::socket>(_nng_socket)->dial(_addr.c_str()); break;
      }
      _connected = true;
    } catch (const std::exception &e) {
      _connected = false;
      std::cerr << e.what() << '\n';
      std::this_thread::sleep_for(1s);
    }
  } while (!_connected && retryLoop);

  return _connected ? 0 : -1;
}

void Network::senderUpdate(bool noBlock) {
  if (!_connected) return;
  std::vector<Models::Data::Datagram> changedEntries;

  // Get tables
  if (getModel()->getTables().size() > 0) {
    for (auto &table : getModel()->getTables()) {

      // Get entries
      if (table.second->getEntries().size() > 0) {
        for (auto &entry : table.second->getEntries()) {
          // check if entry has been changed
          if (entry.second->_hasChanged) {
            Models::Data::Datagram d = entry.second->getDatagram();
            d.location = (table.second->getName() + "/" + entry.second->getName());
            changedEntries.push_back(d);
            entry.second->_hasChanged = false;
          }
        }
      }
    }
  }

  if (changedEntries.size() > 0) {
    for (auto &entryDatagram : changedEntries) {
      Buffer buffer;
      auto writtenSize = bitsery::quickSerialization<OutputAdapter>(buffer, entryDatagram);
      const char *sendBuffer = reinterpret_cast<char *>(buffer.data());
      
      try {
        std::static_pointer_cast<nng::socket>(_nng_socket)->send(nng::view{sendBuffer, writtenSize}, noBlock ? NNG_FLAG_NONBLOCK : 0);
      } catch (const nng::exception &e) {
        printf( "%s: %s\n", e.who(), e.what() );
        break;
      }
    }
  }
}

void Network::receiverUpdate(bool noBlock) {
  if (!_connected) return;
  Models::Data::Datagram changedEntry;
  nng::buffer receiveBuffer;
  Buffer buffer;
  try {
    receiveBuffer = std::static_pointer_cast<nng::socket>(_nng_socket)->recv( noBlock ? NNG_FLAG_NONBLOCK : 0);
    buffer = Buffer(receiveBuffer.data<char>(), receiveBuffer.size());
  } catch (const nng::exception &e) {
    printf( "%s: %s\n", e.who(), e.what() );
    return;
  }
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