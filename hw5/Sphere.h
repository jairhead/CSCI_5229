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
    ~Sphere();
    void color(float r, float g, float b);
    void draw();
  protected:
    double scalingFactor = 1.0;
    const int d = 15;
    float colorArray[3] = {1.0, 1.0, 1.0};
    float specularArray[4] = {1.0, 1.0, 1.0, 1.0};
    float emissionArray[4] = {0.0, 0.0, 0.0, 1.0};
    const int increment = 10;
    double sine(double angle);
    double cosine(double angle);
    void vertex(double th, double ph);
};

#endif
