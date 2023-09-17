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

// display() member function
// Primary OpenGL display function
// Callback for glutDisplayFunc()
void LorenzAttractorHelper::display() {
  std::cout << "LorenzAttractorHelper::reshape(): enter function" << std::endl;
}

// reshape() member function
// Primary OpenGL window resize function
// Callback for glutReshapeFunc()
void LorenzAttractorHelper::reshape(int w, int h) {
  std::cout << "LorenzAttractorHelper::reshape(): enter function" << std::endl;
}

// display() member function
// Primary OpenGL arrow key handler function
// Callback for glutSpecialFunc()
void LorenzAttractorHelper::special(int key, int x, int y) {
  std::cout << "LorenzAttractorHelper::reshape(): enter function" << std::endl;
}

// display() member function
// Primary OpenGL keyboard handler function
// Callback for glutKeyboardFunc()
void LorenzAttractorHelper::key(unsigned char ch, int x, int y) {
  switch(ch) {
    // ESC = exit
    case 27:
      exit(0);
    // 0 = reset viewing angle
    case 0:
      th = 0;
      ph = 0;
      break;
    // 1 - 4 = switch dimensions
    case 1:
      mode = ch - '0';
    case 2:
      mode = ch - '0';
      z = 0;
    case 3:
      mode = ch - '0';
    case 4:
      mode = ch = '0';
      w = 1;
  }
}
