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

#include "TopIncludes.h"
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
    static void crossProduct(double v_A[], double v_B[], double c_P[]);
    static int loadOBJ(const char* fileName);
    static int timeDifference(int currHr, int currMin, int hr, int min);
  private:
    static void reverseBytes(void *x, const int n);
    static void loadMaterial(const char* fileName);
    static void setMaterial(const char* name);
    static void readCoord(char* line, int n, float* x[], int* N, int* M);
    static void readFloat(char* line, int n, float x[]);
    static char* readLine(FILE* f);
    static char* readStr(char* line, const char* skip);
    static char* getWord(char** line);
    static int CRLF(char ch);
};

#endif
