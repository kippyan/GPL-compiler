#include "Variable.h"
#include "error.h"
#include "Expression.h"
#include "Constant.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Textbox.h"
#include "Triangle.h"
#include "Pixmap.h"
#include <iostream>
#include <string>
//Todd's general approach to initialization lists:
//first pass: every member variable
//second pass: the world may never know

Variable::Variable(std::shared_ptr<Symbol> sym)
  : symbol(sym), array_index_expression(nullptr) {}

Variable::Variable(std::shared_ptr<Symbol> sym, Expression* arridx)
  : symbol(sym), array_index_expression(arridx) {}

Constant* Variable::evaluate(){
  delete evaluated_constant;
  if(symbol->is_array()){
    Constant* cindex = array_index_expression->evaluate();
    int index = 0;
    try{
      index = cindex->as_int();
    }catch(...){
      try{
        cindex->as_double();
        Error::error(Error::ARRAY_INDEX_MUST_BE_AN_INTEGER, symbol->get_name(), "A double expression");
      }catch(...){
        Error::error(Error::ARRAY_INDEX_MUST_BE_AN_INTEGER, symbol->get_name(), "A string expression");
      }
      evaluated_constant = new Integer_constant(0);
      return evaluated_constant;
    }
    if(index < 0 || index > symbol->get_count()-1){
      Error::error(Error::ARRAY_INDEX_OUT_OF_BOUNDS, symbol->get_name() , std::to_string(index));
      evaluated_constant = new Integer_constant(0);
      delete array_index_expression;
      return evaluated_constant;
    }
    delete array_index_expression;
    switch(symbol->get_type() ^ ARRAY){ 
      case INT:
      {
        evaluated_constant = new Integer_constant(symbol->as_int(index));
        return evaluated_constant;
      }
      case DOUBLE:
      {
        evaluated_constant = new Double_constant(symbol->as_double(index));
        return evaluated_constant;
      }
      case STRING:
      {
        evaluated_constant = new String_constant(symbol->as_string(index));
        return evaluated_constant;
      }
      case RECTANGLE:
      {
        evaluated_constant = new Rectangle_constant(symbol->as_Rectangle(index));
        return evaluated_constant;
      }
      case CIRCLE:
      {
        evaluated_constant = new Circle_constant(symbol->as_Circle(index));
        return evaluated_constant;
      }
      case TEXTBOX:
      {
        evaluated_constant = new Textbox_constant(symbol->as_Textbox(index));
        return evaluated_constant;
      }
      case TRIANGLE:
      {
        evaluated_constant = new Triangle_constant(symbol->as_Triangle(index));
        return evaluated_constant;
      }
      case PIXMAP:
      {
        evaluated_constant = new Pixmap_constant(symbol->as_Pixmap(index));
        return evaluated_constant;
      }
      default:
      {
        std::cerr << "Invalid variable type " << gpl_type_to_string(symbol->get_type()) << " detected\n";
        evaluated_constant = new Integer_constant(0);
        return evaluated_constant;
      }
    }
  }else{
    switch(symbol->get_type()){
      case INT:
        evaluated_constant = new Integer_constant(symbol->as_int());
        return evaluated_constant;
        break;
      case DOUBLE:
        evaluated_constant = new Double_constant(symbol->as_double());
        return evaluated_constant;
        break;
      case STRING:
        evaluated_constant = new String_constant(symbol->as_string());
        return evaluated_constant;
        break;
      case RECTANGLE:
        evaluated_constant = new Rectangle_constant(symbol->as_Rectangle());
        return evaluated_constant;
        break;
      case CIRCLE:
        evaluated_constant = new Circle_constant(symbol->as_Circle());
        return evaluated_constant;
        break;
      case TEXTBOX:
        evaluated_constant = new Textbox_constant(symbol->as_Textbox());
        return evaluated_constant;
        break;
      case TRIANGLE:
        evaluated_constant = new Triangle_constant(symbol->as_Triangle());
        return evaluated_constant;
        break;
      case PIXMAP:
        evaluated_constant = new Pixmap_constant(symbol->as_Pixmap());
        return evaluated_constant;
        break;
      default:
        break;
    }
  }
  evaluated_constant = new Integer_constant(0);
  return evaluated_constant;
}

Gpl_type Variable::type() const{
  return symbol->get_type();
}

