#ifndef _PAWN_H
#define _PAWN_H
/*
 * File: Pawn.h
 * Author: Jared McKneely
 * Description: Header file for the Pawn class
 */

#include "BaseObject.h"
#include "Sphere.h"

class Pawn : public BaseObject {
  public:
    Pawn();
    ~Pawn();
    void color(double r, double g, double b);
    void setTextureFactor(float tf);
    void setTexture(unsigned int *tex);
    void draw();
  protected:
    // Color & lighting variables
    double colorArray[3] = {1.0, 1.0, 1.0};
    float specularArray[4] = {0.8, 0.8, 0.8, 1.0};
    float emissionArray[4] = {0.0, 0.0, 0.0, 1.0};
    float diffuseArray[4] = {0.1, 0.1, 0.1, 1.0};

    // Geometry variables
    Sphere *top;
    const int d = 15;

    // Texture variables
    float texFact = 1.0;

    // Private member functions
    void drawCap(double r, double y, double yNorm);
    void drawCyl(double x1, double x2,
                 double y1, double y2,
                 double z1, double z2,
                 double ph);
    double sine(double angle);
    double cosine(double angle);
};

#endif
