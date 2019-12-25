#ifndef VARIABLE_H
#define VARIABLE_H
#include <memory>
#include "Expression.h"
#include "Symbol.h"
class Variable : public Expression {
 public:  
  Variable(std::shared_ptr<Symbol> sym);
  Variable(std::shared_ptr<Symbol> sym, Expression* arridx);
  virtual Constant* evaluate();
  Variable(const Variable&) = delete;
  Variable& operator=(const Variable&) = delete;
  virtual Gpl_type type() const;
 protected:
  std::shared_ptr<Symbol> symbol;
  Expression* array_index_expression;
};

#endif

