#include "Variable.h"
#include "error.h"
#include "Expression.h"
#include "Constant.h"
#include <iostream>
#include <string>
//Todd's general approach to initialization lists:
//first pass: every member variable
//second pass: the world may never know

Variable::Variable(std::shared_ptr<Symbol> sym)
  : symbol(sym), array_index_expression(nullptr)
{
  
}
Variable::Variable(std::shared_ptr<Symbol> sym, Expression* arridx)
  : symbol(sym), array_index_expression(arridx)
{

}

Constant* Variable::evaluate(){
  delete evaluated_constant;
  //std::cout << "in var eval\n";
  if(symbol->is_array()){
    //std::cout << "passed in_array\n";
    Constant* cindex = array_index_expression->evaluate();
    //std::cout << "cindex evaluated\n";
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
        evaluated_constant = new Integer_constant(symbol->int_at(index));
        return evaluated_constant;
      }
      case DOUBLE:
      {
        evaluated_constant = new Double_constant(symbol->double_at(index));
        return evaluated_constant;
      }
      case STRING:
      {
        evaluated_constant = new String_constant(symbol->string_at(index));
        return evaluated_constant;
      }
      default:
      {
        std::cerr << "Invalid variable type " << symbol->get_type() << " detected\n";
        evaluated_constant = new Integer_constant(0);
        return evaluated_constant;
      }
    }
  }else{
    switch(symbol->get_type()){
      case INT:
      {
        evaluated_constant = new Integer_constant(symbol->int_at(1));
        return evaluated_constant;
      }
      case DOUBLE:
      {
        evaluated_constant = new Double_constant(symbol->double_at(1));
        return evaluated_constant;
      }
      case STRING:
      {
        evaluated_constant = new String_constant(symbol->string_at(1));
        return evaluated_constant;
      }
      default:
      {
      }
    }
  }
  evaluated_constant = new Integer_constant(0);
  return evaluated_constant;
}

Gpl_type Variable::type() const{
  return symbol->get_type();
}

