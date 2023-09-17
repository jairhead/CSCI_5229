/*
 * File: LorenzAttractorHelper.cpp
* Author: Jared McKneely
 * Description: Implementation file for LorenzAttractorHelper, a helper class
 *              used for drawing the Lorenz Attractor with GLUT callbacks.
 */

 #include <LorenzAttractorHelper.h>

// Constructor
LorenzAttractorHelper::LorenzAttractorHelper() { }

// Destructor
LorenzAttractorHelper::~LorenzAttractorHelper() { }

// display()
// Primary OpenGL display function
// Callback for glutDisplayFunc()
void LorenzAttractorHelper::display() {
  std::cout << "LorenzAttractorHelper::reshape(): enter function" << std::endl;
}

// reshape()
// Primary OpenGL window resize function
// Callback for glutReshapeFunc()
void LorenzAttractorHelper::reshape(int w, int h) {
  std::cout << "LorenzAttractorHelper::reshape(): enter function" << std::endl;
}

// display()
// Primary OpenGL arrow key handler function
// Callback for glutSpecialFunc()
void LorenzAttractorHelper::special(int key, int x, int y) {
  std::cout << "LorenzAttractorHelper::reshape(): enter function" << std::endl;
}

// display()
// Primary OpenGL keyboard handler function
// Callback for glutKeyboardFunc()
void LorenzAttractorHelper::key(unsigned char ch, int x, int y) {
  std::cout << "LorenzAttractorHelper::reshape(): enter function" << std::endl;
}
