#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H
#include <iostream>
#include <unordered_map>
#include <memory>
#include "symbol.h"


class Symbol_table{
  public:
    std::shared_ptr<Symbol> lookup (const std::string& name);
    bool insert(std::shared_ptr<Symbol> sym);
    friend std::ostream& operator<<(std::ostream& os, const Symbol_table&);
  private:
    std::unordered_map<std::string, std::shared_ptr<Symbol>> symbols;
};
#endif
