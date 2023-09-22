/*
 * File: PrimaryGraphicsHelper.cpp
 * Author: Jared McKneely
 * Description: Implementation file for PrimaryGraphicsHelper, a helper class
 *              used for drawing a complex scene.
 */

#include "GenericHomeworkException.h"
#include "PrimaryGraphicsHelper.h"

// Globals
int th = 135;         // Azimuth of view angle
int ph = -30;         // Elevation of view angle
int mode = 1;         // Mode for modifying Lorenz Attractor values (1-4)
double w = 1.0;       // W variable
const double DIM = 2; // Dimension of orthogonal box

// Constructor
PrimaryGraphicsHelper::PrimaryGraphicsHelper() { }

// Destructor
PrimaryGraphicsHelper::~PrimaryGraphicsHelper() { }

// display() member function
// Primary OpenGL display function
// Callback for glutDisplayFunc()
void PrimaryGraphicsHelper::display() {
  //TODO: implement this!
}

// reshape() member function
// Primary OpenGL window resize function
// Callback for glutReshapeFunc()
void PrimaryGraphicsHelper::reshape(int w, int h) {
  // Switch to projection matrix; undo previous updates
  glViewport(0, 0, (RES * w), (RES * h));
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  // Calculate orthogonal projection
  double asp = 1.0;
  if (h > 0) { asp = (double)(w / h); }
  glOrtho((-asp * DIM), (asp * DIM), -DIM, DIM, -DIM, DIM);

  // Switch back to model matrix
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

// special() member function
// Primary OpenGL arrow key handler function
// Callback for glutSpecialFunc()
void PrimaryGraphicsHelper::special(int key, int x, int y) {
  // Handle key display navigation
  std::cout << "PrimaryGraphicsHelper::initializeGlew(): handling "
            << key << " key" << std::endl;
  if (key == GLUT_KEY_RIGHT) { th += 2; }
  else if (key == GLUT_KEY_LEFT) { th -= 2; }
  else if (key == GLUT_KEY_UP) { ph += 2; }
  else if (key == GLUT_KEY_DOWN) { ph -= 2; }

  // Normalize azimuth and elevation; redisplay
  th %= 360;
  ph %= 360;
  glutPostRedisplay();
}

// key() member function
// Primary OpenGL keyboard handler function
// Callback for glutKeyboardFunc()
void PrimaryGraphicsHelper::key(unsigned char ch, int x, int y) {
  // Handle alphanumeric keys
  std::cout << "PrimaryGraphicsHelper::initializeGlew(): handling "
            << ch << " key" << std::endl;
  if (ch == 27) { exit(0) ;}
  else if (ch == '0') { th = 0; ph = 0; }
  else { return; }

  // Redisplay
  glutPostRedisplay();
}

// initializeGlew() public helper method
// Tries to initialize GLEW (throws a GlewException if it fails)
void PrimaryGraphicsHelper::initializeGlew() {
  if (glewInit() != GLEW_OK) { throw GenericHomeworkException(); }
  std::cout << "PrimaryGraphicsHelper::initializeGlew(): GLEW initialization successful!"
            << std::endl;
}
