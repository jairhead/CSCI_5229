/*
 * File: TallGrass.h
 * Author: Jared McKneely
 * Description: Implementation file for the TallGrass class, a child
 *              class of the BaseObject abstract class.
 */

#ifndef _TALL_GRASS_H
#define _TALL_GRASS_H

#include "BaseObject.h"
#include "Utilities.h"

class TallGrass : public BaseObject {
  public:
    TallGrass();
    ~TallGrass();
    void setTheta(double th);
    void setPhi(double ph);
    void draw();
  protected:
    // Protected member functions
    void drawBlade(double h, double r, double ph);

    // Geometry variables
    const int d = 120;
    double phi = 0.0;

    // Color & lighting variables
    float color1[4] = {0.39, 0.46, 0.17, 1.0};
    float color2[4] = {0.30, 0.45, 0.19, 1.0};
    float color3[4] = {0.45, 0.44, 0.19, 1.0};
    float specularArray[4] = {0.25, 0.25, 0.25, 1.0};
    float emissionArray[4] = {0.0, 0.0, 0.0, 1.0};
    float diffuseArray[4] = {0.1, 0.1, 0.1, 1.0};
};

#endif
