#ifndef MEMBER_VARIABLE_H
#define MEMBER_VARIABLE_H
#include <memory>
#include "Variable.h"
#include "Constant.h"
#include "error.h"
class Member_variable : public Variable{
  public:  
    Member_variable(std::shared_ptr<Symbol> sym, const std::string& name);
    Member_variable(std::shared_ptr<Symbol> sym, Expression* index_exp, const std::string& data_member_name);
    virtual Constant* evaluate();
    virtual Gpl_type type() const;
    Member_variable(const Member_variable&) = delete;
    Member_variable& operator=(const Member_variable&) = delete;
  private:
    std::string data_member_name;
};

#endif

