#ifndef SYMBOL_H
#define SYMBOL_H
#include <iostream>
#include "gpl_type.h"

union symbol_type{
  double* double_pointer;
  int* int_pointer;
  std::string* string_pointer;
  symbol_type(int* val) : int_pointer(val){}
  symbol_type(double* val) : double_pointer(val){}
  symbol_type(std::string* val) : string_pointer(val){}
};
class Symbol{
  public:
    Symbol(const std::string& name, double* value); 
    Symbol(const std::string& name, double* value, int count); 
    Symbol(const std::string& name, int* val); 
    Symbol(const std::string& name, int* val, int count); 
    Symbol(const std::string& name, std::string* val); 
    Symbol(const std::string& name, std::string* val, int count); 
    ~Symbol();
    Gpl_type get_type();
    std::string get_name();
    int get_count();
    bool is_array();
    int int_at(int index);
    double double_at(int index);
    std::string string_at(int index);
    friend std::ostream& operator<<(std::ostream& os, const Symbol&); 
  private:
    std::string name; //the name of the variable
    symbol_type value; //the contents of the variable
    Gpl_type type; //the type of the variable. See gpl_type.h
    int count; //used to store the size if array
};

#endif
