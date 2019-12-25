// updated Mon Apr 15 20:43:21 PDT 2019

#include <memory>
#include "Event_manager.h"
#include "gpl_assert.h"
using namespace std;


/* static */ Event_manager&  Event_manager::instance()
{
  static Event_manager the_manager;
  return the_manager;
}

Event_manager::Event_manager()
{
}

Event_manager::~Event_manager()
{
}

void Event_manager::execute_handlers(Window::Keystroke keystroke)
{
  #ifdef P5
    assert(false && "Implement this for p5!");
  #endif
}
