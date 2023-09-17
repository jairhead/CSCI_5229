/*
 * File: LorenzAttractorHelper.cpp
* Author: Jared McKneely
 * Description: Implementation file for LorenzAttractorHelper, a helper class
 *              used for drawing the Lorenz Attractor with GLUT callbacks.
 */

 #include <LorenzAttractorHelper.h>

// Globals
int th = 0;              // Azimuth of view angle
int ph = 0;              // Elevation of view angle
int mode = 1;            // Dimension (1-4)
double z = 0;            // Z variable
double w = 1;            // W variable
const double S = 10;
const double B = 2.6666;
const double R = 28;
const double DT = 0.001;

// Constructor
LorenzAttractorHelper::LorenzAttractorHelper() { }

// Destructor
LorenzAttractorHelper::~LorenzAttractorHelper() { }

// display() member function
// Primary OpenGL display function
// Callback for glutDisplayFunc()
void LorenzAttractorHelper::display() {
  // Initialize the scene; set initial viewing angle
  glClear(GL_COLOR_BUFFER_BIT);
  glLoadIdentity();
  glRotated(ph, 1, 0, 0);
  glRotated(th, 0, 1, 0);

  // Set white lines and draw x, y, z axes
  glColor3ub(255, 255, 255);
  glBegin(GL_LINES);
  glVertex3d(0, 0, 0);
  glVertex3d(1, 0, 0);
  glVertex3d(0, 0, 0);
  glVertex3d(0, 1, 0);
  glVertex3d(0, 0, 0);
  glVertex3d(0, 0, 1);

  // Draw the Lorenz Attractor
  glColor3ub(127, 50, 70);
  double x = 1;
  double y = 1;
  double z = 1;
  computeEulerStep(x, y, z);

  // Flush and swap buffers
  glFlush();
  glutSwapBuffers();
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
      mode = ch - '0';
      w = 1;
  }
}

// computeEulerStep() member function
// Calculates a single explicit Euler integration step
void LorenzAttractorHelper::computeEulerStep(double &x, double &y, double &z) {
  x += (DT * (S * (y - x)));
  y += (DT * ((x * (R - z)) - y));
  z += (DT * ((x * y) - (B * z)));
}
