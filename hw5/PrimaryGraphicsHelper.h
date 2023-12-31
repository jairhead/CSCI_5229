/*
 * File: PrimaryGraphicsHelper.h
 * Author: Jared McKneely
 * Description: Header file for the PrimaryGraphicsHelper class
 */

#include <iostream>
#include "GlutIncludes.h"
#include "GenericHomeworkException.h"
#include "ProjectionManager.h"
#include "LightManager.h"

#include "Axes.h"
#include "ChessBoard.h"
#include "Pawn.h"
#include "Rook.h"

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
    static void displayText(std::string text);
    static void displayParams();
    static void errorCheck(std::string where);
    static double sine(double angle);
    static double cosine(double angle);
};
