// updated Mon Apr 15 17:24:40 PDT 2019

#ifndef CIRCLE_H
#define CIRCLE_H

#include "Game_object.h"

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif

class Circle : public Game_object
{
  public:
    Circle(bool draw_me=true,double red = 0, double green = 0, double blue = 1);
    virtual ~Circle(){}

    // Disable default copy constructor and default assignment
    // This will prevent accidental use.
    Circle(const Circle &) = delete;
    const Circle &operator=(const Circle &) = delete;
    static Gpl_type get_member_variable_type(const std::string& name);
  private:
    static std::map<const std::string, Gpl_type> var_types;
    virtual void updated(std::string name);
    virtual void build_display_list();

    int m_radius;
    GLUquadricObj *m_quadric;
};

#endif // #ifndef CIRCLE_H
