#ifndef COMMBUS_Models_H
#define COMMBUS_Models_H

#include "Table.h"

namespace CommBus {
namespace Models {


  /**
   * @brief Create a data Models. Consisting of tables, each with entries
   * 
   */
  class Model {
   public:
    /**
     * @brief Create a Table object
     * 
     * @param name 
     * @return std::shared_ptr<Table> 
     */
    std::shared_ptr<Table> createTable(std::string name);

    /**
     * @brief Get the Table object (creates a table if it doesn't exist)
     * 
     * @param name 
     * @return std::shared_ptr<Table> 
     */
    std::shared_ptr<Table> getTable(std::string name);

    /**
     * @brief Get the Table Names
     * 
     * @return std::vector<std::string> 
     */
    std::vector<std::string> getTableNames();
    
    /**
     * @brief Get the Size of the model, (number of tables)
     * 
     * @return int 
     */
    int getSize();

    /**
     * @brief Get vector of existing tables
     * 
     * @return std::vector<std::shared_ptr<Table>> 
     */
    std::vector<std::shared_ptr<Table>> getTables();
   private:
    const std::string _name = "root";
    std::vector<std::shared_ptr<Table>> _tables;
  };
}
}

#endif