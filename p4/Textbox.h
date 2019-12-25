// updated Mon Apr 15 17:26:13 PDT 2019

#ifndef TEXTBOX_H
#define TEXTBOX_H

#include "Game_object.h"
#include <string>

#include <GL/gl.h>
#include <GL/freeglut.h>


class Textbox : public Game_object
{
  public:
    Textbox(bool draw_me=true,double red = 0.0, double green = 0.0, double blue = 0.0);

    // Disable default copy constructor and default assignment
    // This will prevent accidental use.
    Textbox(const Textbox &);
    const Textbox &operator=(const Textbox &);
    static Gpl_type get_member_variable_type(const std::string& name);
  private:
    static std::map<const std::string, Gpl_type> var_types;
    virtual void build_display_list();

    std::string m_text;
    double m_size;
    int m_spacing;
    GLUquadricObj *m_quadric;
};

#endif // #ifndef TEXTBOX_H
