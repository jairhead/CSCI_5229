#ifndef _BASE_OBJECT_H
#define _BASE_OBJECT_H
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
    void scaleX(double x) {xPos = x;}
    void scaleY(double y) {yPos = y;}
    void scaleZ(double z) {zPos = z;}
    void scale(double dx, double dy, double dz) {xScaling = dx; yScaling = dy; zScaling = dz;}
    void translate(double x, double y, double z) {xPos = x; yPos = y; zPos = z;}
    void rotate(double th) {theta = th;}
    double getX() {return xPos;}
    double getY() {return yPos;}
    double getZ() {return zPos;}
    double getTheta() {return theta;}
    virtual void color() = 0;
    virtual void draw() = 0;
    virtual ~BaseObject() {}
  protected:
    double xPos = 0.0;
    double yPos = 0.0;
    double zPos = 0.0;
    double xScaling = 1.0;
    double yScaling = 1.0;
    double zScaling = 1.0;
    double theta = 0.0;
    bool lightingEnabled = true;
};

#endif
