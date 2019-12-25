// updated Thu Apr 25 21:55:23 PDT 2019

#include "Textbox.h"
#include "gpl_assert.h"
using namespace std;

//Textbox
/*static*/ std::map<const std::string, Gpl_type> Textbox::var_types
{
  {"text",            STRING},
  {"size",            DOUBLE},
  {"spacing",         INT},
};

/*static*/ Gpl_type Textbox::get_member_variable_type(const std::string& name)
{
  try {
    return Game_object::get_member_variable_type(name);//try base class members
  }
  catch(...)
  {
    return var_types.at(name);//now try derived class members
  }
}

Textbox::Textbox(bool draw_me, double red, double green, double blue)
  : Game_object(draw_me, red, green, blue)
{
    m_text = "";
    m_size = 0.1;
    m_spacing = 10;
    register_member_variable("text", &m_text); 
    register_member_variable("size", &m_size); 
    register_member_variable("spacing", &m_spacing); 
    m_object_type = TEXTBOX;
    m_h = (int) (100 * m_size) + 1;
    m_w = m_spacing;
}

void
Textbox::build_display_list()
{
  assert(m_display_list);

  glNewList(m_display_list, GL_COMPILE);
  glMatrixMode(GL_MODELVIEW);
  glColor3f(m_red, m_green, m_blue);
  double cur_x = m_x;

  for(unsigned int i = 0; i < m_text.length(); i++)
  {
    glPushMatrix();
    glTranslated(cur_x, m_y, 0);
    glScaled(m_size, m_size, 1);
    glutStrokeCharacter(GLUT_STROKE_ROMAN, m_text[i]);
    glPopMatrix();
    cur_x += (glutStrokeWidth(GLUT_STROKE_ROMAN,m_text[i])+m_spacing)*m_size;
  }
  glEndList();


  // update our height & width in case our size has changed
  m_h = (int) (100 * m_size) + 1;
  m_w = (int) cur_x - m_x;
}
