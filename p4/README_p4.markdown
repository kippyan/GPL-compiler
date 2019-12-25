[//]: # (bash$ markdown_py README_p4.markdown >README_p4.html)


# The Fourth Project (p4)#

Ver. 24 April 2019

* Corrected listed functions in step #10

Ver. 22 April 2019

* Reworked game object code and updated step #10. More to come.

Ver. 19 April 2019

* Some minor textual edits. More substantive edits to come.

Ver. 17 April 2019

* Initial version. Step 13 to be revised.

## Summary ##

Support for game objects (Rectangle, Textbox, etc.) are added as well as forward declarations of animation blocks.

## Manifest ##

        ./src/p4/README_p4.html         You are reading this right now.
        ./src/p4/README_p4.markdown     Source file used to generate html page

        ./src/p4/Animation_block.cpp    Animation code block class
        ./src/p4/Animation_block.h

        ./src/p4/Circle.cpp             Circle game object class      
        ./src/p4/Circle.h

        ./src/p4/default_pixmap.h       A default image used by gpl

        ./src/p4/Event_manager.cpp      A stub class for managing GPL events. Expanded in p5
        ./src/p4/Event_manager.h

        ./src/p4/Game_object.cpp        The base class for the game objects
        ./src/p4/Game_object.h

        ./src/p4/Pixmap.cpp             Pixmap game object class
        ./src/p4/Pixmap.h

        ./src/p4/Rectangle.cpp          Rectangle game object class
        ./src/p4/Rectangle.h

        ./src/p4/Textbox.cpp            Textbox game object class
        ./src/p4/Textbox.h

        ./src/p4/Triangle.cpp           Triangle game object class
        ./src/p4/Triangle.h

        ./src/p4/Window.cpp             Class that encapsulates code used to render the graphics.
        ./src/p4/Window.h

## Project Description ##

1. Add support for the following game object types (as pointers) to class `Symbol`:
     * `Rectangle*`
     * `Circle*`
     * `Textbox*`
     * `Triangle*`
     * `Pixmap*`

    This requires writing:

    * Two constructors for each (individual objects and element of an array)
    * Two `as_*` functions for each. For example: `Rectangle* Symbol::as_rectangle() const`. Note that the `as_*` functions return a pointer to the game object, not the actual game object.

2. Add the ability to print the five different game objects in `Symbol::operator<<`. The five game object classes already support the ability to print via `operator<<`. Printing out a game object is as straightforward as printing out a string.

3. Add the same support for `Animation_block*` to class `Symbol` as was done with the game objects above. Note, there are never arrays of `Animation_blocks`. Add the ability to print animation blocks in `Symbol` as well. All that needs to be printed is "*animation_block*" followed by the name of the block. For example: `animation_block mycoolanimation`. Don't forget to add the member function: `Animation_block* Symbol::as_animation_block()`.

4. Derive six additional classes from `Constant`: one for each of the five game objects and one for the animation block. The private data member of each is a pointer. For example, 

        class Rectangle_constant : public Constant {
          private:
            Rectangle* data;
          public:
            Rectangle_constant(Rectangle* d) : data(d) {}
            virtual int         as_int()    const { throw RECTANGLE; }
            virtual double      as_double() const { throw RECTANGLE; }
            virtual std::string as_string() const { throw RECTANGLE; }
            virtual Rectangle*  as_rectangle() const { return data; }
            virtual Circle*     as_circle()    const { throw  RECTANGLE; }
            virtual Textbox*    as_textbox()   const { throw  RECTANGLE; }
            virtual Triangle*   as_triangle()  const { throw  RECTANGLE; }
            virtual Pixmap*     as_pixmap()    const { throw  RECTANGLE; }
            virtual Animation_block* as_animation_block() const { throw RECTANGLE; }
            virtual Gpl_type    type()      const { return RECTANGLE; }
        };


5. Update `Variable::evaluate()` to handle the six new classes derived from Constant.

6. Previously, the actions for the `variable_declaration` production rules were coded to create int, string, and double `Symbol`s and insert them into a `Symbol_table`.
Now, the actions for the  `object_declaration` production rules will be coded to create `Symbol`s (or an array of them) for `Rectangle`, `Circle`, `Textbox`, `Triangle`, and `Pixmap`.  Examples of object declarations:

        triangle my_triangle(x = 100, y = 100);
        rectangle some_rect(x = 42, y = 2, h = 100, w = 200, green = 1.0);

    When declaring single game objects, (i.e., the
    first rule of the `object_declaration` production) `parameter_list_or_empty` presents a
    special challenge because parameters are parsed before `object_declaration`
    is matched. This is a challenge because parameter errors include the name of
    the game object being declared. The solution is to delay processing parameters
    until after the game object itself is created as a symbol. As parameters are
    parsed, a linked list of them is built and passed to the
    `object_declaration` production to be validated after the game object is added
    to the symbol table.  Add a structure to `parser.h` to handle the linked list of
    parameters:

        struct Parameter {
              Expression* expression;
              std::string name;
              Parameter* next;
              ~Parameter() { delete next; }
        }; 

7. Write the action for the `parameter` production. The action simply creates and initializes a new `Parameter` object (`next` is initialized to `nullptr`). Assign the new structure object to `$$`.

    Add a new type to the `%union` in `gpl.y`: `Parameter* union_parameter_ptr`. Add a `%type` directive for `parameter`. At this point gpl.y (and the rest of the project) is incomplete but build. Remove all compiling errors before continuing.
   

8. Write the action for the `parameter_list` production.  Each parameter is added to the list of
     previous parameters by finding the last node in the list 
     (where `next==nullptr`). For this rule in the `parameter_list` production:

        parameter_list T_COMMA parameter

      `parameter_list` contains the current linked list, and parameter contains
      the new parameter to be added to the end of the list.

9. To the `parameter_list_or_empty` production, add `$$=nullptr` to the `empty` rule.

10. Add code to handle the `object_declaration` production (declare game objects and
   add them to the symbol table). A good starting place is to adapt a copy of
   the code that handles `variable_declaration`. Like `variable_declaration`, the
   `object_declaration` production has two rules, one for a single object and
   one for an array of objects. The rule for single object declaration 
   iterates through the linked list of parameters. For each parameter check that each
   is a valid game object parameter and that its value is of the correct
   type.  All parameters in gpl are either int, double, string, or
   `Animation_block*.`  
   
    Each game object class has a static member function to validate the type of
    member variables.  This function returns the `Gpl_type` of the variable
    whose  name is provided as a string.  An `out_of_range` exception is thrown
    if the provided name is not a member variable.

        Gpl_type Rectangle::get_member_variable_type(const string& name) const
        Gpl_type Circle::get_member_variable_type(const string& name) const
        Gpl_type Textbox::get_member_variable_type(const string& name) const
        Gpl_type Triangle::get_member_variable_type(const string& name) const
        Gpl_type Pixmap::get_member_variable_type(const string& name) const

    Example invocation:

        if(Circle::get_member_variable_type("radius")!=DOUBLE) //static fn. No object required
          ...


    Each game object class has member functions to set and get the value of a
    member variable whose name is provided as a string.

        Game_object::set_member_variable(string name, int               value)
        Game_object::set_member_variable(string name, double            value)
        Game_object::set_member_variable(string name, string            value)
        Game_object::set_member_variable(string name, Animation_block*  value)

        Game_object::get_member_variable(string name, int&              value)
        Game_object::get_member_variable(string name, double&           value)
        Game_object::get_member_variable(string name, string&           value)
        Game_object::get_member_variable(string name, Animation_block*& value)

    This member function will set the member variable given by name to value.
    The value may be an int, double, string, or `Animation_block*` The function
    is overloaded for the four types of value (that is, there are four versions
    of the function).

    The `set_*`/`get_*` functions will throw the following self-explanatory exceptions (this enumeration is defined in `gpl_types.h`):

        enum Status {
             MEMBER_NOT_OF_GIVEN_TYPE,
             MEMBER_NOT_DECLARED
             };

11. Add code to handle the other two rules in the variable production. These
    two rules handle variables that are members of game objects. For example:

        my_circle.x
        my_list_of_triangles[3].y

       Derive a class from Variable named `Member_variable`. It will
       have one private data string: the name of the game object's data member.
       In the above examples that would be "x" and "y". The `evaluate()` function
       interrogates the game object to obtain the value of the member variable
       which is returned as a constant object. `Game_object::get_member_variable()`
       is used to get the variable's value.

12. Some evaluate functions for the expressions classes may need to be updated to
    gracefully handle errors when game objects are errantly used in binary
    expressions (e.g. `Plus::evaluate()`, `Greater::evaluate()`, etc.).

13. **DO NOT DO THIS STEP YET** Add code to handle the `forward_declaration` production. Recall:

        forward animation some_anim_object_name(triangle some_game_object_name);

     There are two objects that are created and added to the symbol table in a
     forward declaration: a game object (inside the parentheses) and an
     animation block (named before the parentheses).

     The `Symbol` for the game object should be created in the
     `animation_parameter` production. and assigned to `$$`.
     Because this game object serves a special purpose (as a reference for an
     actual game object when the animation block is assigned to a game object)
     there are two member functions that should be called when the game object
     is created: `never_animate()`, and `never_draw()`.


     The `Symbol` for the animation block should be created in the
     `forward_declaration` production. The animation block has an initialize
     function that should be called on the newly-created animation block:
     `initialize($5, *$3)`. These input arguments are correct for the
     `forward_declaration` production (`$5` is the symbol for the game object and
     `*$3` is the name of the animation block variable).  Assuming there are no
     errors (such as previously declared variable) then both symbols should be
     added to the symbol table.
