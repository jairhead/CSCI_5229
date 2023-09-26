#ifndef _ROAD_H
#define _ROAD_H
/*
 * File: Road.h
 * Author: Jared McKneely
 * Description: Header file for the Road class
 */

#include <iostream>
#include "BaseObject.h"
#include "RectangularPrism.h"

class Road : public BaseObject {
  public:
    Road();
    ~Road();
    void scale(double s);
    void translate(double x, double y, double z);
    void rotate(double th);
    void draw();
  protected:
    double scalingFactor = 1.0;
    RectangularPrism *asphalt;
    RectangularPrism *leftStripe;
    RectangularPrism *rightStripe;
    RectangularPrism *centerLeftStripe;
    RectangularPrism *centerRightStripe;
};

#endif
