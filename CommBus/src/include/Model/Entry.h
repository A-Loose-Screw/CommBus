#ifndef COMMBUS_ENTRY_H
#define COMMBUS_ENTRY_H

#include <string>
#include <memory>
#include <iostream>
#include <variant>
#include "Data/DataValue.h"

namespace CommBus {
namespace Model {

  /**
   * @brief An Entry is an data entry to a table. And can hold *one* the following types
   * 
   * @type: Char
   * @type: Int
   * @type: Float
   * @type: Boolean
   * @type: String
   * @type: Char array/Raw
   * @type: Int Array
   * @type: Float Array
   * @type: Boolean Array
   * 
   * 
   */
  class Entry {
   public:
    Entry(std::string name);

    /**
     * @brief Set entry value
     * 
     * @tparam T 
     * @param v 
     */
    template<typename T>
    void set(T v) {
      _dt = std::make_unique<Data::DataValue>(v);
    }

    /**
     * @brief Main getter for data
     * 
     * @return std::variant<
     * char,
     * int,
     * float,
     * bool,
     * std::string,
     * const char*,
     * std::vector<int>,
     * std::vector<float>,
     * std::vector<bool>
     * > 
     */
    std::variant<
      char,
      int,
      float,
      bool,
      const char *,
      std::string,
      std::vector<int>,
      std::vector<float>,
      std::vector<bool>
      > getVariant() {
      switch (_dt->type) {
        case Data::DataClass_T::COMMBUS_DATA_CHAR_T: return _dt->COMMBUS_DATA_CHAR_S;
        case Data::DataClass_T::COMMBUS_DATA_INT_T: return _dt->COMMBUS_DATA_INT_S;
        case Data::DataClass_T::COMMBUS_DATA_FLOAT_T: return _dt->COMMBUS_DATA_FLOAT_S;
        case Data::DataClass_T::COMMBUS_DATA_BOOL_T: return _dt->COMMBUS_DATA_BOOL_S;

        case Data::DataClass_T::COMMBUS_DATA_RAW_T: return _dt->COMMBUS_DATA_RAW_S.c_str();
        case Data::DataClass_T::COMMBUS_DATA_STRING_T: return _dt->COMMBUS_DATA_STRING_S;
        case Data::DataClass_T::COMMBUS_DATA_INT_ARR_T: return _dt->COMMBUS_DATA_INT_ARR_S;
        case Data::DataClass_T::COMMBUS_DATA_FLOAT_ARR_T: return _dt->COMMBUS_DATA_FLOAT_ARR_S;
        case Data::DataClass_T::COMMBUS_DATA_BOOL_ARR_T: return _dt->COMMBUS_DATA_BOOL_ARR_S;
      }
    }

    /**
     * @brief Get using std::get
     * 
     * @tparam T 
     * @param default_value 
     * @return T 
     */
    template<typename T>
    T get(T default_value) {
      if (_dt == nullptr) {
        return default_value;
      }
      
      try {
        return std::get<T>(getVariant());
      } catch (std::bad_variant_access&) {
        return default_value;
      }
    }

    /**
     * @brief Get the Type object
     * 
     * @return Data::DataClass_T 
     */
    Data::DataClass_T getType();

    /**
     * @brief Get the Name object
     * 
     * @return std::string 
     */
    std::string getName();

   private:
    std::unique_ptr<Data::DataValue> _dt;
    std::string _name;
  };
}
}

#endif