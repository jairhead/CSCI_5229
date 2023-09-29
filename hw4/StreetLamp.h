#ifndef _STREET_LAMP_H
#define _STREET_LAMP_H
/*
 * File: StreetLamp.h
 * Author: Jared McKneely
 * Description: Header file for the StreetLamp class
 */

#include <iostream>
#include "BaseObject.h"
#include "RectangularPrism.h"

class StreetLamp : public BaseObject {
  public:
    StreetLamp();
    ~StreetLamp();
    void translate(double x, double y, double z);
    void color(bool day);
    void rotate(double th);
    void draw();
  protected:
    double sine(double angle);
    double cosine(double angle);
    RectangularPrism *pole;
    RectangularPrism *cantilever;
    RectangularPrism *lamp;
    bool dayTime = true;
    double poleC[3][3] = {{0.43,0.43,0.43},{0.43,0.43,0.43},{0,0,0}};
    double lightC[3][3] = {{0.87,0.77,0},{0.87,0.77,0},{0.87,0.77,0}};
    const int d = 15;
};

#endif
