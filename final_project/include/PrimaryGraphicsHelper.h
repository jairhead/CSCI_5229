/*
 * File: PrimaryGraphicsHelper.h
 * Author: Jared McKneely
 * Description: Header file for the PrimaryGraphicsHelper class
 */

#ifndef _PRIMARY_GRAPHICS_HELPER_H
#define _PRIMARY_GRAPHICS_HELPER_H

#include "GlutIncludes.h"
#include "Utilities.h"
#include "WeatherScene.h"

class PrimaryGraphicsHelper {
  public:
    PrimaryGraphicsHelper();
    ~PrimaryGraphicsHelper();
    static void init();
    static void display();
    static void reshape(int w, int h);
    static void special(int key, int x, int y);
    static void key(unsigned char ch, int x, int y);
    static void idle();
  private:
    static void displayParams();
};

#endif
