/*
 * File: Utilities.h
 * Author: Jared McKneely
 * Description: Library for various graphics-related utilities
 */

#ifndef _UTILS_H
#define _UTILS_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>

#include "GlutIncludes.h"
#include "GenericHomeworkException.h"

class Utilities {
  public:
    static void initializeGlew();
    static void errorCheck(std::string where);
    static void displayText(std::string text);
    static unsigned int loadBmp(const char* fileName);
    static double sine(double angle);
    static double cosine(double angle);
    static double** loadElevationData(std::string fileName);
  private:
    static void reverseBytes(void *x, const int n);
};

#endif
