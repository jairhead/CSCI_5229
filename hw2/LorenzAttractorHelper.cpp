/*
 * File: LorenzAttractorHelper.cpp
* Author: Jared McKneely
 * Description: Implementation file for LorenzAttractorHelper, a helper class
 *              used for drawing the Lorenz Attractor with GLUT callbacks.
 */

 #include <LorenzAttractorHelper.h>

// Display Globals
int th = 50;    // Azimuth of view angle
int ph = -50;   // Elevation of view angle
int mode = 1;   // Dimension (1-4)
double z = 0.0; // Z variable
double w = 1.0; // W variable

// Lorenz Attractor Globals
double sigma = 10;
double beta = 2.6666;
double rho = 28;
double dt = 0.001;
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
  glClear(GL_COLOR_BUFFER_BIT);
  glLoadIdentity();
  glRotated(ph, 1, 0, 0);
  glRotated(th, 0, 1, 0);

  // Display the axes
  createAxes();

  // Draw the Lorenz Attractor
  double x = 1.0;
  double y = 1.0;
  double z = 1.0;
  glColor3d(0.0, 0.5, 0.5);
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
  // Key switch
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
      break;
    case 2:
      mode = ch - '0';
      z = 0;
      break;
    case 3:
      mode = ch - '0';
      break;
    case 4:
      mode = ch - '0';
      w = 1;
      break;
  }
}

// computeEulerStep() private member function
// Helper method that calculates a single explicit Euler integration step
void LorenzAttractorHelper::computeEulerStep(double &x, double &y, double &z) {  
  x += (dt * (sigma * (y - x)));
  y += (dt * ((x * (rho - z)) - y));
  z += (dt * ((x * y) - (beta * z)));
}

// displayText private member function
// Helper method that displays a string to the scene
void LorenzAttractorHelper::displayText(std::string text) {
  for (size_t i = 0; i < text.size(); i++) {
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
  }
}

// createAxes() private member function
// Helper method that displays the x, y, and z axes, puts dots on the ends, and labels them
void LorenzAttractorHelper::createAxes() {
  // Draw grey x, y, z axes
  glColor3d(0.35, 0.35, 0.35);
  glLineWidth(1.0);
  glBegin(GL_LINES);
  glVertex3d(0.0, 0.0, 0.0);
  glVertex3d(1.0, 0.0, 0.0);
  glVertex3d(0.0, 0.0, 0.0);
  glVertex3d(0.0, 1.0, 0.0);
  glVertex3d(0.0, 0.0, 0.0);
  glVertex3d(0.0, 0.0, 1.0);
  glEnd();

  // Draw dots at end of axes
  glPointSize(10);
  glEnable(GL_POINT_SMOOTH);
  glBegin(GL_POINTS);
  glVertex4d(0, 0, 0, w);
  glVertex4d(1, 0, 0, w);
  glVertex4d(0, 1, 0, w);
  glVertex4d(0, 0, 1, w);
  glEnd();
  glDisable(GL_POINT_SMOOTH);

  // Label axes in white
  glColor3d(1, 1, 1);
  glRasterPos3d(1.1, 0, 0);
  displayText("x");
  glRasterPos3d(0, 1.1, 0);
  displayText("y");
  glRasterPos3d(0, 0, 1.1);
  displayText("z");
}

// errorCheck() private member function
// Helper method that checks errors from OpenGL
void LorenzAttractorHelper::errorCheck(const char* where)
{
   int error = glGetError();
   if (error) {
     std::cout << "LorenzAttractorHelper::errorCheck: [ERROR] " << gluErrorString(error) << where << std::endl;
   }
}
