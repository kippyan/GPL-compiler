#include<iostream>
#include "Statement.h"

void Statement::append_statement(Statement* atend)
{
  Statement* current=this;
  while(current->next != nullptr)
    current=current->next;
  current->next=atend;
}

void Print_statement::execute()

void If_statement::execute()
  
void Assign::execute()

void Plus_equals::execute()

void Minus_equals::execute()
  
void Plus_plus::execute()

void Minus_minus::execute()
