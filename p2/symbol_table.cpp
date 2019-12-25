#include <iostream>
#include <vector>
#include <algorithm>
//#include "symbol.h"
#include "symbol_table.h"

std::shared_ptr<Symbol> Symbol_table::lookup (const std::string& name){
  auto it = symbols.find(name);
  if(it != symbols.end())
    return it->second; 
  else
    return nullptr;
}
bool Symbol_table::insert(std::shared_ptr<Symbol> sym){
  if(symbols.find(sym->get_name()) == symbols.end()){ 
    symbols[sym->get_name()] = sym;
    return true;
  }else{
    return false;
  }
}
std::ostream& operator<<(std::ostream& os, const Symbol_table& st){
  std::shared_ptr<Symbol> sym;
  std::vector<std::string> names;
  for(auto i : st.symbols){//0 IQ for loop
    names.push_back(i.first);
  }
  std::sort(names.begin(), names.end());
  for(int i = 0; i < (int)names.size(); i++){
    os << *st.symbols.at(names[i]);//-5 iq for loop
  }
  return os;
}

