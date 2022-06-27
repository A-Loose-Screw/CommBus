#ifndef COMMBUS_TABLE_H
#define COMMBUS_TABLE_H

#include <string>

namespace CommBus {
namespace Model {

  /**
   * @brief A table is a one dimensional array which holds entries.
   * Each entry consts of a name/id and a value. Of which should be abstract.
   * 
   */
  class Table {
   public:
    Table(std::string name);
  };
}
}

#endif