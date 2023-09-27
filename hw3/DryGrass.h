#ifndef _DRY_GRASS_H
#define _DRY_GRASS_H
/*
 * File: DryGrass.h
 * Author: Jared McKneely
 * Description: Header file for the House class
 */

#include <iostream>
#include "BaseObject.h"

class DryGrass : public BaseObject {
  public:
    DryGrass();
    ~DryGrass();
    void scale(double dx, double dy, double dz);
    void translate(double x, double y, double z);
    void color(double r, double g, double b);
    void rotate(double th);
    void draw();
  protected:
    double red = 0.26;
    double green = 0.29;
    double blue = 0.14;
    double xScaling = 0.75;
    double yScaling = 0.75;
    double zScaling = 0.75;
};

#endif
