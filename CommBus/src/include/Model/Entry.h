#ifndef COMMBUS_ENTRY_H
#define COMMBUS_ENTRY_H

#include <string>
#include <memory>
#include <iostream>
#include <variant>
#include <atomic>
#include "Data/DataValue.h"

namespace CommBus {
class Network;
namespace Models {

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
   * @type: Double Array
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
      _hasChanged = true;
    }

    /**
     * @brief Main getter for data
     * 
     * @return std::variant<
     * char,
     * int,
     * double,
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
      double,
      bool,
      const char *,
      std::string,
      std::vector<int>,
      std::vector<double>,
      std::vector<bool>
      > getVariant() {
      switch (_dt->type) {
        case Data::DataClass_T::COMMBUS_DATA_CHAR_T: return _dt->COMMBUS_DATA_CHAR_S;
        case Data::DataClass_T::COMMBUS_DATA_INT_T: return _dt->COMMBUS_DATA_INT_S;
        case Data::DataClass_T::COMMBUS_DATA_DOUBLE_T: return _dt->COMMBUS_DATA_DOUBLE_S;
        case Data::DataClass_T::COMMBUS_DATA_BOOL_T: return _dt->COMMBUS_DATA_BOOL_S;

        case Data::DataClass_T::COMMBUS_DATA_RAW_T: return _dt->COMMBUS_DATA_RAW_S.c_str();
        case Data::DataClass_T::COMMBUS_DATA_STRING_T: return _dt->COMMBUS_DATA_STRING_S;
        case Data::DataClass_T::COMMBUS_DATA_INT_ARR_T: return _dt->COMMBUS_DATA_INT_ARR_S;
        case Data::DataClass_T::COMMBUS_DATA_DOUBLE_ARR_T: return _dt->COMMBUS_DATA_DOUBLE_ARR_S;
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


    friend class ::CommBus::Network;
   private:
    /**
     * @brief Get Datagram of entry (does not set location)
     * 
     * @return Data::Datagram 
     */
    Data::Datagram getDatagram() {
      Data::Datagram d;
      d.type = _dt->type;
      switch (_dt->type) {
        case Data::DataClass_T::COMMBUS_DATA_CHAR_T: d.COMMBUS_DATA_CHAR_S = _dt->COMMBUS_DATA_CHAR_S; break;
        case Data::DataClass_T::COMMBUS_DATA_INT_T: d.COMMBUS_DATA_INT_S = _dt->COMMBUS_DATA_INT_S; break;
        case Data::DataClass_T::COMMBUS_DATA_DOUBLE_T: d.COMMBUS_DATA_DOUBLE_S = _dt->COMMBUS_DATA_DOUBLE_S; break;
        case Data::DataClass_T::COMMBUS_DATA_BOOL_T: d.COMMBUS_DATA_BOOL_S = _dt->COMMBUS_DATA_BOOL_S; break;

        case Data::DataClass_T::COMMBUS_DATA_RAW_T: d.COMMBUS_DATA_RAW_S = _dt->COMMBUS_DATA_RAW_S; break;
        case Data::DataClass_T::COMMBUS_DATA_STRING_T: d.COMMBUS_DATA_STRING_S = _dt->COMMBUS_DATA_STRING_S; break;
        case Data::DataClass_T::COMMBUS_DATA_INT_ARR_T: d.COMMBUS_DATA_INT_ARR_S = _dt->COMMBUS_DATA_INT_ARR_S; break;
        case Data::DataClass_T::COMMBUS_DATA_DOUBLE_ARR_T: d.COMMBUS_DATA_DOUBLE_ARR_S = _dt->COMMBUS_DATA_DOUBLE_ARR_S; break;
        case Data::DataClass_T::COMMBUS_DATA_BOOL_ARR_T:
          for (auto act_bool : _dt->COMMBUS_DATA_BOOL_ARR_S) {
            d.COMMBUS_DATA_BOOL_ARR_S.push_back(act_bool);
          }
          break;
      }

      return d;
    }

    /**
     * @brief Set entry based on a datagram
     * 
     * @param d 
     */
    void setFromDatagram(Data::Datagram d) {
      switch (d.type) {
        case Data::DataClass_T::COMMBUS_DATA_CHAR_T: _dt = std::make_unique<Data::DataValue>(d.COMMBUS_DATA_CHAR_S); break;
        case Data::DataClass_T::COMMBUS_DATA_INT_T: _dt = std::make_unique<Data::DataValue>(d.COMMBUS_DATA_INT_S); break;
        case Data::DataClass_T::COMMBUS_DATA_DOUBLE_T: _dt = std::make_unique<Data::DataValue>(d.COMMBUS_DATA_DOUBLE_S); break;
        case Data::DataClass_T::COMMBUS_DATA_BOOL_T: _dt = std::make_unique<Data::DataValue>(d.COMMBUS_DATA_BOOL_S); break;

        case Data::DataClass_T::COMMBUS_DATA_RAW_T: _dt = std::make_unique<Data::DataValue>(d.COMMBUS_DATA_RAW_S); break;
        case Data::DataClass_T::COMMBUS_DATA_STRING_T: _dt = std::make_unique<Data::DataValue>(d.COMMBUS_DATA_STRING_S); break;
        case Data::DataClass_T::COMMBUS_DATA_INT_ARR_T: _dt = std::make_unique<Data::DataValue>(d.COMMBUS_DATA_INT_ARR_S); break;
        case Data::DataClass_T::COMMBUS_DATA_DOUBLE_ARR_T: _dt = std::make_unique<Data::DataValue>(d.COMMBUS_DATA_DOUBLE_ARR_S); break;
        case Data::DataClass_T::COMMBUS_DATA_BOOL_ARR_T: 
          std::vector<bool> tmp;
          for (auto char_bool : d.COMMBUS_DATA_BOOL_ARR_S) {
            tmp.push_back(char_bool);
          }
          _dt = std::make_unique<Data::DataValue>(tmp); 
          break;
      }

      _dt->type = d.type; 
    }

    std::unique_ptr<Data::DataValue> _dt;
    std::string _name;

    std::atomic_bool _hasChanged{false};
  };
}
}

#endif