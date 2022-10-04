#include "Model/Model.h"

using namespace CommBus::Models;

std::shared_ptr<Table> Model::createTable(std::string name) {
  std::shared_ptr<Table> table = std::make_shared<Table>(name);
  _tables.insert({name, table});
  return table;
}

std::shared_ptr<Table> Model::getTable(std::string name) {
  std::unordered_map<std::string, std::shared_ptr<Table>>::const_iterator iter = _tables.find(name);
  if (iter != _tables.end()) {
    return iter->second;
  } else {
    return createTable(name);
  }
}

std::unordered_map<std::string, std::shared_ptr<Table>> Model::getTables() {
  if (_tables.size() > 0) {
    return _tables;
  }

  return {};
}

std::vector<std::string> Model::getTableNames() {
  std::vector<std::string> names;
  for (auto &table : _tables) {
    names.push_back(table.second->getName());
  }

  return names;
}

int Model::getSize() {
  return _tables.size();
}