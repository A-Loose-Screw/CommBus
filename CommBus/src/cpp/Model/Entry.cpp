#include "Model/Entry.h"

using namespace CommBus::Model;

Entry::Entry(std::string name) : _name(name) {}

Data::DataClass_T Entry::getType() {
  return _dt->type;
}

std::string Entry::getName() {
  return _name;
}