#ifndef COMMBUS_DATA_VALUE_H
#define COMMBUS_DATA_VALUE_H

#include <string>
#include <vector>

#include "Classification.h"

namespace CommBus {
namespace Models {
namespace Data {
  
  /**
   * @brief Main data construct
   * Provides storage for *one* of the classified types supported
   * 
   */
  struct DataValue {
    DataClass_T type;
    // COMMBUS_SUPP_DATATYPES_S

    /**
     * @brief Supported data types
     * 
     */
    union {
      char                        COMMBUS_DATA_CHAR_S;
      int                         COMMBUS_DATA_INT_S;
      double                      COMMBUS_DATA_DOUBLE_S;
      bool                        COMMBUS_DATA_BOOL_S;

      std::string                 COMMBUS_DATA_RAW_S;
      std::string                 COMMBUS_DATA_STRING_S;
      std::vector<int>            COMMBUS_DATA_INT_ARR_S;
      std::vector<double>         COMMBUS_DATA_DOUBLE_ARR_S;
      std::vector<bool>           COMMBUS_DATA_BOOL_ARR_S;
    };

    DataValue(const char &v) :            COMMBUS_DATA_CHAR_S(v), type(DataClass_T::COMMBUS_DATA_CHAR_T) {}
    DataValue(const int &v) :             COMMBUS_DATA_INT_S(v), type(DataClass_T::COMMBUS_DATA_INT_T) {}
    DataValue(const double &v) :          COMMBUS_DATA_DOUBLE_S(v), type(DataClass_T::COMMBUS_DATA_DOUBLE_T) {}
    DataValue(const bool &v) :            COMMBUS_DATA_BOOL_S(v), type(DataClass_T::COMMBUS_DATA_BOOL_T) {}

    DataValue(const char* v) :            COMMBUS_DATA_RAW_S(std::move(v)), type(DataClass_T::COMMBUS_DATA_RAW_T) {}
    DataValue(std::string &v) :           COMMBUS_DATA_STRING_S(std::move(v)), type(DataClass_T::COMMBUS_DATA_STRING_T) {}
    DataValue(std::vector<int> &v) :      COMMBUS_DATA_INT_ARR_S(std::move(v)), type(DataClass_T::COMMBUS_DATA_INT_ARR_T) {}
    DataValue(std::vector<double> &v) :   COMMBUS_DATA_DOUBLE_ARR_S(std::move(v)), type(DataClass_T::COMMBUS_DATA_DOUBLE_ARR_T) {}
    DataValue(std::vector<bool> &v) :     COMMBUS_DATA_BOOL_ARR_S(std::move(v)), type(DataClass_T::COMMBUS_DATA_BOOL_ARR_T) {}


    /**
     * @brief Destroy the Data Value object
     * Handles only non trivial types, primitives deleted by default
     * 
     */
    ~DataValue() {
      switch (type) {
        case DataClass_T::COMMBUS_DATA_STRING_T: COMMBUS_DATA_STRING_S.~basic_string(); return;
        case DataClass_T::COMMBUS_DATA_INT_ARR_T: COMMBUS_DATA_INT_ARR_S.~vector(); return;
        case DataClass_T::COMMBUS_DATA_DOUBLE_ARR_T: COMMBUS_DATA_DOUBLE_ARR_S.~vector(); return;
        case DataClass_T::COMMBUS_DATA_BOOL_ARR_T: COMMBUS_DATA_BOOL_ARR_S.~vector(); return;
      }
    }
  };

  struct Datagram {
    std::string location;

    char                        COMMBUS_DATA_CHAR_S;
    int                         COMMBUS_DATA_INT_S;
    double                      COMMBUS_DATA_DOUBLE_S;
    bool                        COMMBUS_DATA_BOOL_S;

    std::string                 COMMBUS_DATA_RAW_S;
    std::string                 COMMBUS_DATA_STRING_S;
    std::vector<int>            COMMBUS_DATA_INT_ARR_S;
    std::vector<double>         COMMBUS_DATA_DOUBLE_ARR_S;
    std::vector<unsigned char>  COMMBUS_DATA_BOOL_ARR_S;

    DataClass_T type;
  };

  template<typename S>
  void serialize(S &s, Datagram &o) {
    s.text1b(o.location, 128);

    s.value1b(o.COMMBUS_DATA_CHAR_S);
    s.value4b(o.COMMBUS_DATA_INT_S);
    s.value8b(o.COMMBUS_DATA_DOUBLE_S);
    s.value1b(o.COMMBUS_DATA_BOOL_S);

    s.text1b(o.COMMBUS_DATA_RAW_S, 128);
    s.text1b(o.COMMBUS_DATA_STRING_S, 128);
    
    s.container4b(o.COMMBUS_DATA_INT_ARR_S, 128);
    s.container8b(o.COMMBUS_DATA_DOUBLE_ARR_S, 128);
    s.container1b(o.COMMBUS_DATA_BOOL_ARR_S, 128);

    s.value2b(o.type);
  }
}
}
}

#endif