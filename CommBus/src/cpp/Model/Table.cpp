#include "Model/Table.h"

using namespace CommBus::Models;

Table::Table(std::string name) : _name(name) {}

std::shared_ptr<Entry> Table::createEntry(std::string name) {
  _entries.push_back(std::move(std::make_shared<Entry>(name)));
  return _entries.back();
}

std::shared_ptr<Entry> Table::getEntry(std::string name) {
  if (_entries.size() > 0) {
    for (auto &entry : _entries) {
      if (entry->getName() == name) {
        return entry;
      }
    }
  }

  return createEntry(name);
}

int Table::getSize() {
  return _entries.size();
}

std::string Table::getName() {
  return _name;
}