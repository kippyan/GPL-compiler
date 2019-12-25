//File: Expression.h
#ifndef EXPRESSION_H
#define EXPRESSION_H
#include "gpl_type.h"
class Constant;
class Expression {
  public:
    Expression():evaluated_constant(nullptr) {}
    Expression(Constant* cptr):evaluated_constant(cptr) {}
    virtual Constant* evaluate()=0;
    virtual ~Expression();
    virtual Gpl_type type() const = 0;
  protected:
    Constant* evaluated_constant;//keep pointer so it can be released
};

class Binary_operator : public Expression {
  public:
    Binary_operator(Expression* lhs, Expression* rhs) :lhs(lhs), rhs(rhs) {}
    virtual Constant* evaluate()=0;
    virtual ~Binary_operator() { delete lhs; delete rhs;}
  protected:
    Expression* lhs;
    Expression* rhs;
    Constant* ret(Constant* cp);
};
class Unary_operator : public Expression {
  public:
    Unary_operator(Expression* lhs) :lhs(lhs){}
    virtual Constant* evaluate()=0;
    virtual ~Unary_operator() { delete lhs;}
  protected:
    Expression* lhs;
    Constant* ret(Constant* cp);
};

class Plus : public Binary_operator {
  public:
    Plus(Expression* lhs, Expression* rhs) : Binary_operator(lhs, rhs){};
    virtual Constant* evaluate();
    virtual Gpl_type type() const;
};
class Minus : public Binary_operator {
  public:
    Minus(Expression* lhs, Expression* rhs) : Binary_operator(lhs, rhs){};
    virtual Constant* evaluate();
    virtual Gpl_type type() const;
};
class Multiply : public Binary_operator {
  public:
    Multiply(Expression* lhs, Expression* rhs) : Binary_operator(lhs, rhs){};
    virtual Constant* evaluate();
    virtual Gpl_type type() const;
};
class Divide: public Binary_operator {
  public:
    Divide(Expression* lhs, Expression* rhs) : Binary_operator(lhs, rhs){};
    virtual Constant* evaluate();
    virtual Gpl_type type() const;
};
class Mod: public Binary_operator{
  public:
    Mod(Expression* lhs, Expression* rhs) : Binary_operator(lhs, rhs){};
    virtual Constant* evaluate();
    virtual Gpl_type type() const;
};
class Or: public Binary_operator {
  public:
    Or(Expression* lhs, Expression* rhs) : Binary_operator(lhs, rhs){};
    virtual Constant* evaluate();
    virtual Gpl_type type() const;
};
class And: public Binary_operator {
  public:
    And(Expression* lhs, Expression* rhs) : Binary_operator(lhs, rhs){};
    virtual Constant* evaluate();
    virtual Gpl_type type() const;
};
class Less_than: public Binary_operator {
  public:
    Less_than(Expression* lhs, Expression* rhs) : Binary_operator(lhs, rhs){};
    virtual Constant* evaluate();
    virtual Gpl_type type() const;
};
class Greater_than: public Binary_operator {
  public:
    Greater_than(Expression* lhs, Expression* rhs) : Binary_operator(lhs, rhs){};
    virtual Constant* evaluate();
    virtual Gpl_type type() const;
};
class Less_equal: public Binary_operator {
  public:
    Less_equal(Expression* lhs, Expression* rhs) : Binary_operator(lhs, rhs){};
    virtual Constant* evaluate();
    virtual Gpl_type type() const;
};
class Greater_equal: public Binary_operator {
  public:
    Greater_equal(Expression* lhs, Expression* rhs) : Binary_operator(lhs, rhs){};
    virtual Constant* evaluate();
    virtual Gpl_type type() const;
};
class Equal: public Binary_operator {
  public:
    Equal(Expression* lhs, Expression* rhs) : Binary_operator(lhs, rhs){};
    virtual Constant* evaluate();
    virtual Gpl_type type() const;
};
class Not_equal: public Binary_operator {
  public:
    Not_equal(Expression* lhs, Expression* rhs) : Binary_operator(lhs, rhs){};
    virtual Constant* evaluate();
    virtual Gpl_type type() const;
};
class Unary_minus: public Unary_operator {
  public:
    Unary_minus(Expression* lhs) : Unary_operator(lhs){};
    virtual Constant* evaluate();
    virtual Gpl_type type() const;
};
class Not: public Unary_operator {
  public:
    Not(Expression* lhs) : Unary_operator(lhs){};
    virtual Constant* evaluate();
    virtual Gpl_type type() const;
};
class Cosine: public Unary_operator {
  public:
    Cosine(Expression* lhs) : Unary_operator(lhs){};
    virtual Constant* evaluate();
    virtual Gpl_type type() const;
};
class Sine: public Unary_operator {
  public:
    Sine(Expression* lhs) : Unary_operator(lhs){};
    virtual Constant* evaluate();
    virtual Gpl_type type() const;
};
class Tan: public Unary_operator {
  public:
    Tan(Expression* lhs) : Unary_operator(lhs){};
    virtual Constant* evaluate();
    virtual Gpl_type type() const;
};
class Acos: public Unary_operator {
  public:
    Acos(Expression* lhs) : Unary_operator(lhs){};
    virtual Constant* evaluate();
    virtual Gpl_type type() const;
};
class Asin: public Unary_operator {
  public:
    Asin(Expression* lhs) : Unary_operator(lhs){};
    virtual Constant* evaluate();
    virtual Gpl_type type() const;
};
class Atan: public Unary_operator {
  public:
    Atan(Expression* lhs) : Unary_operator(lhs){};
    virtual Constant* evaluate();
    virtual Gpl_type type() const;
};
class Sqrt: public Unary_operator {
  public:
    Sqrt(Expression* lhs) : Unary_operator(lhs){};
    virtual Constant* evaluate();
    virtual Gpl_type type() const;
};
class Abs: public Unary_operator {
  public:
    Abs(Expression* lhs) : Unary_operator(lhs){};
    virtual Constant* evaluate();
    virtual Gpl_type type() const;
};
class Floor: public Unary_operator {
  public:
    Floor(Expression* lhs) : Unary_operator(lhs){};
    virtual Constant* evaluate();
    virtual Gpl_type type() const;
};
class Random: public Unary_operator {
  public:
    Random(Expression* lhs) : Unary_operator(lhs){};
    virtual Constant* evaluate();
    virtual Gpl_type type() const;
};

#endif
