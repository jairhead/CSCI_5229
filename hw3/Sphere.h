/*
 * File: Sphere.h
 * Author: Jared McKneely
 * Description: Header file for the Sphere class
 */

 #include <iostream>
 #include "BaseObject.h"

class Sphere : public BaseObject {
  public:
    Sphere();
    ~Sphere();
    void draw();
}
