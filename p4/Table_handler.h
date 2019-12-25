#ifndef TABLE_HANDLER_H
#define TABLE_HANDLER_H
#include <iostream>
#include <vector>
#include "Symbol_table.h"

class Table_handler{
 public:
  static Table_handler& instance();
  void push_table();
  void pop_table();
  bool insert(std::shared_ptr<Symbol> sym);
  std::shared_ptr<Symbol> lookup(const std::string& name);
  bool defined_in_current_scope(const std::string& name);
  friend std::ostream& operator<<(std::ostream& os, Table_handler& sh);
 private:
  Table_handler(): tables(){};
  std::vector<std::shared_ptr<Symbol_table>> tables;
};

#endif
