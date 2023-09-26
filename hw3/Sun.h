#ifndef _SUN_H
#define _SUN_H
/*
 * File: Sun.h
 * Author: Jared McKneely
 * Description: Header file for the Sun class
 */

#include <iostream>
#include "BaseObject.h"

class Sun : public BaseObject {
  public:
    Sun();
    ~Sun();
    void scale(double dx, double dy, double dz);
    void translate(double x, double y, double z);
    void color(double r, double g, double b);
    void draw();
  protected:
    double xScaling = 1.0;
    double yScaling = 1.0;
    double zScaling = 1.0;
    double red = 0.85;
    double green = 0.57;
    double blue = 0.0;
};

#endif
