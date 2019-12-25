//File: Constant.h
#ifndef CONSTANT_H
#define CONSTANT_H
#include "Expression.h"
#include "gpl_type.h"

class Constant : public Expression {
  public:
    virtual Constant*   evaluate() final;
    virtual int         as_int()    const=0;
    virtual double      as_double() const=0;
    virtual std::string as_string() const=0;
};

class Integer_constant : public Constant {
  private:
    int data;
  public:
    Integer_constant(int d) : data(d) {}
    virtual int         as_int()    const { return data; }
    virtual double      as_double() const { return data; }
    virtual std::string as_string() const { return std::to_string(data);}
    virtual Gpl_type type() const {return INT;}
};

class Double_constant : public Constant {
  private:
    double data;
  public:
    Double_constant(double d) : data(d) {}
    virtual int         as_int()    const { throw DOUBLE; }
    virtual double      as_double() const { return data; }
    virtual std::string as_string() const { return std::to_string(data);}
    virtual Gpl_type type() const {return DOUBLE;}
};

class String_constant : public Constant {
  private:
    std::string data;
  public:
    String_constant(const std::string& d) : data(d) {}
    virtual int         as_int()    const { throw STRING; }
    virtual double      as_double() const { throw STRING; }
    virtual std::string as_string() const { return data;}
    virtual Gpl_type type() const {return STRING;}
};
#endif
