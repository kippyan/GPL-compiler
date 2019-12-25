// updated Mon Apr 15 17:45:03 PDT 2019

#include <vector>
#include "Animation_block.h"
#include "Game_object.h"
#include "gpl_assert.h"
#include "Symbol.h"
using namespace std;

void Animation_block::initialize(Symbol *parameter_symbol, string name)
{
  m_name = name;
  // during error recovery a NULL parameter_symbol can be passed to Animation_block()
//  if (parameter_symbol)
//    assert(parameter_symbol->is_game_object());
  m_parameter_symbol = parameter_symbol;
}

void Animation_block::execute(Game_object *argument)
{
  // you have to implement this as part of p6
}

