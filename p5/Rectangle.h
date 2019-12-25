// updated Mon Apr 15 17:23:19 PDT 2019

#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Game_object.h"

class Rectangle : public Game_object
{
  public:
    Rectangle(bool draw_me=true,double red = 1.0, double green = 0.0, double blue = 0.0);

    // Disable default copy constructor and default assignment
    // This will prevent accidental use.
    Rectangle(const Rectangle &) = delete;
    const Rectangle &operator=(const Rectangle &) = delete;
    static Gpl_type get_member_variable_type(const std::string& name);
  private:
    static std::map<const std::string, Gpl_type> var_types;//tagger

    virtual void build_display_list();

    double m_rotation;

};

#endif // #ifndef RECTANGLE_H
