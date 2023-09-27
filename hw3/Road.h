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
    void color(bool day);
    void rotate(double th);
    void draw();
  protected:
    double scalingFactor = 1.0;
    RectangularPrism *asphalt;
    RectangularPrism *leftStripe;
    RectangularPrism *rightStripe;
    RectangularPrism *centerLeftStripe;
    RectangularPrism *centerRightStripe;
    double asphaltC[3][3] = {{0.17,0.17,0.17},{0.17,0.17,0.17},{0,0,0}};
    double whiteStripeC[3][3] = {{0.86,0.86,0.86},{0.86,0.86,0.86},{0,0,0}};
    double orangeStripeC[3][3] = {{0.92,0.56,0.0},{0.92,0.56,0.0},{0,0,0}};
};

#endif
