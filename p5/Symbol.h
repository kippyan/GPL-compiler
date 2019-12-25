#ifndef SYMBOL_H
#define SYMBOL_H
#include <iostream>
#include "gpl_type.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Textbox.h"
#include "Triangle.h"
#include "Pixmap.h"
#include "Animation_block.h"

union symbol_type{
  double* double_pointer;
  int* int_pointer;
  std::string* string_pointer;
  Rectangle* rectangle_pointer;
  Circle* circle_pointer;
  Textbox* textbox_pointer;
  Triangle* triangle_pointer;
  Pixmap* pixmap_pointer;
  Animation_block* animation_block_pointer;

  symbol_type(int* val) : int_pointer(val){}
  symbol_type(double* val) : double_pointer(val){}
  symbol_type(std::string* val) : string_pointer(val){}
  symbol_type(Rectangle* val) : rectangle_pointer(val){}
  symbol_type(Circle* val) : circle_pointer(val){}
  symbol_type(Textbox* val) : textbox_pointer(val){}
  symbol_type(Triangle* val) : triangle_pointer(val){}
  symbol_type(Pixmap* val) : pixmap_pointer(val){}
  symbol_type(Animation_block* val) : animation_block_pointer(val){}
};
class Symbol{
  public:
    Symbol(const std::string& name, double* value); 
    Symbol(const std::string& name, double* value, int count); 
    Symbol(const std::string& name, int* val); 
    Symbol(const std::string& name, int* val, int count); 
    Symbol(const std::string& name, std::string* val); 
    Symbol(const std::string& name,std::string* val,int count);
    Symbol(const std::string& name, Rectangle* val); 
    Symbol(const std::string& name, Rectangle* val, int count);
    Symbol(const std::string& name, Circle* val); 
    Symbol(const std::string& name, Circle* val, int count); 
    Symbol(const std::string& name, Textbox* val); 
    Symbol(const std::string& name, Textbox* val, int count); 
    Symbol(const std::string& name, Triangle* val); 
    Symbol(const std::string& name, Triangle* val, int count); 
    Symbol(const std::string& name, Pixmap* val); 
    Symbol(const std::string& name, Pixmap* val, int count); 
    Symbol(const std::string& name, Animation_block* val); 
    ~Symbol();
    Gpl_type    get_type();
    std::string get_name();
    int         get_count();
    bool        is_array();

    int&         as_int();
    double&      as_double();
    std::string& as_string();
    Rectangle*&  as_Rectangle();
    Circle*&     as_Circle();
    Textbox*&    as_Textbox();
    Triangle*&   as_Triangle();
    Pixmap*&     as_Pixmap();
    Animation_block*& as_Animation_block();
    int&         as_int(int);
    double&      as_double(int);
    std::string& as_string(int);
    Rectangle*&  as_Rectangle(int);
    Circle*&     as_Circle(int);
    Textbox*&    as_Textbox(int);
    Triangle*&   as_Triangle(int);
    Pixmap*&     as_Pixmap(int);
    
    friend std::ostream& operator<<(std::ostream& os, const Symbol&); 
  private:
    std::string name;
    symbol_type value;
    Gpl_type type;
    int count; 
};

#endif
