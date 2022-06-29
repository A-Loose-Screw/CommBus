#include "Model/Model.h"

using namespace CommBus::Models;

std::shared_ptr<Table> Model::createTable(std::string name) {
  _tables.push_back(std::move(std::make_shared<Table>(name)));
  return _tables.back();
}

std::shared_ptr<Table> Model::getTable(std::string name) {
  if (_tables.size() > 0) {
    for (auto &table : _tables) {
      if (table->getName() == name) {
        return table;
      }
    }
  }

  return createTable(name);
}

std::vector<std::string> Model::getTableNames() {
  std::vector<std::string> names;
  for (auto &table : _tables) {
    names.push_back(table->getName());
  }
}

int Model::getSize() {
  return _tables.size();
}