// File: Expression.cpp
#include "Expression.h"
#include "Constant.h"
#include "error.h"
#include <string>
#include <cmath>
#include <iostream>
/**********************************************/
/************* Other operators ****************/
/**********************************************/
Expression::~Expression(){delete evaluated_constant;}

Constant* Unary_operator::ret(Constant* cp){
  delete evaluated_constant;
  return evaluated_constant = cp;
}

Gpl_type Plus::type() const
{
  Gpl_type lht = lhs->type();
  Gpl_type rht = rhs->type();
  if(lht == STRING || rht == STRING)
    return STRING;
  if(lht == DOUBLE || rht == DOUBLE)
    return DOUBLE;
  //if(lht == INT || rht == INT)
    return INT;
}
Constant* Plus::evaluate()
{
  delete evaluated_constant;
  //std::cout << "in plus::evaluate\n";
  Constant* lhs_constant = lhs->evaluate();
  Constant* rhs_constant = rhs->evaluate();
  try{
    evaluated_constant = new Integer_constant(lhs_constant->as_int() + rhs_constant->as_int());
  }catch(...){ 
    try{
      evaluated_constant = new Double_constant(lhs_constant->as_double() + rhs_constant->as_double());
    }catch(...){
      evaluated_constant = new String_constant(lhs_constant->as_string() + rhs_constant->as_string()); 
    }
  }
  return evaluated_constant; 
}

Gpl_type Minus::type() const
{
  Gpl_type lht = lhs->type();
  Gpl_type rht = rhs->type();
  if(lht == STRING || rht == STRING)
    return INT;
  if(lht == DOUBLE || rht == DOUBLE)
    return DOUBLE;
  //if(lht == INT || rht == INT)
    return INT;
}
Constant* Minus::evaluate()
{
  delete evaluated_constant;
  //std::cout << "in minus::evaluate\n";
  Constant* lhs_constant = lhs->evaluate();
  Constant* rhs_constant = rhs->evaluate();
  try{
    evaluated_constant = new Integer_constant(lhs_constant->as_int() - rhs_constant->as_int());
  }catch(...){ 
    evaluated_constant = new Double_constant(lhs_constant->as_double() - rhs_constant->as_double());
  }
  return evaluated_constant; 
}

Gpl_type Multiply::type() const{
  Gpl_type lht = lhs->type();
  Gpl_type rht = rhs->type();
  if(lht == STRING || rht == STRING)
    return INT;
  if(lht == DOUBLE || rht == DOUBLE)
    return DOUBLE;
  //if(lht == INT || rht == INT)
    return INT;
}
Constant* Multiply::evaluate()
{
  delete evaluated_constant;
  //std::cout << "in multiply::evaluate\n";
  Constant* lhs_constant = lhs->evaluate();
  Constant* rhs_constant = rhs->evaluate();
  try{
    evaluated_constant = new Integer_constant(lhs_constant->as_int() * rhs_constant->as_int());
  }catch(...){
      evaluated_constant = new Double_constant(lhs_constant->as_double() * rhs_constant->as_double());
  }
  return evaluated_constant; 
}

Gpl_type Divide::type() const{
  Gpl_type lht = lhs->type();
  Gpl_type rht = rhs->type();
  if(lht == STRING || rht == STRING)
    return INT;
  if(lht == DOUBLE || rht == DOUBLE)
    return DOUBLE;
  //if(lht == INT || rht == INT)
    return INT;
}
Constant* Divide::evaluate()
{
  delete evaluated_constant;
  //std::cout << "in divide::evaluate\n";
  Constant* lhs_constant = lhs->evaluate();
  Constant* rhs_constant = rhs->evaluate();
  delete evaluated_constant;
  try{
    evaluated_constant = new Integer_constant(lhs_constant->as_int() / rhs_constant->as_int());
  }catch(...){
    evaluated_constant = new Double_constant(lhs_constant->as_double() / rhs_constant->as_double());
  }
  return evaluated_constant; 
}

Gpl_type Mod::type() const{
  return INT;
}
Constant* Mod::evaluate()
{
  delete evaluated_constant;
  //std::cout << "in mod::evaluate\n";
  Constant* lhs_constant = lhs->evaluate();
  Constant* rhs_constant = rhs->evaluate();
  delete evaluated_constant;
  evaluated_constant = new Integer_constant(lhs_constant->as_int() % rhs_constant->as_int());
  return evaluated_constant;
}

Gpl_type And::type() const{
  return INT;
}
Constant* And::evaluate()
{
  delete evaluated_constant;
  //std::cout << "in and::evaluate\n";
  Constant* lhs_constant = lhs->evaluate();
  Constant* rhs_constant = rhs->evaluate();
  try{
    evaluated_constant = new Integer_constant(lhs_constant->as_int() && rhs_constant->as_int());
  }catch(...){
    evaluated_constant = new Integer_constant(lhs_constant->as_double() && rhs_constant->as_double());
  }
  return evaluated_constant; 
}

Gpl_type Or::type() const{
  return INT;
}
Constant* Or::evaluate()
{
  delete evaluated_constant;
  //std::cout << "in or::evaluate\n";
  Constant* lhs_constant = lhs->evaluate();
  Constant* rhs_constant = rhs->evaluate();
  try{
    evaluated_constant = new Integer_constant(lhs_constant->as_int() || rhs_constant->as_int());
  }catch(...){
    evaluated_constant = new Integer_constant(lhs_constant->as_double() || rhs_constant->as_double());
  }
  return evaluated_constant;
}

Gpl_type Less_than::type() const{
  return INT;
}
Constant* Less_than::evaluate()
{
  delete evaluated_constant;
  //std::cout << "in lessthan::evaluate\n";
  Constant* lhs_constant = lhs->evaluate();
  Constant* rhs_constant = rhs->evaluate();
  try{
    evaluated_constant = new Integer_constant(lhs_constant->as_int() < rhs_constant->as_int());
  }catch(...){
    try{
      evaluated_constant = new Integer_constant(lhs_constant->as_double() < rhs_constant->as_double());
    }catch(...){
      evaluated_constant = new Integer_constant(lhs_constant->as_string() < rhs_constant->as_string());
    }
  }
  return evaluated_constant;
}

Gpl_type Greater_than::type() const{
  return INT;
}
Constant* Greater_than::evaluate()
{
  delete evaluated_constant;
  //std::cout << "in greaterthan::evaluate\n";
  Constant* lhs_constant = lhs->evaluate();
  Constant* rhs_constant = rhs->evaluate();
  try{
    evaluated_constant = new Integer_constant(lhs_constant->as_int() > rhs_constant->as_int());
  }catch(...){
    try{
      evaluated_constant = new Integer_constant(lhs_constant->as_double() > rhs_constant->as_double());
    }catch(...){
      evaluated_constant = new Integer_constant(lhs_constant->as_string() > rhs_constant->as_string());
    }
  }
  return evaluated_constant;
}

Gpl_type Less_equal::type() const{
  return INT;
}
Constant* Less_equal::evaluate()
{
  delete evaluated_constant;
  //std::cout << "in lessequal::evaluate\n";
  Constant* lhs_constant = lhs->evaluate();
  Constant* rhs_constant = rhs->evaluate();
  try{
    evaluated_constant = new Integer_constant(lhs_constant->as_int() <= rhs_constant->as_int());
  }catch(...){
    try{
      evaluated_constant = new Integer_constant(lhs_constant->as_double() <= rhs_constant->as_double());
    }catch(...){
      evaluated_constant = new Integer_constant(lhs_constant->as_string() <= rhs_constant->as_string());
    }
  }
  return evaluated_constant;
}

Gpl_type Greater_equal::type() const
{
  return INT;
}
Constant* Greater_equal::evaluate()
{
  delete evaluated_constant;
  //std::cout << "in greaterequal::evaluate\n";
  Constant* lhs_constant = lhs->evaluate();
  Constant* rhs_constant = rhs->evaluate();
  try{
    evaluated_constant = new Integer_constant(lhs_constant->as_int() >= rhs_constant->as_int());
  }catch(...){
    try{
    evaluated_constant = new Integer_constant(lhs_constant->as_double() >= rhs_constant->as_double());
    }catch(...){
    evaluated_constant = new Integer_constant(lhs_constant->as_string() >= rhs_constant->as_string());
    }
  }
  return evaluated_constant;
}

Gpl_type Equal::type() const
{
  return INT;
}
Constant* Equal::evaluate()
{
  delete evaluated_constant;
  //std::cout << "in equal::evaluate\n";
  Constant* lhs_constant = lhs->evaluate();
  Constant* rhs_constant = rhs->evaluate();
  try{
    evaluated_constant = new Integer_constant(lhs_constant->as_int() == rhs_constant->as_int());
  }catch(...){
    try{
    evaluated_constant = new Integer_constant(lhs_constant->as_double() == rhs_constant->as_double());
    }catch(...){
    evaluated_constant = new Integer_constant(lhs_constant->as_string() == rhs_constant->as_string());
    }
  }
  return evaluated_constant;
}

Gpl_type Not_equal::type() const{
  return INT;
}
Constant* Not_equal::evaluate()
{
  delete evaluated_constant;
  //std::cout << "in notequal::evaluate\n";
  Constant* lhs_constant = lhs->evaluate();
  Constant* rhs_constant = rhs->evaluate();
  try{
    evaluated_constant = new Integer_constant(lhs_constant->as_int() != rhs_constant->as_int());
  }catch(...){
    try{
    evaluated_constant = new Integer_constant(lhs_constant->as_double() != rhs_constant->as_double());
    }catch(...){
    evaluated_constant = new Integer_constant(lhs_constant->as_string() != rhs_constant->as_string());
    }
  }
  return evaluated_constant;
}

Gpl_type Unary_minus::type() const{
  Gpl_type lht = lhs->type();
  if(lht == STRING)
    return INT;
  if(lht == DOUBLE)
    return DOUBLE;
  //if(lht == INT)
    return INT;
}
Constant* Unary_minus::evaluate()
{
  //std::cout << "in unaryminus::evaluate\n";
  Constant* lhs_constant = lhs->evaluate();
  try{
    lhs_constant = new Integer_constant(-lhs_constant->as_int());
  }catch(...){
    lhs_constant = new Double_constant(-lhs_constant->as_double());
  }
  return ret(lhs_constant);
}

Gpl_type Not::type() const{
  return INT;
}
Constant* Not::evaluate()
{
  //std::cout << "in not::evaluate\n";
  Constant* lhs_constant = lhs->evaluate();
  try{
    lhs_constant = new Integer_constant(!lhs_constant->as_int()); 
  }catch(...){
    lhs_constant= new Integer_constant(!lhs_constant->as_double()); 
  }
  return ret(lhs_constant);
}

Gpl_type Cosine::type() const{
  Gpl_type lht = lhs->type();
  if(lht == STRING)
    return INT;
  return DOUBLE;
}
Constant* Cosine::evaluate()
{
  //std::cout << "in cos::evaluate\n";
  Constant* lhs_constant = lhs->evaluate();
  lhs_constant= new Double_constant(cos(lhs_constant->as_double()*M_PI/180));
  return ret(lhs_constant);
}

Gpl_type Sine::type() const{
  Gpl_type lht = lhs->type();
  if(lht == STRING)
    return INT;
  return DOUBLE;
}
Constant* Sine::evaluate()
{
  //std::cout << "in sine::evaluate\n";
  Constant* lhs_constant = lhs->evaluate();
  lhs_constant = new Double_constant(sin(lhs_constant->as_double()*M_PI/180));
  return ret(lhs_constant);
}

Gpl_type Tan::type() const{
  Gpl_type lht = lhs->type();
  if(lht == STRING)
    return INT;
  return DOUBLE;
}
Constant* Tan::evaluate()
{
  //std::cout << "in tan::evaluate\n";
  Constant* lhs_constant = lhs->evaluate();
  lhs_constant= new Double_constant(tan(lhs_constant->as_double()*M_PI/180));
  return ret(lhs_constant);
}

Gpl_type Acos::type() const{
  Gpl_type lht = lhs->type();
  if(lht == STRING)
    return INT;
  return DOUBLE;
}
Constant* Acos::evaluate()
{
  //std::cout << "in acos::evaluate\n";
  Constant* lhs_constant = lhs->evaluate();
  lhs_constant= new Double_constant(acos(lhs_constant->as_double())/M_PI*180);
  return ret(lhs_constant);
}

Gpl_type Asin::type() const{
  Gpl_type lht = lhs->type();
  if(lht == STRING)
    return INT;
  return DOUBLE;
}
Constant* Asin::evaluate()
{
  //std::cout << "in asin::evaluate\n";
  Constant* lhs_constant = lhs->evaluate();
  lhs_constant= new Double_constant(asin(lhs_constant->as_double())/M_PI*180);
  return ret(lhs_constant);
}

Gpl_type Atan::type() const{
  Gpl_type lht = lhs->type();
  if(lht == STRING)
    return INT;
  return DOUBLE;
}
Constant* Atan::evaluate()
{
  //std::cout << "in atan::evaluate\n";
  Constant* lhs_constant = lhs->evaluate();
  lhs_constant= new Double_constant(atan(lhs_constant->as_double())/M_PI*180);
  return ret(lhs_constant);
}

Gpl_type Sqrt::type() const{
  Gpl_type lht = lhs->type();
  if(lht == STRING)
    return INT;
  return DOUBLE;
}
Constant* Sqrt::evaluate()
{
  //std::cout << "in sqrt::evaluate\n";
  Constant* lhs_constant = lhs->evaluate();
  lhs_constant= new Double_constant(sqrt(lhs_constant->as_double()));
  return ret(lhs_constant);
}

Gpl_type Abs::type() const{
  Gpl_type lht = lhs->type();
  if(lht == STRING)
    return INT;
  if(lht == DOUBLE) 
    return DOUBLE;
  //if(lht == INT) 
    return INT;
}
Constant* Abs::evaluate()
{
  //std::cout << "in abs::evaluate\n";
  Constant* lhs_constant = lhs->evaluate();
  try{
    lhs_constant= new Integer_constant(abs(lhs_constant->as_int()));
  }catch(...){
    lhs_constant= new Double_constant(fabs(lhs_constant->as_double()));
  }
  return ret(lhs_constant);
}

Gpl_type Floor::type() const{
  return INT;
}
Constant* Floor::evaluate()
{
  //std::cout << "in floor::evaluate\n";
  Constant* lhs_constant = lhs->evaluate();
  try{
    lhs_constant= new Integer_constant(lhs_constant->as_int());
  }catch(...){
    double j = lhs_constant->as_double();
    int d = std::floor(j);
    lhs_constant= new Integer_constant(d);
  }
  return ret(lhs_constant);
}

Gpl_type Random::type() const{
  return INT;
}
Constant* Random::evaluate()
{
  //std::cout << "in random::evaluate\n";
  Constant* lhs_constant = lhs->evaluate();
  int randbound;
  try{
    randbound = lhs_constant->as_int();
  }catch(...){
    randbound = floor(lhs_constant->as_double());
  }
  if(randbound < 2){
    Error::error(Error::INVALID_ARGUMENT_FOR_RANDOM, lhs_constant->as_string());
    randbound = 2;
  }
  lhs_constant= new Integer_constant(rand() % randbound);
  return ret(lhs_constant);
}

