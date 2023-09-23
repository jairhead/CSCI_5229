/*
 * File: Cube.h
 * Author: Jared McKneely
 * Description: Header file for the Cube class
 */

#include <iostream>
#include "BaseObject.h"

class Cube : public BaseObject {
  public:
    Cube(double x, double y, double z,
         double dx, double dy, double dz,
         double th);
    ~Cube();
    void draw();
};
