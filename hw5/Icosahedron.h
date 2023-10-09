#ifndef _ICOSAHEDRON_H
#define _ICOSAHEDRON_H
/*
 * File: Icosahedron.h
 * Author: Jared McKneely
 * Description: Header file for the Icosahedron class
 */

#include "BaseObject.h"

class Icosahedron : public BaseObject {
  public:
    Icosahedron();
    ~Icosahedron();
    void color(double r, double g, double b);
    void draw();
  protected:
    double colorArray[3] = {1.0, 1.0, 1.0};
    const int numSides = 20;
    const int index[20][3] = {
      { 2, 1, 0}, { 3, 2, 0}, { 4, 3, 0}, { 5, 4, 0}, { 1, 5, 0},
      {11, 6, 7}, {11, 7, 8}, {11, 8, 9}, {11, 9,10}, {11,10, 6},
      { 1, 2, 6}, { 2, 3, 7}, { 3, 4, 8}, { 4, 5, 9}, { 5, 1,10},
      { 2, 7, 6}, { 3, 8, 7}, { 4, 9, 8}, { 5,10, 9}, { 1, 6,10}
    };
    const double vertices[12][3] = {
      { 0.000, 0.000, 1.000}, { 0.894, 0.000, 0.447}, { 0.276, 0.851, 0.447},
      {-0.724, 0.526, 0.447}, {-0.724,-0.526, 0.447}, { 0.276,-0.851, 0.447},
      { 0.724, 0.526,-0.447}, {-0.276, 0.851,-0.447}, {-0.894, 0.000,-0.447},
      {-0.276,-0.851,-0.447}, { 0.724,-0.526,-0.447}, { 0.000, 0.000,-1.000}
    };
    void drawTriangle(double vertex1[3], double vertex2[3], double vertex3[3]);
};

#endif
