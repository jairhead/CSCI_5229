#ifndef _TREE_H
#define _TREE_H
/*
 * File: Tree.h
 * Author: Jared McKneely
 * Description: Header file for the Tree class
 */

#include <iostream>
#include "BaseObject.h"
#include "RectangularPrism.h"
#include "Sphere.h"

class Tree : public BaseObject {
  public:
    Tree();
    ~Tree();
    void translate(double x, double y, double z);
    void color(bool day);
    void rotate(double th);
    void draw();
  protected:
    Sphere *leaves;
    RectangularPrism *trunk;
    bool dayTime = true;
    double leavesC[3][3] = {{0.0,0.28,0.07},{0.0,0.28,0.07},{0.0,0.0,0.0}};
    double trunkC[3][3] = {{0.24,0.12,0.0},{0.24,0.12,0.0},{0.0,0.0,0.0}};
};

#endif
