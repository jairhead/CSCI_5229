/*
 * File: Sphere.cpp
 * Author: Jared McKneely
 * Description: Implementation file for the Utilities class
 */

#include "Utilities.h"

// initializeGlew() public member function
// Tries to initialize GLEW (throws a GenericHomeworkException if it fails)
void Utilities::initializeGlew() {
  #ifdef USEGLEW
  if (glewInit() != GLEW_OK) {throw GenericHomeworkException();}
  std::cout << "PrimaryGraphicsHelper::initializeGlew(): GLEW initialization successful!"
            << std::endl;
  #else
  std::cout << "PrimaryGraphicsHelper::initializeGlew(): Skipped GLEW initialization"
            << std::endl;
  #endif
}

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
  for (size_t i = 0; i < text.size(); i++) {glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);}
  #else
  std::cout << parameters << std::endl;
  #endif
}

// loadBmp() public member function
// Contains logic to load a bitmap image into OpenGL as a texture
void Utilities::loadBmp(std::string fileName) {
  // Open file
  std::ifstream file;
  file.exceptions(ifstream::badbit);
  try {
    // Attempt to open the file
    file.open(fileName, std::ios::binary);

    // Check for little endian bitmap bits
    //char* byte
    //file.read();
  }
  catch (const ifstream::failure& e) {
    std::cout << e.what() << std::endl;
    exit(1);
  }
}
