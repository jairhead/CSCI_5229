#ifndef _MOUNTAIN_BACKDROP_H
#define _MOUNTAIN_BACKDROP_H
/*
 * File: MountainBackdrop.h
 * Author: Jared McKneely
 * Description: Header file for the Mountain Backdrop class
 */

#include <iostream>
#include "BaseObject.h"

class MountainBackdrop : public BaseObject {
  public:
    MountainBackdrop();
    ~MountainBackdrop();
    void scale(double dx, double dy, double dz);
    void translate(double x, double y, double z);
    void color(double r, double g, double b);
    void rotate(double th);
    void draw();
  protected:
    double xScaling = 0.1;
    double yScaling = 0.1;
    double zScaling = 0.1;
    double red = 0.17;
    double green = 0.17;
    double blue = 0.17;
};

#endif
