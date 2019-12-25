// updated Mon Apr 15 17:45:24 PDT 2019

/*
  An Animation_block is a Statement_block with:
    a parameter symbol pointer (m_parameter_symbol)
    a name (m_name)
    a flag to indicate if the body exists 
        (forward + animation block -vs- forward w/o animation block)
 
  When an animation is executed, it needs to know both the formal and
  the actual parameters.  At parse time the formal parameter is known and
  is passed to Animation_block::initialize().

  At execution, the actual parameter is known and is passed to execute()

  p4 & p5:  can use this file (you do not have to change it) 

  p6: must (1) implement flag to indicate if body exists 
                  will need a set and get functions
           (2) write the body of Animation_block::execute()
*/

#ifndef ANIMATION_BLOCK_H
#define ANIMATION_BLOCK_H

#include <string>

class Symbol;
class Game_object;

class Animation_block
{
  public:
    Animation_block() {}; // relies on default parameters
    void initialize(Symbol *parameter_symbol, std::string name);

    void execute(Game_object *argument);

    Symbol *get_parameter_symbol() {return m_parameter_symbol;}
    std::string name() {return m_name;}

    // Disable default copy constructor and default assignment
    // This will prevent accidental use.
    Animation_block(const Animation_block &) = delete;
    const Animation_block &operator=(const Animation_block &) = delete;
  private:

    Symbol *m_parameter_symbol = NULL;
    std::string m_name = "you forgot to call initialize() on this Animation_block";

};

#endif // #ifndef ANIMATION_BLOCK_H
