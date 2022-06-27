#ifndef COMMBUS_ENTRY_H
#define COMMBUS_ENTRY_H

#include <string>
#include <memory>
#include "Data/Data.h"

namespace CommBus {
namespace Model {

  /**
   * @brief An Entry is an entry to a table. And can hold the following types
   * 
   * @type: Char
   * @type: Int
   * @type: Float
   * @type: Boolean
   * @type: String
   * @type: Int Array
   * @type: Float Array
   * @type: Boolean Array
   * 
   * 
   */
  class Entry {
   public:
    Entry(std::string &name);

    void set(Data::DataConstruct data, Data::DataClass type) {
      _dt.data = data;
      _dt.type = type;
    }

    void setChar(char data);
    void setInt(int data);
    void setFloat(float data);
    void setBool(bool data);
    void setString(std::string data);
    void setIntArr(std::vector<int> data);
    void setFloatArr(std::vector<float> data);
    void setBool(std::vector<bool> data);

    
    // char getChar() { return get().COMMBUS_DATA_CHAR_S; }
    // int getInt() { return get().COMMBUS_DATA_INT_S; }
    // float getFloat() { return get().COMMBUS_DATA_FLOAT_S; }
    // bool getBool() { return get().COMMBUS_DATA_BOOL_S; }

   private:
    Data::Datagram _dt;
    std::string _name;
  };
}
}

#endif