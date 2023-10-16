/*
 * File: Sphere.cpp
 * Author: Jared McKneely
 * Description: Implementation file for the Utilities class
 */

#include "Utilities.h"

// errorCheck() public member function
// Checks errors from OpenGL
void Utilities::errorCheck(std::string where) {
  int error = glGetError();
  if (error) {
    std::cout << "PrimaryGraphicsHelper::errorCheck(): [ERROR] "
              << gluErrorString(error) << ", " << where
              << std::endl;
  }
}

// displayText() public member function
// Displays a string to the scene
void Utilities::displayText(std::string text) {
  #ifdef USEGLEW
  for (size_t i = 0; i < text.size(); i++) {
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
  }
  #else
  std::cout << parameters << std::endl;
  #endif
}

// loadBmp() public member function
// Contains logic to load a bitmap image into OpenGL
void Utilities::loadBmp(std::string file) {

}
