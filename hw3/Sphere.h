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
};

#endif
