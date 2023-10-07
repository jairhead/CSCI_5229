/*
 * File: PrimaryGraphicsHelper.cpp
 * Author: Jared McKneely
 * Description: Implementation file for PrimaryGraphicsHelper, a helper class
 *              used for drawing a complex scene.
 */

#include "PrimaryGraphicsHelper.h"

// Constructor
PrimaryGraphicsHelper::PrimaryGraphicsHelper() { }

// Destructor
PrimaryGraphicsHelper::~PrimaryGraphicsHelper() { }

// display() public member function
// Callback for glutDisplayFunc()
void PrimaryGraphicsHelper::display() { }

// reshape() public member function
// Callback for glutReshapeFunc()
void PrimaryGraphicsHelper::reshape(int w, int h) { }

// special() public member function
// Callback for glutSpecialFunc()
void PrimaryGraphicsHelper::special(int key, int x, int y) { }

// key() public member function
// Callback for glutKeyboardFunc()
void PrimaryGraphicsHelper::key(unsigned char ch, int x, int y) { }

// initializeGlew() public member function
// Tries to initialize GLEW (throws a GenericHomeworkException if it fails)
void PrimaryGraphicsHelper::initializeGlew() {
  #ifdef USEGLEW
  if (glewInit() != GLEW_OK) {throw GenericHomeworkException();}
  std::cout << "PrimaryGraphicsHelper::initializeGlew(): GLEW initialization successful!"
            << std::endl;
  #else
  std::cout << "PrimaryGraphicsHelper::initializeGlew(): Skipped GLEW initialization"
            << std::endl;
  #endif
}

// displayText private member function
// Helper method that displays a string to the scene
void PrimaryGraphicsHelper::displayText(std::string text) {
  for (size_t i = 0; i < text.size(); i++) {
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
  }
}

// displayParams private member function
// Helper method that displays parameters to the window
void PrimaryGraphicsHelper::displayParams() {
  // Create string
  std::string parameters = "[NULL]";

  // Display
  #ifdef USEGLEW
  displayText(parameters);
  #else
  std::cout << parameters << std::endl;
  #endif
}

// errorCheck() private member function
// Helper method that checks errors from OpenGL
void PrimaryGraphicsHelper::errorCheck(std::string where) {
  int error = glGetError();
  if (error) {
    std::cout << "PrimaryGraphicsHelper::errorCheck(): [ERROR] "
              << gluErrorString(error) << ", " << where
              << std::endl;
  }
}
