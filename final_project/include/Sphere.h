/*
 * File: Sphere.h
 * Author: Jared McKneely
 * Description: Header file for the Sphere class
 */

#ifndef _SPHERE_H
#define _SPHERE_H

#include "BaseObject.h"
#include "Utilities.h"

class Sphere : public BaseObject {
  public:
    Sphere();
    ~Sphere();
    void color(float r, float g, float b);
    void setSpecular(float r, float g, float b);
    void setEmission(float r, float g, float b);
    void setTextureFactor(float tf);
    void draw();
  protected:
    // Color & lighting variables
    float colorArray[3] = {1.0, 1.0, 1.0};
    float specularArray[4] = {1.0, 1.0, 1.0, 1.0};
    float emissionArray[4] = {0.0, 0.0, 0.0, 1.0};

    // Geometry variables
    const int increment = 10;
    double scalingFactor = 1.0;
    const int d = 15;

    // Texture variables
    float texFact = 1.0;

    // Private member functions
    void vertex(double th, double ph);
};

#endif
