[//]: # (bash$ markdown_py README_p1.markdown >README_p1.html)

# The First Project (p1) #

Ver. 10 February 2019

## Summary ##

For this first project, the tokens and grammar that comprise the Game Programming Language (GPL) will be integrated into files used by the scanner, flex (gpl.l) and the parser, bison (gpl.y). 

## Manifest ##

The tarball expands into the following file hierarchy:

        ./src/p1/README_p1.markdown     Source file used to generate html page
        ./src/p1/README_p1.html         You are reading this right now.

        ./src/p1/gpl.cpp                main() function. Don't change.
        ./src/p1/error.h                Header for error reporting functions. Don't change.
        ./src/p1/error.cpp              Source for error reporting functions. Don't change.

        ./src/p1/parser.h               Always include this file instead of gpl.tab.h.
        ./src/p1/gpl_assert.h           Header for a debugging function.
        ./src/p1/gpl_assert.cpp         Source for a debugging function.

        ./src/p1/tokens_for_bison.txt   Premade tokens to be added to gpl.y
        ./src/p1/grammar_for_bison.txt  Premade GPL grammar to be added to gpl.y
        ./src/p1/tokens_for_flex.txt    List of tokens to be integrated into gpl.l

        ./src/p1/gpl.l                  Stub scanner file to use.
        ./src/p1/gpl.y                  Stub parser file to use.
        ./src/p1/tests/*                This directory contains test code. See ./bin/README.html

        ./src/p1/Makefile               Self-explanatory (I hope)
        ./bin/README.html               instructions on using binaries in bin directory

        ./bin/gt                        run project tests
        ./bin/vde                       examine test differences in expected and actual error output
        ./bin/vd                        examine test differences in expected and actual standard output



## Format of files ##


        Grammar file (.y extension)     |       Scanner file (.l extension)
        ---------------------------     |       ---------------------------
        %{                              |       %{
        Prologue (code)                 |       Prologue (code)
        %}                              |       %}
                                        |       
        Bison Declarations              |       Flex definitions
                                        |       
        %%                              |       %%
                                        |       
        Grammar Rules                   |       Scanner rules
                                        |       
        %%                              |       %%
                                        |       
        Epilogue                        |       Epilogue

## Project description ##

1. Because the parser (`gpl.y`) generates the tokens that are included by the scanner (`gpl.l`) the parser should be built first. Begin by copying `tokens_for_bison.txt` into `gpl.y` just below the comment `//tokens declared here`.

2. The scanner will be passing semantic values to the parser. For example, when the scanner encounters `3.14` in a gpl program, it will return token `T_DOUBLE_CONSTANT` to the parser and set the token's semantic value to `3.14`. There are three types of semantic value returned: `int`, `double`, and `string*`. These three types must be part of the parser's `%union` declaration. Two of these three types have already been added for you.

3. Several of the parser's tokens have empty angle-braces `< >`. These are the tokens that have semantic values found by the scanner. Inside the angle braces add the appropriate union member (e.g., `union_int`) to specify the type of that token's semantic value.

4. Copy `grammar_for_bison.txt` into the "Grammar Rules" section of `gpl.y`. 

5. Run `bison -d gpl.y`. There should be a warning of over 200 shift/reduce conflicts, but no errors.

6. Copy the `tokens_for_flex.txt` file into the "Scanner rules" section of `gpl.l`.

7. Each of the matched literal/keyword expressions should return the corresponding token defined in `gpl.y`. For example:

        "int" {return T_INT;}
        ...
        "!=" {return T_NOT_EQUAL;}

    The `forward`, `print`, and `exit` keywords also having semantic values requiring the appropriate union member of `yylval` to be set. For example:

        "print" {yylval.union_int = line_count; return T_PRINT; }

    The `forward`, `print`, and `exit` keywords return the value of `line_count` as their semantic values. This is a global variable that keeps track of the current line number being analyzed by the scanner. The global declaration itself has already been provided in the prologue of `gpl.l`. However, a scanner rule must be added that increments `line_count` whenever a newline is encountered.

8. Create the regular expressions and the associated actions for the more complex tokens:
    * **integer constant** - A sequence of one or more digits (0 – 9). Place the value of the integer in the `union_int` field `yylval`.
    * **double constant** - A sequence of one or more digits (0 - 9) that contains a period. May start with a period or end with a period (.1, 1., 1.1, 123.123 are all legal). Place the value of the double in the `union_double` field of `yylval`.  Ensure a period "." is not matched as a double.
    * **string constant** - Any sequence of characters enclosed in double quotes ("one", "123", "one two three" are all legal). Place the value of the string *without the quotes* in the `union_string` field of `yylval`. Dynamically allocate a new string for each token. For example:  `yylval.union_string=new string(yytext);` Note that the above code snippet is only an example. It does not remove quotes if they are present in `yytext`.
    * **identifier** - Any letter (a-z or A-Z) or underscore followed by zero or more letters, underscores, and digits (0-9). Place the value of the string in the `union_string` field of `yylval`. Dynamically allocate a new string for each token.
    * **comments** - Like the C++ `//` commment. Ignore everything to the end of the line
   
8. In `gpl.y` just below the `%token` declarations, add precedence declarations (e.g., `%left, %right, %nonassoc`) for the following operators (these precedence requirements are also denoted by comments in `tokens_for_flex.txt`):

        * / + - %
        < > <= >= == != !  && ||
        near touches

    Place operators with the same precedence on the same line. For example:

        %left T_PLUS T_MINUS

    The unary operators - (`T_MINUS`) and ! (`T_NOT`) are non-associative (directive written as: %nonassoc).  T_NOT can be added along with the other operators, but T_MINUS is problematic because it's precedence is already specified as a binary operator (subtraction). Create/name a precedence for negation (at its appropriate level), like this:

        %nonassoc UNARY_OPS

    To tie this new token's precedence to the unary function of negating an expression, add a `%prec` directive at the end of the production rule for it:

        expression: T_MINUS expression %prec UNARY_OPS

    The if-statement rules have a shift/reduce conflict. To remove it, create a new (non-associative) precedence token for the if without an else. And give the existing `T_ELSE` token a higher (non-associative) precedence than `IF_NO_ELSE`

        %nonassoc IF_NO_ELSE

    As was done with the `UNARY_OPS`, add a `%prec` directive at the end of the rule for an if-statement that does not have an else clause.

Final note: `gpl.tab.h` is generated by bison and is normally included inside of the flex file, `gpl.l`. For these projects, `gpl.tab.h` is now included in `parser.h` which is included by `gpl.l`. This is only notable in that in future projects structure declarations, include statements, etc. will be required. Those will be added to `parser.h` instead of directly to `gpl.l`.
