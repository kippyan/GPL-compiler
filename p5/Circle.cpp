// updated Thu Apr 25 21:55:15 PDT 2019

#include "Circle.h"
#include "gpl_assert.h"
using namespace std;

//Circle
/*static*/ std::map<const std::string, Gpl_type> Circle::var_types
{
  {"radius",          INT},
};

/*static*/ Gpl_type Circle::get_member_variable_type(const std::string& name)
{
  try {
    return Game_object::get_member_variable_type(name);//try base class members
  }
  catch(...)
  {
    return var_types.at(name);//now try derived class members
  }
}

Circle::Circle(bool draw_me, double red, double green, double blue)
  : Game_object(draw_me, red, green, blue)
{
    m_radius = 10;
    register_member_variable("radius", &m_radius);
    m_object_type = CIRCLE;

    // the width and height are derived from the radius
    m_w = 2*m_radius;
    m_h = 2*m_radius;

    // width and height are derived --> user cannot change them
    Status status;
    status = mark_member_variable_as_derived("w");
    assert(status == OK);
    status = mark_member_variable_as_derived("h");
    assert(status == OK);

    m_quadric = 0;
}

void Circle::updated(string name)
{
  if (name == "radius")
  {
    m_w = 2*m_radius;
    m_h = 2*m_radius;
  }
  m_display_list_dirty = true;
}

void Circle::build_display_list()
{
  assert(m_display_list);
  if (m_quadric == 0)
  {
    m_quadric = gluNewQuadric();
    gluQuadricDrawStyle(m_quadric, GLU_FILL);
  }
  glNewList(m_display_list, GL_COMPILE);
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glTranslated(m_x + m_radius, m_y + m_radius, 0);
  glColor3f(m_red, m_green, m_blue);
  gluDisk(m_quadric,
          /* innerRadius = */ 0,    // creates a hole in center
          /* outerRadius = */ m_radius,
          /* slices = */ 200, // use to be 20
          /* rings = */ 1
         );
  glPopMatrix();
  glEndList();

  // width and height are derived from the radius
  m_w = 2*m_radius;
  m_h = 2*m_radius;
}
