// updated Thu Apr 25 21:55:03 PDT 2019

#include "Rectangle.h"
#include "gpl_assert.h"

#include <GL/gl.h>

//Rectangle
/*static*/ std::map<const std::string, Gpl_type> Rectangle::var_types
{
  {"rotation",        DOUBLE},
};

/*static*/ Gpl_type Rectangle::get_member_variable_type(const std::string& name)
{
  try {
    return Game_object::get_member_variable_type(name);//try base class members
  }
  catch(...)
  {
    return var_types.at(name);//now try derived class members
    
  }
}
#include<iostream>
Rectangle::Rectangle(bool draw_me, double red, double green, double blue)
  : Game_object(draw_me, red, green, blue)
{
  m_rotation = 0;
  register_member_variable("rotation", &m_rotation);
  m_object_type = RECTANGLE;
}

/* virtual */ void Rectangle::build_display_list()
{
  assert(m_display_list);

  glNewList(m_display_list, GL_COMPILE);
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  if (m_rotation != 0)
  {
    double center_x = m_x + m_w/2.0;
    double center_y = m_y + m_h/2.0;
    glTranslated(center_x, center_y, 0);
    glRotated(m_rotation, 0, 0, 1);
    glTranslated(-center_x, -center_y, 0);
  }

  glColor3f(m_red, m_green, m_blue);
  glBegin(GL_QUADS);
    glVertex2i(m_x, m_y);
    glVertex2i(m_x + m_w, m_y);
    glVertex2i(m_x + m_w, m_y + m_h);
    glVertex2i(m_x, m_y + m_h);
  glEnd();
  glPopMatrix();
  glEndList();
}
