#ifndef _SPHERE_H
#define _SPHERE_H
/*
 * File: Sphere.h
 * Author: Jared McKneely
 * Description: Header file for the Sphere class
 */

#include <iostream>
#include "BaseObject.h"

class Sphere : public BaseObject {
  public:
    Sphere();
    Sphere(double x, double y, double z,
           double s, double th);
    ~Sphere();
    void draw();
  protected:
    double sine(double angle);
    double cosine(double angle);
    void vertex(double th, double ph);
    double scalingFactor = 1.0;
    const int d = 15;
};

#endif
