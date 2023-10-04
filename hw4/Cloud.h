#ifndef _CLOUD_H
#define _CLOUD_H
/*
 * File: Cloud.h
 * Author: Jared McKneely
 * Description: Header file for the Cloud class
 */

#include <iostream>
#include "BaseObject.h"
#include "Sphere.h"

class Cloud : public BaseObject {
  public:
    Cloud();
    ~Cloud();
    void translate(double x, double y, double z);
    void color(bool day);
    void rotate(double th);
    void draw();
  protected:
    Sphere *lobe1;
    Sphere *lobe2;
    Sphere *lobe3;
    bool dayTime = true;
    double cloudC[3][3] = {{0.9,0.9,0.9},{0.9,0.9,0.9},{0.11,0.11,0.11}};
};

#endif
