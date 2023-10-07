#ifndef _RECTANGULAR_PRISM_H
#define _RECTANGULAR_PRISM_H
/*
 * File: RectangularPrism.h
 * Author: Jared McKneely
 * Description: Header file for the RectangularPrism class
 */

#include "BaseObject.h"

class RectangularPrism : public BaseObject {
  public:
    RectangularPrism();
    ~RectangularPrism();
    void color(double r, double g, double b);
    void draw();
  protected:
    double red = 1.0;
    double green = 1.0;
    double blue = 1.0;
};

#endif
