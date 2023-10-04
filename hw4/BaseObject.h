#ifndef _BASEOBJECT_H
#define _BASEOBJECT_H
/*
 * File: BaseObject.h
 * Author: Jared McKneely
 * Description: Header file for the BaseObject class, an abstract
 *              class used for 3D objects.
 */

 #include <iostream>
 #include "GlutIncludes.h"

class BaseObject {
  public:
    void setX(double x) {xPos = x;}
    void setY(double y) {yPos = y;}
    void setZ(double z) {zPos = z;}
    double getX() {return xPos;}
    double getY() {return yPos;}
    double getZ() {return zPos;}
    virtual void draw() = 0;
    virtual ~BaseObject() {}
  protected:
    double xPos = 0.0;
    double yPos = 0.0;
    double zPos = 0.0;
    double theta = 0.0;
};

#endif
