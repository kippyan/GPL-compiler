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
    Symbol(const std::string& name, double* value); //for double solo
    Symbol(const std::string& name, double* value, int count); //for double array
    Symbol(const std::string& name, int* val); //for int solo
    Symbol(const std::string& name, int* val, int count); //for int array
    Symbol(const std::string& name, std::string* val); //for string solo
    Symbol(const std::string& name, std::string* val, int count); //for string array
    ~Symbol();
    Gpl_type get_type();
    std::string get_name();
    friend std::ostream& operator<<(std::ostream& os, const Symbol&); //enigmatic
  private:
    std::string name; //the name of the variable
    symbol_type value; //the contents of the variable
    Gpl_type type; //the type of the variable. See gpl_type.h
    int count; //used to store the size if the variable is an array
};

#endif
