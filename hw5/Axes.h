#ifndef _AXES_H
#define _AXES_H
/*
 * File: Axes.h
 * Author: Jared McKneely
 * Description: Header file for the Axes class
 */

#include "BaseObject.h"

class Axes : public BaseObject {
  public:
    Axes();
    ~Axes();
    void setAxisColors(double r, double g, double b);
    void setTextColors(double r, double g, double b);
    void setLineThickness(double th);
    void draw();
  protected:
    double axisRed = 0.35;
    double axisGreen = 0.35;
    double axisBlue = 0.35;
    double textRed = 1.0;
    double textGreen = 1.0;
    double textBlue = 1.0;
    double thickness = 3.0;
    double w = 1.0;
    void displayText(std::string text);
};

#endif
