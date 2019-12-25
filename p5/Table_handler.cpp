#include <iostream>
#include <stdexcept>
#include "Table_handler.h"
#include "error.h"
Table_handler& Table_handler::instance(){
  static Table_handler the_instance;
  if(the_instance.tables.empty())
    the_instance.push_table();
  return the_instance;
}

void Table_handler::push_table(){
  std::shared_ptr<Symbol_table> atable;
  atable = std::make_shared<Symbol_table>();
  tables.push_back(atable);
}

void Table_handler::pop_table(){
  if(tables.size() > 0){
    tables.pop_back();
  }else{
    throw std::underflow_error("Can't pop global symbol table");
  }
}
bool Table_handler::insert(std::shared_ptr<Symbol> sym){
  int size = tables.size();
  if(size > 0){
    return tables[size - 1]->insert(sym);
  }else{
    std::cerr << "super bad happen in handler insert\n";
  }
  return false;
}

std::shared_ptr<Symbol> Table_handler::lookup(const std::string& name){
  int size = tables.size();
  for(int i = size-1; i >= 0; i--){
    std::shared_ptr<Symbol> sym = tables[i]->lookup(name);
    if(sym)
      return sym;
  }
  return nullptr;
}

bool Table_handler::defined_in_current_scope(const std::string& name){
  int size = tables.size();
  std::shared_ptr<Symbol> sym = tables[size-1]->lookup(name);
  if(sym) 
    return true; 
  else 
    return false;
}

std::ostream& operator<<(std::ostream& os, Table_handler& sh){
  int size = sh.tables.size();
  for(int i = size-1; i >= 0; i--){
    os << *sh.tables[i];
  }
  return os;
}
