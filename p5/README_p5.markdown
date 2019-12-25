[//]: # (bash$ markdown_py README_p5.markdown >README_p5.html)

# The Fifth Project (p5) #

Ver. 6 May 2019

* Initial version.

## Errata to gpl.y ##

The purpose of this errata is to allow game objects to be declared without parentheses. For example,
`Triangle t;`

1.  <span style="color:red">Original:</span> <pre>object_declaration:
    object_type T_ID **T_LPAREN** parameter_list_or_empty **T_RPAREN**
</pre><span style="color:LimeGreen">Revised:</span> <pre>
object_declaration:
    object_type T_ID parameter_list_or_empty
</pre>
  NOTE: this changes $4 to $3. Be sure to update the action code for this rule, replacing each occurrence of $4 with $3.

2.  <span style="color:red">Original:</span> <pre>parameter_list_or_empty:
    parameter_list
    | empty {$$=nullptr;}
    ;
</pre><span style="color:LimeGreen">Revised:</span><pre>parameter_list_or_empty:
    **T_LPAREN** parameter_list **T_RPAREN** **{$$=$2;}**
    **| T_LPAREN empty T_RPAREN {$$=nullptr;}**
    | empty {$$=nullptr;}
</pre>


## Description ##

This project implements the functionality for event blocks (e.g., `on leftarrow {...}`) and statements.


1. In GPL, assignment can occur on `int`, `double`, `string`, and `Animation_block*`. At the C++ level, that means that functions are required that allow a symbol's value to change. Adjust the signatures of the Symbol class's `as_*` functions associated with these types. Returning by reference allows these to appear on the left-hand side of expressions. For example:

        my_symbol->as_double()=3.14; //change the symbol's value to 3.14

    This can be accomplished by simply removing `const` and adding `&` to the return type. There is no need to change the body of these functions, just change their signatures in the header and source files.

    The provided `Window` class assumes your Symbol class has the signatures as shown below. If your `as_(int|double|string)` functions return pointers, modify the Window code to dereference and change their values. Compiler errors in Window.cpp will direct you to the four lines of code to adjust.

        // Symbol.h
        int& as_int();                             //was: int as_int() const;
        double& as_double();                       //was: double as_double() const;
        std::string& as_string();                  //was: std::string as_string() const;
        Animation_block*& as_animation_block();    //was as_animation_block() const;

        int& as_int(int);                          //was: int as_int(int) const;
        double& as_double(int);                    //was: double as_double(int) const;
        std::string& as_string(int);               //was: std::string as_string(int) const;

2. The `Variable` and `Member_variable` classes must support being changed by `=`, `+=`, `-=`, `++`, and `--`. For example:

        my_rect.x += 30;
        var = 9.2;
        my_triangle.height++;

    Create a member function for each of the operators in both classes:

        virtual void assign(Constant* cptr);
        virtual void plus_equals(Constant* cptr);
        virtual void minus_equals(Constant* cptr);
        virtual void plus_plus();
        virtual void minus_minus();

    Each of these functions should make the appropriate modification to the variable's underlying symbol. Consult the GPL manual for the types each operator may operate on (e.g., `-=` is only valid for `int` and `double`).

3. *Overview*: Statements should be architected similarly to operators. An abstract base class `Statement` is provided. It has a pure virtual execute function: `virtual void execute()=0;`  This function is overridden in each statement subclass, similar to how the `evaluate()` function is overridden in the expression subclasses. There is also a protected `next` pointer provided which allows statements to be chained together. Statements are chained together in the `statement_list` production. (Note this is semantically similar to how parameters were chained together in the `parameter_list` production). The `Statement` class also has an `append_statement()` function. Call it to add a statement to the end of the statement chain. Each subclass has the following private data members:
    * class `Print_statement`
        + line number
        + Expression pointer
    * class `If_statement`
        + Expression pointer
        + Statement pointer (for the if-clause)
        + Statement pointer (for the optional else-clause)
    * class `Assignment_statement`
        + Variable pointer (LHS)
        + Expression pointer (RHS, not present with ++ and --)
        + operator type (=, +=, -=, ++, --)
        + *Alternatively*, derive a separate classes for each specific type of assignment statement.
    * class `Exit_statement`
        + Expression pointer (evaluates to integer exit status)
    * class `For_statement`
        + Statement pointer (initializer, *can be `nullptr`*)
        + Expression pointer (condition, evaluates to int)
        + Statement pointer (incrementor, *can be `nullptr`*)
        + Statement pointer (body of loop)

    **Note**: To ensure that the entire chain of statements in a block are executed, the last statement of every `execute()` function should be:

        if(next!=nullptr)
          next->execute(); //execute next statement

4. Begin by coding a `Print` class, a class derived from the `Statement` class that handles the GPL print statement. Recall usage of the GPL print statement:

        print("value=" + 42 + ", x=" + x); 
        //displays: print[6]: value=42, x=38.2
        //In this example the 6 in square braces is the line number

    The constructor to this class should take the current line number (stored in the `line_count` variable in `gpl.y`) and an expression pointer. The execute() member function should print in the format shown in the example above. Don't forget to make the last line of the execute function: `if(next!=nullptr) next->execute();` Write a destructor that releases (deletes) the expression pointer.

5. Modify `gpl.y` to integrate the new Print statement class:
    * In the production rule for `print_statment:`, code an action to create a `Print` object. A new `%type` entry will be required (of type `Statement*`. The newly allocated object will be assigned to $$.
    * Add a `%type` entry for `statement`. Code the `print_statement` rule for `statement` (`$$=$1;`)
    * Add a `%type` entry for `statement_list`. Code both rules for this production. The `statement_list` rule invokes the `append_statement function`: `$1->append_statement($2); $$=$1;`. The `statement` rule is simply `$$=$1;`.
    * Add a `%type` entry and code action for propgating the `Statement*` through the `statement_block` and `statement_or_block_of_statements` productions.

6. The skeleton of the `Event_manager` class is provided. GPL events (such as
   `on downarrow { ... }`) are collected by the event manager and executed
   automatically by the `Window` class. A `Statement*` points to the first
   statement of a linked list of statements comprising the event block. Because
   there can be more than one event block written for each event (e.g.,
   multiple downarrow event blocks), the proper data structure to handle an
   event type is a vector of `Statement*`. Finally, there are several events
   handled by GPL (not just downarrow), So `Event_manager` should have an array
   of vectors, one for each type of event (downarrow, uparrow, jkey, etc.). The
   size of the array is given by `Window::NUMBER_OF_KEYS`:
   
        std::vector<Statement*> events[Window::NUMBER_OF_KEYS]; //private data of Event_manager, an array of vectors.
   
    An enumeration type, `Window::Keystroke` has been defined for the different
    events. These enumerations start at zero and are contiguous so work nicely
    as array indices. Usage example: To access the downarrow event blocks in the
    vector: 

        Window::Keystroke thekey=Window::JKEY;
        //...
        events[thekey]; //this is a vector of Statement pointers for the J-key 

    Write the `Event_manager::add_handler` and `Event_manager::execute_handlers` member functions. Each is only a couple lines long. The destructor should iterate through the array of vectors, releasing (deleting) each Statement* in each vector.

7. For each rule in the `keystroke:` production, assign the appropriate Window::Keystroke enumeration. Add the appropriate %type

8. Add an action for the rule to the `on_block:` production:

                { Event_manager::instance().add_handler($2, $3); }
