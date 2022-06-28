#ifndef COMMBUS_DATA_CLASSIFICATION_H
#define COMMBUS_DATA_CLASSIFICATION_H

namespace CommBus {
namespace Model {
namespace Data {
  /**
   * @brief Classification for all supported datatypes in the model
   * 
   */
  enum class DataClass_T {
    COMMBUS_DATA_CHAR_T         = 0,
    COMMBUS_DATA_INT_T          = 1,
    COMMBUS_DATA_FLOAT_T        = 2,
    COMMBUS_DATA_BOOL_T         = 3,
    COMMBUS_DATA_STRING_T       = 4,
    COMMBUS_DATA_INT_ARR_T      = 5,
    COMMBUS_DATA_FLOAT_ARR_T    = 6,
    COMMBUS_DATA_BOOL_ARR_T     = 7
  };
}
}
}

#endif