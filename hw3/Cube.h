#ifndef _CUBE_H
#define _CUBE_H
/*
 * File: Cube.h
 * Author: Jared McKneely
 * Description: Header file for the Cube class
 */

#include <iostream>
#include "BaseObject.h"

class Cube : public BaseObject {
  public:
    Cube();
    Cube(double x, double y, double z,
         double dx, double dy, double dz,
         double th);
    ~Cube();
    void draw();
};

#endif
