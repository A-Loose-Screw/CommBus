#include "Model/Table.h"

using namespace CommBus::Models;

Table::Table(std::string name) : _name(name) {}

std::shared_ptr<Entry> Table::createEntry(std::string name) {
  std::shared_ptr<Entry> entry = std::make_shared<Entry>(name);
  _entries.insert({name, entry});
  return entry;
}

std::shared_ptr<Entry> Table::getEntry(std::string name) {
  std::unordered_map<std::string, std::shared_ptr<Entry>>::const_iterator iter = _entries.find(name);
  if (iter != _entries.end()) {
    return iter->second;
  } else {
    return createEntry(name);
  }
}

std::unordered_map<std::string, std::shared_ptr<Entry>> Table::getEntries() {
  if (_entries.size() > 0) {
    return _entries;
  }

  return {};
}

int Table::getSize() {
  return _entries.size();
}

std::string Table::getName() {
  return _name;
}

std::vector<std::string> Table::getEntryNames() {
  std::vector<std::string> names;
  for (auto &entry : _entries) {
    names.push_back(entry.second->getName());
  }

  return names;
}