#ifndef _HOUSE_H
#define _HOUSE_H
/*
 * File: House.h
 * Author: Jared McKneely
 * Description: Header file for the House class
 */

#include <iostream>
#include "BaseObject.h"

class House : public BaseObject {
  public:
    House();
    ~House();
    void scale(double dx, double dy, double dz);
    void translate(double x, double y, double z);
    void color(double r, double g, double b);
    void rotate(double th);
    void draw();
  protected:
    double red = 0.43;
    double green = 0.15;
    double blue = 0.0;
    double xScaling = 0.15;
    double yScaling = 0.15;
    double zScaling = 0.25;
};

#endif
