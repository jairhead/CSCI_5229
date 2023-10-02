/*
 * File: PrimaryGraphicsHelper.h
 * Author: Jared McKneely
 * Description: Header file for the PrimaryGraphicsHelper class
 */

#include <iostream>
#include "GlutIncludes.h"

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
    static void initializeGlew();
  private:
    static void createAxes();
    static void displayText(std::string text);
    static void displayParams();
    static void errorCheck(std::string where);
    static void transitionToNight();
    static void transitionToDay();
};
