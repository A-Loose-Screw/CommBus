#ifndef COMMBUS_DATA_H
#define COMMBUS_DATA_H

#include <string>
#include <vector>

#include "Classification.h"

// #define SWITCH_GET(type, )

namespace CommBus {
namespace Model {
namespace Data {

  /**
   * @brief Pure storage construct for specified data
   * 
   */
  struct DataConstruct {
    char                        COMMBUS_DATA_CHAR_S;
    int                         COMMBUS_DATA_INT_S;
    float                       COMMBUS_DATA_FLOAT_S; 
    bool                        COMMBUS_DATA_BOOL_S;
    std::string                 COMMBUS_DATA_STRING_S;
    std::vector<int>            COMMBUS_DATA_INT_ARR_S;
    std::vector<float>          COMMBUS_DATA_FLOAT_ARR_S;
    std::vector<bool>           COMMBUS_DATA_BOOL_ARR_S;
  };
  
  /**
   * @brief Datagram, consists of the type of data and the storage
   * 
   */
  struct Datagram {
    // DataClass     type;
    DataConstruct data;
  };

  // static void setData(DataStorage d, DataClass c);
}
}
}

#endif