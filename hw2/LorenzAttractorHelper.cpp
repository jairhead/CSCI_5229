/*
 * File: LorenzAttractorHelper.cpp
* Author: Jared McKneely
 * Description: Implementation file for LorenzAttractorHelper, a helper class
 *              used for drawing the Lorenz Attractor with GLUT callbacks.
 */

 #include <LorenzAttractorHelper.h>

// Display Globals
int th = 50;    // Azimuth of view angle
int ph = 50;    // Elevation of view angle
int mode = 1;   // Dimension (1-4)
double z = 0.0; // Z variable
double w = 1.0; // W variable

// Lorenz Attractor Globals
const double S = 10;
const double B = 2.6666;
const double R = 28;
const double DT = 0.001;
const double SCALING_FACTOR = 50.0;

// Constructor
LorenzAttractorHelper::LorenzAttractorHelper() { }

// Destructor
LorenzAttractorHelper::~LorenzAttractorHelper() { }

// display() member function
// Primary OpenGL display function
// Callback for glutDisplayFunc()
void LorenzAttractorHelper::display() {
  // Initialize the scene; set initial viewing angle
  std::cout << "LorenzAttractorHelper::display(): entrance" << std::endl;
  glClear(GL_COLOR_BUFFER_BIT);
  glLoadIdentity();
  glRotated(ph, 1, 0, 0);
  glRotated(th, 0, 1, 0);

  // Set white lines and draw x, y, z axes
  glColor3f(1, 1, 1);
  glLineWidth(1.0);
  glBegin(GL_LINES);
  glVertex3d(0.0, 0.0, 0.0);
  glVertex3d(1.0, 0.0, 0.0);
  glVertex3d(0.0, 0.0, 0.0);
  glVertex3d(0.0, 1.0, 0.0);
  glVertex3d(0.0, 0.0, 0.0);
  glVertex3d(0.0, 0.0, 1.0);
  glEnd();

  // Draw the Lorenz Attractor
  double x = 1.0;
  double y = 1.0;
  double z = 1.0;
  glColor3f(0.0f, 0.5f, 0.5f);
  glBegin(GL_LINE_STRIP);
  for (int i = 0; i < 50000; i++) {
    glVertex3d(x / SCALING_FACTOR, y / SCALING_FACTOR, z / SCALING_FACTOR);
    computeEulerStep(x, y, z);
  }
  glEnd();

  // Flush and swap buffers
  glFlush();
  glutSwapBuffers();
}

// reshape() member function
// Primary OpenGL window resize function
// Callback for glutReshapeFunc()
void LorenzAttractorHelper::reshape(int w, int h) {
  std::cout << "LorenzAttractorHelper::reshape(): entrance" << std::endl; 
}

// display() member function
// Primary OpenGL arrow key handler function
// Callback for glutSpecialFunc()
void LorenzAttractorHelper::special(int key, int x, int y) {
  // Handle key display navigation
  std::cout << "LorenzAttractorHelper::special(): entrance" << std::endl;
  switch(key) {
    case GLUT_KEY_RIGHT:
      th += 2;
      break;
    case GLUT_KEY_LEFT:
      th -= 2;
      break;
    case GLUT_KEY_UP:
      ph += 2;
      break;
    case GLUT_KEY_DOWN:
      ph -= 2;
      break;
  }

  // Normalize azimuth and elevation
  th %= 360;
  ph %= 360;
  glutPostRedisplay();
}

// display() member function
// Primary OpenGL keyboard handler function
// Callback for glutKeyboardFunc()
void LorenzAttractorHelper::key(unsigned char ch, int x, int y) {
  // 
  std::cout << "LorenzAttractorHelper::key(): entrance" << std::endl;
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
  x = x + (DT * (S * (y - x)));
  y = y + (DT * ((x * (R - z)) - y));
  z = z + (DT * ((x * y) - (B * z)));
  //std::cout << "x = " << x << ", y = " << y << ", z = " << z << std::endl;
}
