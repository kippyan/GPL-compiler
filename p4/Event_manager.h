// updated Mon Apr 15 20:37:30 PDT 2019

/***
  This file is a placeholder for the Event_manager class you will write 
  in phase 5 (p5).

  class Window uses class Event_manager.  Since p4 uses class Window
  this placeholder class allows p4 to work.

  You may use this file and Event_manager.cpp w/o modification in p4.

  You may use them as a starting point for your Event_manager class for p5.

  I have put in just enough for it to work in p4.

***/

#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H

#include <memory>
#include <iostream>
#include <string>
#include <vector>

#include "Window.h" // for Keystroke enum

class Statement;

class Event_manager
{
  public:

    static Event_manager& instance();

    void execute_handlers(Window::Keystroke keystroke);
    void add_handler(Window::Keystroke, Statement*);

    ~Event_manager();

    // Disable default copy constructor and default assignment
    // This will prevent accidental use.
    Event_manager(const Event_manager&) = delete; 
    const Event_manager &operator=(const Event_manager&) = delete;

  private:
    // hide default constructor because this is a singleton
    Event_manager();

};

#endif // #ifndef EVENT_MANAGER_H
