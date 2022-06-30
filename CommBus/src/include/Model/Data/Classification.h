#ifndef COMMBUS_DATA_CLASSIFICATION_H
#define COMMBUS_DATA_CLASSIFICATION_H

namespace CommBus {
namespace Models {
namespace Data {
  /**
   * @brief Classification for all supported datatypes in the Models
   * 
   */
  enum class DataClass_T:uint16_t {
    COMMBUS_DATA_RAW_T          = 0,
    COMMBUS_DATA_CHAR_T         = 1,
    COMMBUS_DATA_INT_T          = 2,
    COMMBUS_DATA_DOUBLE_T       = 3,
    COMMBUS_DATA_BOOL_T         = 4,
    COMMBUS_DATA_STRING_T       = 5,
    COMMBUS_DATA_INT_ARR_T      = 6,
    COMMBUS_DATA_DOUBLE_ARR_T   = 7,
    COMMBUS_DATA_BOOL_ARR_T     = 8
  };
}
}
}

#endif