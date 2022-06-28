#ifndef COMMBUS_DATA_VALUE_H
#define COMMBUS_DATA_VALUE_H

#include <string>
#include <vector>

#include "Classification.h"

namespace CommBus {
namespace Model {
namespace Data {
  
  /**
   * @brief Main data construct
   * Provides storage for *one* of the classified types supported
   * 
   */
  struct DataValue {
    DataClass_T type;

    /**
     * @brief Supported data types
     * 
     */
    union {
      char                        COMMBUS_DATA_CHAR_S;
      int                         COMMBUS_DATA_INT_S;
      float                       COMMBUS_DATA_FLOAT_S; 
      bool                        COMMBUS_DATA_BOOL_S;

      std::string                 COMMBUS_DATA_STRING_S;
      std::vector<int>            COMMBUS_DATA_INT_ARR_S;
      std::vector<float>          COMMBUS_DATA_FLOAT_ARR_S;
      std::vector<bool>           COMMBUS_DATA_BOOL_ARR_S;
    };

    DataValue(const char &v) :            COMMBUS_DATA_CHAR_S(v), type(DataClass_T::COMMBUS_DATA_CHAR_T) {}
    DataValue(const int &v) :             COMMBUS_DATA_INT_S(v), type(DataClass_T::COMMBUS_DATA_INT_T) {}
    DataValue(const float &v) :           COMMBUS_DATA_FLOAT_S(v), type(DataClass_T::COMMBUS_DATA_FLOAT_T) {}
    DataValue(const bool &v) :            COMMBUS_DATA_BOOL_S(v), type(DataClass_T::COMMBUS_DATA_BOOL_T) {}

    DataValue(const char* &&v) :          COMMBUS_DATA_STRING_S(std::move(v)), type(DataClass_T::COMMBUS_DATA_STRING_T) {}
    DataValue(std::vector<int> &&v) :     COMMBUS_DATA_INT_ARR_S(std::move(v)), type(DataClass_T::COMMBUS_DATA_INT_ARR_T) {}
    DataValue(std::vector<float> &&v) :   COMMBUS_DATA_FLOAT_ARR_S(std::move(v)), type(DataClass_T::COMMBUS_DATA_FLOAT_ARR_T) {}
    DataValue(std::vector<bool> &&v) :    COMMBUS_DATA_BOOL_ARR_S(std::move(v)), type(DataClass_T::COMMBUS_DATA_BOOL_ARR_T) {}


    /**
     * @brief Destroy the Data Value object
     * Handles only non trivial types, primitives deleted by default
     * 
     */
    ~DataValue() {
      switch (type) {
        case DataClass_T::COMMBUS_DATA_STRING_T: COMMBUS_DATA_STRING_S.~basic_string(); return;
        case DataClass_T::COMMBUS_DATA_INT_ARR_T: COMMBUS_DATA_INT_ARR_S.~vector(); return;
        case DataClass_T::COMMBUS_DATA_FLOAT_ARR_T: COMMBUS_DATA_FLOAT_ARR_S.~vector(); return;
        case DataClass_T::COMMBUS_DATA_BOOL_ARR_T: COMMBUS_DATA_BOOL_ARR_S.~vector(); return;
      }
    }
  };
}
}
}

#endif