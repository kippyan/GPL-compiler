#include <iostream>
#include "Member_variable.h"

Member_variable::Member_variable(std::shared_ptr<Symbol> sym, const std::string& name)
  :Variable(sym), data_member_name(name) {}

Member_variable::Member_variable(std::shared_ptr<Symbol> sym, Expression* index_exp, const std::string& name)
  :Variable(sym, index_exp), data_member_name(name) {}

Gpl_type Member_variable::type() const
{
  switch((symbol->is_array() ? symbol->get_type() ^ ARRAY : symbol->get_type()))
  {
    case RECTANGLE:
      return Rectangle::get_member_variable_type(data_member_name);
      break;
    case CIRCLE:
      return Circle::get_member_variable_type(data_member_name);
      break;
    case TEXTBOX:
      return Textbox::get_member_variable_type(data_member_name);
      break;
    case TRIANGLE:
      return Triangle::get_member_variable_type(data_member_name);
      break;
    case PIXMAP:
      return Pixmap::get_member_variable_type(data_member_name);
      break;
    default:
      std::cerr << "error: data type has no member variables!\n"; 
      return INT;
      break;
  }
}

Constant* Member_variable::evaluate()
{
  Game_object* gop = nullptr;
  if(array_index_expression){
    int index = 0;
    try{ 
      index = array_index_expression->evaluate()->as_int();
    }catch(Gpl_type thrown){
      switch(thrown){
        case DOUBLE: 
          Error::error(Error::ARRAY_INDEX_MUST_BE_AN_INTEGER, data_member_name, "a double expression");
          break;
        case STRING: 
        Error::error(Error::ARRAY_INDEX_MUST_BE_AN_INTEGER, data_member_name, "a string expression");
          break;
        /*case animation_block: 
        Error::error(Error::array_index_must_be_an_integer, *$1, "an animation_block expression");
          break;*/
        default:
          std::cerr << "very invalid array index type\n";
      }   
    }
    if(index < 0 || index > symbol->get_count() - 1){
      Error::error(Error::ARRAY_INDEX_OUT_OF_BOUNDS, symbol->get_name(), std::to_string(index));
      index = 0;
    }
    switch(symbol->get_type() ^ ARRAY)
    {
      case RECTANGLE:   gop = symbol->as_Rectangle(index);   break;
      case CIRCLE:      gop = symbol->as_Circle(index);      break;
      case TEXTBOX:     gop = symbol->as_Textbox(index);     break;
      case TRIANGLE:    gop = symbol->as_Triangle(index);    break;
      case PIXMAP:      gop = symbol->as_Pixmap(index);      break;
      default: std::cerr << "invalid typem_v:eval\n"; break;
    }
  }else{
    switch(symbol->get_type())
    {
      case RECTANGLE:   gop = symbol->as_Rectangle();   break;
      case CIRCLE:      gop = symbol->as_Circle();      break;
      case TEXTBOX:     gop = symbol->as_Textbox();     break;
      case TRIANGLE:    gop = symbol->as_Triangle();    break;
      case PIXMAP:      gop = symbol->as_Pixmap();      break;
      default: std::cerr << "invalid type(m_v:eval)\n"; break;
    }
  }
  int val;
  double val2;
  std::string val3;
  //Animation_block val4;
  switch(this->type())
  {
    case INT:
      gop->get_member_variable(data_member_name, val);
      return new Integer_constant(val);
      break;
    case DOUBLE:
      gop->get_member_variable(data_member_name, val2);
      return new Double_constant(val2);
      break;
    case STRING:
      gop->get_member_variable(data_member_name, val3);
      return new String_constant(val3);
      break;
    /*case ANIMATION_BLOCK:
      gop->get_member_variable(data_member_name, val4);
      return new Animation_block_constant(val4);
      break;*/
    default:
      std::cerr << "bad member variable type in evaluate\n";
  }
  std::cerr << "m_v reached end of function for some reason\n";
  return new Integer_constant(0);
}
