#include <iostream>
#include "Symbol.h"

Symbol::Symbol(const std::string& n, int* v)//for int solo
    :name(n), value(v), type(INT), count(-1) {} 
Symbol::Symbol(const std::string& n, int* v, int c) //for int array
    :name(n), value(v), type(INT_ARRAY), count(c) {}
Symbol::Symbol(const std::string& n, double* v) //for double solo 
    :name(n), value(v), type(DOUBLE), count(-1) {} 
Symbol::Symbol(const std::string& n, double* v, int c) //for double array
    :name(n), value(v), type(DOUBLE_ARRAY), count(c) {} 
Symbol::Symbol(const std::string& n, std::string* v) //for string solo
    :name(n), value(v), type(STRING), count(-1) {} 
Symbol::Symbol(const std::string& n, std::string* v, int c) //for string array
    :name(n), value(v), type(STRING_ARRAY), count(c) {} 

Symbol::~Symbol(){
  if(type == INT)
    delete value.int_pointer;
  else if(type == DOUBLE)
    delete value.double_pointer;
  else if(type == STRING)
    delete value.string_pointer;
  else if(type == INT_ARRAY)
    delete[] value.int_pointer;
  else if(type == DOUBLE_ARRAY)
    delete[] value.double_pointer;
  else if(type == STRING_ARRAY)
    delete[] value.string_pointer;
}
Gpl_type Symbol::get_type(){
  return type;
}

std::string Symbol::get_name(){
  return name;
}

int Symbol::get_count(){
  if(type < 1024)
    return -1;
  return count;
}

bool Symbol::is_array(){
  return type & ARRAY;
}

int Symbol::int_at(int index){
  if(type < 1024)
    return *value.int_pointer;
  return value.int_pointer[index];
}
double Symbol::double_at(int index){
  if(type < 1024)
    return *value.double_pointer;
  return value.double_pointer[index];
}
std::string Symbol::string_at(int index){
  if(type < 1024)
    return *value.string_pointer;
  return value.string_pointer[index];
}

std::ostream& operator<<(std::ostream& os, const Symbol& sym){
  if(sym.type == INT){
    os << "int " << sym.name << " = " << *sym.value.int_pointer << '\n'; 
  }else if(sym.type == DOUBLE){
    os << "double " << sym.name << " = " << *sym.value.double_pointer << '\n';
  }else if(sym.type == STRING){
    os << "string " << sym.name << " = \"" << *sym.value.string_pointer << "\"\n";
  }else if(sym.type == INT_ARRAY){
    for(int i = 0; i < sym.count; i++)
      os << "int " << sym.name << '[' << i << ']' << " = " << sym.value.int_pointer[i] << '\n';
  }else if(sym.type == DOUBLE_ARRAY){
    for(int i = 0; i < sym.count; i++)
      os << "double " << sym.name << '[' << i << ']' << " = " << sym.value.double_pointer[i] << '\n';
  }else if(sym.type == STRING_ARRAY){
    for(int i = 0; i < sym.count; i++)
      os << "string " << sym.name << '[' << i << ']' << " = \"" << sym.value.string_pointer[i] << "\"\n";
  }else{
    os << "bad happen: << operator error";
  }return os;
}
