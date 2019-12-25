#ifndef VARIABLE_H
#define VARIABLE_h
#include <memory>
#include "Expression.h"
#include "Symbol.h"
class Variable:public Expression {
 public:  
  Variable(std::shared_ptr<Symbol> sym);
  Variable(std::shared_ptr<Symbol> sym, Expression* arridx);
  virtual Constant* evaluate();
  Variable(const Variable&) = delete;
  Variable& operator=(const Variable&) = delete;
  Gpl_type type() const;
 private:
  std::shared_ptr<Symbol> symbol;
  Expression* array_index_expression;
};

#endif

