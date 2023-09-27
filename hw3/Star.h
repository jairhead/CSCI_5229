#ifndef _STAR_H
#define _STAR_H
/*
 * File: Moon.h
 * Author: Jared McKneely
 * Description: Header file for the Star class
 */

#include <iostream>
#include "BaseObject.h"

class Star : public BaseObject {
  public:
    Star();
    ~Star();
    void scale(double dx, double dy, double dz);
    void translate(double x, double y, double z);
    void color(double r, double g, double b);
    void rotate(double th);
    void draw();
  protected:
    double xScaling = 0.1;
    double yScaling = 0.1;
    double zScaling = 0.1;
    double red = 0.64;
    double green = 0.64;
    double blue = 0.64;
};

#endif
