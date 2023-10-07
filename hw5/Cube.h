#ifndef _CUBE_H
#define _CUBE_H
/*
 * File: Cube.h
 * Author: Jared McKneely
 * Description: Header file for the Cube class
 */

#include "BaseObject.h"

class Cube : public BaseObject {
  public:
    Cube();
    ~Cube();
    void draw();
};

#endif
