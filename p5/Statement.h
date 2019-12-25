#ifndef STATEMENT_H
#define STATEMENT_H

class Statement {
  public:
    void append_statement(Statement* atend);
    Statement():next(nullptr) {}
    virtual void execute()=0;
    virtual ~Statement(){}
  protected:
    Statement* next;
};

class Print_statement : protected Statement {
  private:
    int line_number;
    Expression* expr;
};

class If_statement : protected Statement {
  private:
    Expression* expr;
    Statement* if_clause;
    Statement* else_clause;
};

class Assign : protected Assignment_statement {
  private: 
    Variable* LHS;
    Expression* RHS;
};
class Plus_equals : protected Assignment_statement {
  private: 
    Variable* LHS;
    Expression* RHS;
};
class Minus_equals : protected Assignment_statement {
  private: 
    Variable* LHS;
    Expression* RHS;
};
class Plus_plus : protected Assignment_statement {
  private: 
    Variable* LHS;
};
class Minus_minus : protected Assignment_statement {
  private: 
    Variable* LHS;
};
#endif
