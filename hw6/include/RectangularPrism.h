/*
 * File: RectangularPrism.h
 * Author: Jared McKneely
 * Description: Header file for the RectangularPrism class
 */

#ifndef _RECTANGULAR_PRISM_H
#define _RECTANGULAR_PRISM_H

#include "BaseObject.h"

class RectangularPrism : public BaseObject {
  public:
    RectangularPrism();
    ~RectangularPrism();
    void setTextureFactor(float tf);
    void color(float r, float g, float b);
    void scale(double dx, double dy, double dz);
    void draw();
  protected:
    float colorArray[4] = {1.0, 1.0, 1.0, 1.0};
    float specularArray[4] = {1.0, 1.0, 1.0, 1.0};
    float emissionArray[4] = {0.0, 0.0, 0.0, 1.0};
    double xScaling = 1.0;
    double yScaling = 1.0;
    double zScaling = 1.0;
    float texFact = 1.0;
};

#endif
