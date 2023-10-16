/*
 * File: Utilities.h
 * Author: Jared McKneely
 * Description: Library for various graphics-related utilities
 */

#ifndef _UTILS_H
#define _UTILS_H

#include <fstream>

#include "GlutIncludes.h"
#include "GenericHomeworkException.h"

class Utilities {
  public:
    static void initializeGlew();
    static void errorCheck(std::string where);
    static void displayText(std::string text);
    static void loadBmp(std::string fileName);
};

#endif
