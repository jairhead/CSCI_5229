/*
 * File: BaseObject.h
 * Author: Jared McKneely
 * Description: Header file for the BaseObject class, an abstract
 *              class used for 3D objects.
 */

#ifndef _BASE_OBJECT_H
#define _BASE_OBJECT_H

#include "GlutIncludes.h"

class BaseObject {
  public:
    void scaleX(double x) {posArray[0] = x;}
    void scaleY(double y) {posArray[1] = y;}
    void scaleZ(double z) {posArray[2] = z;}
    virtual void scale(double dx, double dy, double dz) {scaleArray[0] = dx; scaleArray[1] = dy; scaleArray[2] = dz;}
    void translate(double x, double y, double z) {posArray[0] = x; posArray[1] = y; posArray[2] = z;}
    void rotate(double th) {theta = th;}
    void setTexture(unsigned int *tex) {texture = tex; textureEnabled = true;}
    void setShiny(float shiny) {shinyFactor = shiny;}
    double getX() {return posArray[0];}
    double getY() {return posArray[1];}
    double getZ() {return posArray[2];}
    double getTheta() {return theta;}
    float getShiny() {return shinyFactor;}
    void enableLighting() {lightingEnabled = true;}
    void disableLighting() {lightingEnabled = false;}
    void enableTexture() {textureEnabled = true;}
    void disableTexture() {textureEnabled = false;}
    virtual void draw() = 0;
    virtual ~BaseObject() {}
  protected:
    // Position attributes
    double posArray[3] = {0.0, 0.0, 0.0};
    double scaleArray[3] = {1.0, 1.0, 1.0};
    double theta = 0.0;

    // Lighting attributes
    float shinyFactor = 1.0;
    bool lightingEnabled = true;

    // Texture attributes
    unsigned int *texture = nullptr;
    bool textureEnabled = false;
};

#endif
