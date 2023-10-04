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
    void rotate(double th);
    void draw();
  protected:
    double sine(double angle);
    double cosine(double angle);
    double xScaling = 0.15;
    double yScaling = 0.15;
    double zScaling = 0.15;
    double red = 0.83;
    double green = 0.6;
    double blue = 0.14;
    const int d = 15;
};

#endif
