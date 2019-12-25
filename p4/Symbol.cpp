#include <iostream>
#include "Symbol.h"

Symbol::Symbol(const std::string& n, int* v)
    :name(n), value(v), type(INT), count(-1) {} 
Symbol::Symbol(const std::string& n, int* v, int c)
    :name(n), value(v), type(INT_ARRAY), count(c) {}
Symbol::Symbol(const std::string& n, double* v)
    :name(n), value(v), type(DOUBLE), count(-1) {} 
Symbol::Symbol(const std::string& n, double* v, int c)
    :name(n), value(v), type(DOUBLE_ARRAY), count(c) {} 
Symbol::Symbol(const std::string& n, std::string* v)
    :name(n), value(v), type(STRING), count(-1) {} 
Symbol::Symbol(const std::string& n, std::string* v, int c)
    :name(n), value(v), type(STRING_ARRAY), count(c) {} 
Symbol::Symbol(const std::string& n, Rectangle* v)
    :name(n), value(v), type(RECTANGLE), count(-1) {}
Symbol::Symbol(const std::string& n, Rectangle* v, int c)
    :name(n), value(v), type(RECTANGLE_ARRAY), count(c) {}  
Symbol::Symbol(const std::string& n, Circle* v)
    :name(n), value(v), type(CIRCLE), count(-1) {}
Symbol::Symbol(const std::string& n, Circle* v, int c)
    :name(n), value(v), type(CIRCLE_ARRAY), count(c) {}
Symbol::Symbol(const std::string& n, Textbox* v)
    :name(n), value(v), type(TEXTBOX), count(-1) {}
Symbol::Symbol(const std::string& n, Textbox* v, int c)
    :name(n), value(v), type(TEXTBOX_ARRAY), count(c) {}
Symbol::Symbol(const std::string& n, Triangle* v)
    :name(n), value(v), type(TRIANGLE), count(-1) {}
Symbol::Symbol(const std::string& n, Triangle* v, int c)
    :name(n), value(v), type(TRIANGLE_ARRAY),  count(c) {}
Symbol::Symbol(const std::string& n, Pixmap* v)
    :name(n), value(v), type(PIXMAP), count(-1) {}
Symbol::Symbol(const std::string& n, Pixmap* v, int c)
    :name(n), value(v), type(PIXMAP_ARRAY), count(c) {}
Symbol::Symbol(const std::string& n, Animation_block* v)
    :name(n), value(v), type(ANIMATION_BLOCK) {}

Symbol::~Symbol(){
  if(type == INT)
    delete value.int_pointer;
  else if(type == DOUBLE)
    delete value.double_pointer;
  else if(type == STRING)
    delete value.string_pointer;
  else if(type == RECTANGLE)
    delete value.rectangle_pointer;
  else if(type == CIRCLE)
    delete value.circle_pointer;
  else if(type == TEXTBOX)
    delete value.textbox_pointer;
  else if(type == TRIANGLE)
    delete value.triangle_pointer;
  else if(type == PIXMAP)
    delete value.pixmap_pointer;
  else if(type == ANIMATION_BLOCK)
    delete value.animation_block_pointer;
  else if(type == INT_ARRAY)
    delete[] value.int_pointer;
  else if(type == DOUBLE_ARRAY)
    delete[] value.double_pointer;
  else if(type == STRING_ARRAY)
    delete[] value.string_pointer;
  else if(type == RECTANGLE_ARRAY)
    delete[] value.rectangle_pointer;
  else if(type == CIRCLE_ARRAY)
    delete[] value.circle_pointer;
  else if(type == TEXTBOX_ARRAY)
    delete[] value.textbox_pointer;
  else if(type == TRIANGLE_ARRAY)
    delete[] value.triangle_pointer;
  else if(type == PIXMAP_ARRAY)
    delete[] value.pixmap_pointer;
}

Gpl_type Symbol::get_type(){
  return type;
}

std::string Symbol::get_name(){
  return name;
}

int Symbol::as_int() const
    {return *value.int_pointer;}
double Symbol::as_double() const
    {return *value.double_pointer;}
std::string Symbol::as_string() const
    {return *value.string_pointer;}
Rectangle* Symbol::as_Rectangle() const
    {return value.rectangle_pointer;}
Circle* Symbol::as_Circle() const
    {return value.circle_pointer;}
Textbox* Symbol::as_Textbox() const
    {return value.textbox_pointer;}
Triangle* Symbol::as_Triangle() const
    {return value.triangle_pointer;}
Pixmap* Symbol::as_Pixmap() const
    {return value.pixmap_pointer;}
Animation_block* Symbol::as_Animation_block() const
    {return value.animation_block_pointer;}
int Symbol::as_int(int i) const
    {return *(value.int_pointer + i);}
double Symbol::as_double(int i) const
    {return *(value.double_pointer + i);}
std::string Symbol::as_string(int i) const
    {return *(value.string_pointer + i);}
Rectangle* Symbol::as_Rectangle(int i) const
    {return (value.rectangle_pointer + i);}
Circle* Symbol::as_Circle(int i) const
    {return (value.circle_pointer + i);}
Textbox* Symbol::as_Textbox(int i) const
    {return (value.textbox_pointer + i);}
Triangle* Symbol::as_Triangle(int i) const
    {return (value.triangle_pointer + i);}
Pixmap* Symbol::as_Pixmap(int i) const
    {return (value.pixmap_pointer + i);}

int Symbol::get_count(){
  return (type & ARRAY) ? count : -1;
}

bool Symbol::is_array(){
  return type & ARRAY;
}

std::ostream& operator<<(std::ostream& os, const Symbol& sym){
  if(sym.type & INT){
    os << "int " << sym.name << " = " << *sym.value.int_pointer << '\n'; 
  }else if(sym.type == DOUBLE){
    os << "double " << sym.name << " = " << *sym.value.double_pointer << '\n';
  }else if(sym.type == STRING){
    os << "string " << sym.name << " = \"" << *sym.value.string_pointer << "\"\n";
  }else if(sym.type == RECTANGLE){
    os << "rectangle " << sym.name  << *sym.value.rectangle_pointer << "\n";
  }else if(sym.type == CIRCLE){
    os << "circle " << sym.name << *sym.value.circle_pointer << "\n";
  }else if(sym.type == TEXTBOX){
    os << "textbox " << sym.name << *sym.value.textbox_pointer << "\n";
  }else if(sym.type == TRIANGLE){
    os << "triangle " << sym.name << *sym.value.triangle_pointer << "\n";
  }else if(sym.type == PIXMAP){
    os << "pixmap " << sym.name << *sym.value.pixmap_pointer << "\n";
  }else if(sym.type == ANIMATION_BLOCK){
    os << "animation_block " << sym.name << '\n';
  }else if(sym.type == INT_ARRAY){
    for(int i = 0; i < sym.count; i++)
      os << "int " << sym.name << '[' << i << ']'  << sym.value.int_pointer[i] << '\n';
  }else if(sym.type == DOUBLE_ARRAY){
    for(int i = 0; i < sym.count; i++)
      os << "double " << sym.name << '[' << i << ']' << sym.value.double_pointer[i] << '\n';
  }else if(sym.type == STRING_ARRAY){
    for(int i = 0; i < sym.count; i++)
      os << "string " << sym.name << '[' << i << ']' << sym.value.string_pointer[i] << "\n";
  }else if(sym.type == RECTANGLE_ARRAY){
    for(int i = 0; i < sym.count; i++)
      os << "rectangle " << sym.name << '[' << i << ']' << *(sym.value.rectangle_pointer + i) << "\n";
  }else if(sym.type == CIRCLE_ARRAY){
    for(int i = 0; i < sym.count; i++)
      os << "circle " << sym.name << '[' << i << ']' << *(sym.value.circle_pointer + i) << "\n";
  }else if(sym.type == TEXTBOX_ARRAY){
    for(int i = 0; i < sym.count; i++)
      os << "textbox " << sym.name << '[' << i << ']' << *(sym.value.textbox_pointer + i) << "\n";
  }else if(sym.type == TRIANGLE_ARRAY){
    for(int i = 0; i < sym.count; i++)
      os << "triangle " << sym.name << '[' << i << ']' << *(sym.value.triangle_pointer + i) << "\n";
  }else if(sym.type == PIXMAP_ARRAY){
    for(int i = 0; i < sym.count; i++)
      os << "pixmap " << sym.name << '[' << i << ']' << *(sym.value.pixmap_pointer + i) << "\n";
  }else{
    os << "bad happen: symbol << operator error";
  }return os;
}
