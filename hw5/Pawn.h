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
    void draw();
  protected:
    Sphere *top;
    const int d = 15;
    double colorArray[3] = {1.0, 1.0, 1.0};
    float specularArray[4] = {0.8, 0.8, 0.8, 1.0};
    float emissionArray[4] = {0.0, 0.0, 0.0, 1.0};
    float diffuseArray[4] = {0.1, 0.1, 0.1, 1.0};
    double sine(double angle);
    double cosine(double angle);
};

#endif
