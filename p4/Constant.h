//File: Constant.h
#ifndef CONSTANT_H
#define CONSTANT_H
#include "Expression.h"
#include "gpl_type.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Textbox.h"
#include "Triangle.h"
#include "Pixmap.h"

class Constant : public Expression {
  public:
    virtual Constant*   evaluate() final;
    virtual int         as_int()    const=0;
    virtual double      as_double() const=0;
    virtual std::string as_string() const=0;
};

class Integer_constant : public Constant {
  private:
    int data;
  public:
    Integer_constant(int d) : data(d) {}
    virtual int         as_int()        const { return data; }
    virtual double      as_double()     const { return data; }
    virtual std::string as_string()     const { return std::to_string(data);}
    virtual Rectangle*  as_Rectangle()  const { throw INT; }
    virtual Circle*     as_Circle()     const { throw INT; }
    virtual Textbox*    as_Textbox()    const { throw INT; }
    virtual Triangle*   as_Triangle()   const { throw INT; }
    virtual Pixmap*     as_Pixmap()     const { throw INT; }
    virtual Animation_block* as_Animation_block() const { throw INT; }
    virtual Gpl_type type() const {return INT;}
};

class Double_constant : public Constant {
  private:
    double data;
  public:
    Double_constant(double d) : data(d) {}
    virtual int         as_int()        const { throw DOUBLE; }
    virtual double      as_double()     const { return data; }
    virtual std::string as_string()     const { return std::to_string(data);}
    virtual Rectangle*  as_Rectangle()  const { throw DOUBLE; }
    virtual Circle*     as_Circle()     const { throw DOUBLE; }
    virtual Textbox*    as_Textbox()    const { throw DOUBLE; }
    virtual Triangle*   as_Triangle()   const { throw DOUBLE; }
    virtual Pixmap*     as_Pixmap()     const { throw DOUBLE; }
    virtual Animation_block* as_Animation_block() const { throw DOUBLE; }
    virtual Gpl_type type() const {return DOUBLE;}
};

class String_constant : public Constant {
  private:
    std::string data;
  public:
    String_constant(const std::string& d) : data(d) {}
    virtual int         as_int()       const { throw STRING; }
    virtual double      as_double()    const { throw STRING; }
    virtual std::string as_string()    const { return data;}
    virtual Rectangle*  as_Rectangle() const { throw STRING; }
    virtual Circle*     as_Circle()    const { throw STRING; }
    virtual Textbox*    as_Textbox()   const { throw STRING; }
    virtual Triangle*   as_Triangle()  const { throw STRING; }
    virtual Pixmap*     as_Pixmap()    const { throw STRING; }
    virtual Animation_block* as_Animation_block() const { throw STRING; }
    virtual Gpl_type type() const {return STRING;}
};

class Rectangle_constant : public Constant {
  private:
    Rectangle* data;
  public:
    Rectangle_constant(Rectangle* d) : data(d) {}
    virtual int         as_int()       const { throw RECTANGLE; }
    virtual double      as_double()    const { throw RECTANGLE; }
    virtual std::string as_string()    const { throw RECTANGLE; }
    virtual Rectangle*  as_rectangle() const { return data; }
    virtual Circle*     as_circle()    const { throw  RECTANGLE; }
    virtual Textbox*    as_textbox()   const { throw  RECTANGLE; }
    virtual Triangle*   as_triangle()  const { throw  RECTANGLE; }
    virtual Pixmap*     as_pixmap()    const { throw  RECTANGLE; }
    virtual Animation_block* as_animation_block() const { throw RECTANGLE; }
    virtual Gpl_type    type()      const { return RECTANGLE; }
};

class Circle_constant : public Constant {
  private:
    Circle* data;
  public:
    Circle_constant(Circle* d) : data(d) {}
    virtual int         as_int()       const { throw CIRCLE; }
    virtual double      as_double()    const { throw CIRCLE; }
    virtual std::string as_string()    const { throw CIRCLE; }
    virtual Rectangle*  as_rectangle() const { throw  CIRCLE; }
    virtual Circle*     as_circle()    const { return data; }
    virtual Textbox*    as_textbox()   const { throw  CIRCLE; }
    virtual Triangle*   as_triangle()  const { throw  CIRCLE; }
    virtual Pixmap*     as_pixmap()    const { throw  CIRCLE; }
    virtual Animation_block* as_animation_block() const { throw CIRCLE; }
    virtual Gpl_type    type()      const { return CIRCLE; }
};

class Textbox_constant : public Constant {
  private:
    Textbox* data;
  public:
    Textbox_constant(Textbox* d) : data(d) {}
    virtual int         as_int()       const { throw TEXTBOX; }
    virtual double      as_double()    const { throw TEXTBOX; }
    virtual std::string as_string()    const { throw TEXTBOX; }
    virtual Rectangle*  as_rectangle() const { throw  TEXTBOX; }
    virtual Circle*     as_circle()    const { throw  TEXTBOX; }
    virtual Textbox*    as_textbox()   const { return data; }
    virtual Triangle*   as_triangle()  const { throw  TEXTBOX; }
    virtual Pixmap*     as_pixmap()    const { throw  TEXTBOX; }
    virtual Animation_block* as_animation_block() const { throw TEXTBOX; }
    virtual Gpl_type    type()      const { return TEXTBOX; }
};

class Triangle_constant : public Constant {
  private:
    Triangle* data;
  public:
    Triangle_constant(Triangle* d) : data(d) {}
    virtual int         as_int()       const { throw TRIANGLE; }
    virtual double      as_double()    const { throw TRIANGLE; }
    virtual std::string as_string()    const { throw TRIANGLE; }
    virtual Rectangle*  as_rectangle() const { throw  TRIANGLE; }
    virtual Circle*     as_circle()    const { throw  TRIANGLE; }
    virtual Textbox*    as_textbox()   const { throw  TRIANGLE; }
    virtual Triangle*   as_triangle()  const { return data; }
    virtual Pixmap*     as_pixmap()    const { throw  TRIANGLE; }
    virtual Animation_block* as_animation_block() const { throw TRIANGLE; }
    virtual Gpl_type    type()      const { return TRIANGLE; }
};

class Pixmap_constant : public Constant {
  private:
    Pixmap* data;
  public:
    Pixmap_constant(Pixmap* d) : data(d) {}
    virtual int         as_int()       const { throw PIXMAP; }
    virtual double      as_double()    const { throw PIXMAP; }
    virtual std::string as_string()    const { throw PIXMAP; }
    virtual Rectangle*  as_rectangle() const { throw  PIXMAP; }
    virtual Circle*     as_circle()    const { throw  PIXMAP; }
    virtual Textbox*    as_textbox()   const { throw  PIXMAP; }
    virtual Triangle*   as_triangle()  const { throw  PIXMAP; }
    virtual Pixmap*     as_pixmap()    const { return data; }
    virtual Animation_block* as_animation_block() const { throw PIXMAP; }
    virtual Gpl_type    type()      const { return PIXMAP; }
};

class Animation_block_constant : public Constant {
  private:
    Animation_block* data;
  public:
    Animation_block_constant(Animation_block* d) : data(d) {}
    virtual int         as_int()       const { throw ANIMATION_BLOCK; }
    virtual double      as_double()    const { throw ANIMATION_BLOCK; }
    virtual std::string as_string()    const { throw ANIMATION_BLOCK; }
    virtual Rectangle*  as_rectangle() const { throw  ANIMATION_BLOCK; }
    virtual Circle*     as_circle()    const { throw  ANIMATION_BLOCK; }
    virtual Textbox*    as_textbox()   const { throw  ANIMATION_BLOCK; }
    virtual Triangle*   as_triangle()  const { throw  ANIMATION_BLOCK; }
    virtual Pixmap*     as_pixmap()    const { throw ANIMATION_BLOCK; }
    virtual Animation_block* as_animation_block() const { return data; }
    virtual Gpl_type    type()      const { return ANIMATION_BLOCK; }
};

#endif
