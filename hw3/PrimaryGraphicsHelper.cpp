/*
 * File: PrimaryGraphicsHelper.cpp
 * Author: Jared McKneely
 * Description: Implementation file for PrimaryGraphicsHelper, a helper class
 *              used for drawing a complex scene.
 */

#include <GlewException.h>
#include <PrimaryGraphicsHelper.h>

// Globals

// Constructor
PrimaryGraphicsHelper::PrimaryGraphicsHelper() { }

// Destructor
PrimaryGraphicsHelper::~PrimaryGraphicsHelper() { }

// display() member function
// Primary OpenGL display function
// Callback for glutDisplayFunc()
void PrimaryGraphicsHelper::display() {
  
}

// reshape() member function
// Primary OpenGL window resize function
// Callback for glutReshapeFunc()
void PrimaryGraphicsHelper::reshape(int w, int h) {
  
}

// display() member function
// Primary OpenGL arrow key handler function
// Callback for glutSpecialFunc()
void PrimaryGraphicsHelper::special(int key, int x, int y) {
  
}

// display() member function
// Primary OpenGL keyboard handler function
// Callback for glutKeyboardFunc()
void PrimaryGraphicsHelper::key(unsigned char ch, int x, int y) {
  
}

// initializeGlew() public helper method
// Tries to initialize GLEW (throws a GlewException if it fails)
void PrimaryGraphicsHelper::initializeGlew() {
    if (glewInit() != GLEW_OK) { throw GlewException(); }
}