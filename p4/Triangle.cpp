// updated Thu Apr 25 21:55:30 PDT 2019

#include "Triangle.h"
#include "gpl_assert.h"
using namespace std;

#include <GL/gl.h>
#include <GL/glu.h>

//Triangle
/*static*/ std::map<const std::string, Gpl_type> Triangle::var_types
{
  {"size",            INT},
  {"rotation",        DOUBLE},
  {"skew",            DOUBLE},
};

/*static*/ Gpl_type Triangle::get_member_variable_type(const std::string& name)
{
  try {
    return Game_object::get_member_variable_type(name);//try base class members
  }
  catch(...)
  {
    return var_types.at(name);//now try derived class members
  }
}

Triangle::Triangle(bool draw_me, double red, double green, double blue)
  : Game_object(draw_me, red, green, blue)
{
    m_size = 10;
    m_rotation = 0;
    m_skew = 1.0;
    register_member_variable("size", &m_size);
    register_member_variable("rotation", &m_rotation);
    register_member_variable("skew", &m_skew);
    m_object_type = TRIANGLE;

    // width and height are derived --> user cannot change them
    Status status;
    status = mark_member_variable_as_derived("w");
    assert(status == OK);
    status = mark_member_variable_as_derived("h");
    assert(status == OK);
}

void Triangle::updated(string name)
{
  m_display_list_dirty = true;
}

/* virtual */ void Triangle::build_display_list()
{
  assert(m_display_list);

  double midpoint_x = m_x + m_size/2.0;
  double top_point_y = 1.118 * m_size * m_skew + m_y;

  // assume size or skew changed:  recalculate the height and width
  m_w = m_size;
  m_h = (int) top_point_y - m_y;

  glNewList(m_display_list, GL_COMPILE);
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  if (m_rotation != 0)
  {
    double center_x = midpoint_x;
    double center_y = m_y + ((top_point_y - m_y) * .5);
    glTranslated(center_x, center_y, 0);
    glRotated(m_rotation, 0, 0, 1);
    glTranslated(-center_x, -center_y, 0);
  }
  glColor3f(m_red, m_green, m_blue);
  glBegin(GL_TRIANGLES);
    glVertex2i(m_x, m_y);
    glVertex2i(m_x + m_size, m_y);
    glVertex2i((int) midpoint_x, (int) top_point_y);
  glEnd();
  glPopMatrix();
  glEndList();
}
