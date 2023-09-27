#ifndef _MOON_H
#define _MOON_H
/*
 * File: Moon.h
 * Author: Jared McKneely
 * Description: Header file for the Moon class
 */

#include <iostream>
#include "BaseObject.h"

class Moon : public BaseObject {
  public:
    Moon();
    ~Moon();
    void scale(double dx, double dy, double dz);
    void translate(double x, double y, double z);
    void color(double r, double g, double b);
    void rotate(double th);
    void draw();
  protected:
    double xScaling = 0.15;
    double yScaling = 0.15;
    double zScaling = 0.15;
    double red = 0.64;
    double green = 0.64;
    double blue = 0.64;
};

#endif
