[//]: # (bash$ markdown_py README_p2.markdown >README_p2.html)

# The Second Project (p2) #

Ver. 20 February 2019

* Initial version

## Summary ##

For this second project, symbols and symbol tables are introduced to manage the declaration and access of variables that are created in GPL.

## Manifest ##

The tarball expands into the following file hierarchy:

        ./src/p2/README_p2.markdown     Source file used to generate html page
        ./src/p1/README_p2.html         You are reading this right now.

        ./src/p2/gpl_type.h             Enumerations and function prototypes for use in managing types in the GPL language
        ./src/p2/gpl_type.cpp           Source to utility functions declared in header file.
        ./src/p2/Makefile               Updated Makefile.
        ./src/p2/gpl.cpp                Updated gpl.cpp.
        ./src/p2/tests/*                Testing suite for P2

        ./src/p2/sample_singleton.cpp   Sample code--implementing Singleton class

## Project description ##

1. A `Symbol` class will have a private data member that is a union to manage each type of variable that the GPL language supports. For this project, GPL integers, doubles, and strings will be supported. Each member of the union should be a pointer to the type. Creating a constructor for each data member eases its use in `Symbol`'s initialization list. Example of union declaration:
        union symbol_type {
          double* double_pointer;
          //etc. for int and string

          //constructors to ease initialization of union variables
          symbol_type(double* val) : double_pointer(val){}
          //etc. for int and string
        };

2. Write the `Symbol` class.  

    Private data:

        std::string name; //the name of the variable
        symbol_type value; //the contents of the variable
        Gpl_type type;  //the type of the variable. See gpl_type.h
        int count; //used to store the size if the variable is an array

    Public member functions:

        Symbol(const std::string& name, double* value); //for double variable
        Symbol(const std::string& name, double* value, int count); //for double array
        //etc. for int and string

        Gpl_type get_type();
        std::string get_name();
        friend std::ostream& operator<<(std::ostream& os, const Symbol&);

    The actual value (or array of values) is created using `new` outside of the constructor. The constructor takes a pointer to the newly-allocated value(s). The destructor (`Symbol::~Symbol`) is responsible for releasing the memory (`delete`, or `delete []`, depending on whether value points to a single variable or array of variables).


3. Test the `Symbol` class. Write a test program that creates various Symbols. Run the test code through `valgrind` to confirm that there are no memory leaks:

        valgrind ./a.out

4. Write the `Symbol_table` class.  The `Symbol_table` class manages an `unordered_map` with the symbol's name as the key and a pointer to the `Symbol` object as the value. Smart pointers are used to avoid memory leaks.

        class Symbol_table {
          public:
            std::shared_ptr<Symbol> lookup(const std::string& name);
            bool insert(std::shared_ptr<Symbol> sym);
            friend std::ostream& operator<<(std::ostream& os, const Symbol_table&);
          private:
            std::unordered_map<std::string, std::shared_ptr<Symbol>> symbols;
        };


    `Symbol_table::lookup` -- Return the named `Symbol` object if it is found in the `unordered_map`, and `nullptr` otherwise. Note that `unordered_map::find` should be used to search the keys for the symbol's name. Using `[ ]` will create an entry if it doesn't already exist.

    `Symbol_table::insert` --  If the `Symbol` input parameter already exists in the `unordered_map` return `false`. Otherwise add the `Symbol` to the map and return `true`.

    `Symbol_table::operator<<` -- Print out all of the symbols in the table sorted by name. The format of the output is: **`type name = value`**. For example:

        int a = 42
        double b = 3.14159
        int c = 42
        string d = "Hello world"
        int nums[0] = 42
        int nums[1] = 42
        int nums[2] = 42

    Note that the double-quotes surrounding the string are added by the printing routine. They are not be part of the string's value. The flex pattern action from the previous project strips the quotes off.

5. Write a test program to ensure the `Symbol_table` class is bug-free. Run the test code through `valgrind` to confirm that there are no memory leaks:

6. Write the `Table_handler` class. This class is a *singleton* class which ensures that no more than one `Table_handler` object will exist in the application. See `sample_singleton.cpp` for an example of how to structure a class as a singleton. (Be sure to move `sample_singleton.cpp` out of the project directory or the Makfile will try to add it to the project build.) A `std::vector` should be used as the private data to manage multiple symbol tables.

        static std::vector<std::shared_ptr<Symbol_table>> tables;

    The public member functions include:

    * `static Table_handler& instance()` -- Return the singleton instance. Additionally, if the vector of `Symbol_table` instances is empty, call `push_table()` to add a new `Symbol_table` object before returning the singleton.

    * `void push_table()` -- Create a new `Symbol_table` and `push_back` onto the vector.

    * `void pop_table()` -- If more than one table is on the vector `pop_back()` to remove it. If there is only one table on the vector, throw an exception:

                #include<stdexcept>
                throw std::underflow_error("Can't pop global symbol table");

    * `bool insert(std::shared_ptr<Symbol> sym)` -- Add a symbol to the top/last/back table in the vector via a call to `Symbol_table::insert`.

    * `std::shared_ptr<Symbol> lookup(const std::string& name)` -- Iterate through the symbol tables from back to front, calling `Table_handler::lookup` on each. Return the first match found. Return `nullptr` if the symbol is undefined.

    * `bool defined_in_current_scope(const std::string& name)` -- Search the top/last/back table for the named symbol. Return true if it is defined, false otherwise. Used to check for variable redefinition errors.

    * `friend std::ostream& operator<<(std::ostream& os, Table_handler& sh)` - Iterate through the symbol tables from back to front, printing each.

7. Write a test program to ensure `Table_handler` is bug-free. Run the test code through `valgrind` to ensure it is free of memory leaks.

8. In `gpl.y`, the specific type of the `simple_type` production should be made available to the `variable_declaration` production. Assign the corresponding `Gpl_type` to each rule:
        
        simple_type:
            T_INT      {$$=INT;}
            | T_DOUBLE {$$=DOUBLE;}
            | T_STING  {$$=STRING;}


9. Assigning a `Gpl_type` to `simple_type` requires two additional configurations:

    1. Add **`Gpl_type union_gpl_type;`** to the `%union` declaration.

    2. Declare the type that `simple_type` holds:

            %type <union_gpl_type> simple_type

           This can be appended just after the `%token` declarations.

10. For this project, simplify the rule in the `variable_declaration` production for declaring arrays. 

    <span style="color:red">Original:</span> <pre>
        | simple_type  T_ID T_LBRACKET **expression** T_RBRACKET
</pre><span style="color:LimeGreen">Simplified:</span> <pre>
        | simple_type  T_ID T_LBRACKET **T_INT_CONSTANT** T_RBRACKET
</pre>

11. Write the action that accompanies the two `variable_declaration` rules. Each action should allocate and initialize variables and arrays. Initialize both individual variables and each element of arrays using hard-code values:

        int     42
        double  3.14159
        string  "Hello world"

     Error checking should also be done and reported using the error routines found in `error.h` and `error.cpp`. For example:

        
        Table_handler& tabhand=Table_handler::instance();
        if(tabhand.defined_in_current_scope(*$2))
        {
          Error::error(Error::PREVIOUSLY_DECLARED_VARIABLE, *$2);
          // break after error because generated code puts each
          // rule as a case in a switch statement
          break; 
        }

11. After these actions are completely written, all of the tests should pass.

12. The scanner (`gpl.l`) dynamically allocates strings for the semantic values of `T_ID`. To avoid memory leaks these need to be released in the parser. At the end of each action for `variable_declaration`, release the memory allocated for `T_ID`:

        delete $2;

    Errors that `break` out of the action (Shown in the #11 example), should release the memory before the break.

13. Syntax errors are sequences of tokens that do not match any rule in the grammar. In this case, the parser itself needs to release memory allocated in the scanner. This is done with the following directive (just add it below the `%union` directive):

        %destructor { delete $$; } <union_string>

    Adding this directive will generate bison warnings in 5-6 places where a rule uses `T_ID` but for which no action has been written. This is OK in this project.

14. Finally, dynamic memory is allocated for `T_CONSTANT_STRING`. Since we aren't using this constant in this project, add an action to delete it in the `primary_expression` production.

15. Use valgrind to confirm that none of the tests leak memory.
