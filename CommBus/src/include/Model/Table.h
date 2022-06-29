#ifndef COMMBUS_TABLE_H
#define COMMBUS_TABLE_H

#include <string>
#include "Entry.h"

namespace CommBus {
namespace Models {

  /**
   * @brief A table is a one dimensional array which holds entries.
   * Each entry consts of a name/id and a value. Of which is abstract.
   * 
   */
  class Table {
   public:
    Table(std::string name);

    /**
     * @brief Create a Entry object
     * 
     * @param name 
     * @return std::shared_ptr<Entry> 
     */
    std::shared_ptr<Entry> createEntry(std::string name);


    /**
     * @brief Get the Entry object, Will create one if it doesn't exist
     * 
     * @param name 
     * @return std::shared_ptr<Entry> 
     */
    std::shared_ptr<Entry> getEntry(std::string name);
    
    /**
     * @brief Get the Size of the table, (number of entries)
     * 
     * @return int 
     */
    int getSize();

    /**
     * @brief Get the Name of the table
     * 
     * @return std::string 
     */
    std::string getName();

    /**
     * @brief Get the Entry Names
     * 
     * @return std::vector<std::string> 
     */
    std::vector<std::string> getEntryNames();

    /**
     * @brief Get vector of existing entries
     * 
     * @return std::vector<std::shared_ptr<Entry>> 
     */
    std::vector<std::shared_ptr<Entry>> getEntries();

   private:
    std::string _name;
    std::vector<std::shared_ptr<Entry>> _entries;
  };
}
}

#endif