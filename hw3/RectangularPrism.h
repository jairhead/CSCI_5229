#ifndef _RECTANGULAR_PRISM_H
#define _RECTANGULAR_PRISM_H
/*
 * File: RectangularPrism.h
 * Author: Jared McKneely
 * Description: Header file for the Rectangular Prism class
 */

 #include <iostream>
 #include "BaseObject.h"

class RectangularPrism : public BaseObject {
  public:
    RectangularPrism();
    RectangularPrism(double r, double g, double b);
    ~RectangularPrism();
    void scale(double dx, double dy, double dz);
    void translate(double x, double y, double z);
    void color(double r, double g, double b);
    void draw();
  protected:
    double xScaling = 1.0;
    double yScaling = 1.0;
    double zScaling = 1.0;
    double red = 0.0;
    double green = 0.0;
    double blue = 0.0;
};

#endif
