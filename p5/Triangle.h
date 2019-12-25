// updated Mon Apr 15 17:27:22 PDT 2019

#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Game_object.h"
#include <string>

class Triangle : public Game_object
{
  public:
    Triangle(bool draw_me=true,double red = 0.0, double green = 1.0, double blue = 0.0);

    // Disable default copy constructor and default assignment
    // This will prevent accidental use.
    Triangle(const Triangle &);
    const Triangle &operator=(const Triangle &);
    static Gpl_type get_member_variable_type(const std::string& name);
  private:
    static std::map<const std::string, Gpl_type> var_types;
    int m_size;
    double m_rotation;
    double m_skew;

    virtual void updated(std::string name);
    virtual void build_display_list();

};

#endif // #ifndef TRIANGLE_H
