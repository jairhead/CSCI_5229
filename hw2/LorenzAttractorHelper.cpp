/*
 * File: LorenzAttractorHelper.cpp
* Author: Jared McKneely
 * Description: Implementation file for LorenzAttractorHelper, a helper class
 *              used for drawing the Lorenz Attractor with GLUT callbacks.
 */

 #include <LorenzAttractorHelper.h>

// Display Globals
int th = 135;         // Azimuth of view angle
int ph = -30;         // Elevation of view angle
int mode = 1;         // Mode for modifying Lorenz Attractor values (1-4)
double w = 1.0;       // W variable
const double DIM = 2; // Dimension of orthogonal box

// Lorenz Attractor Globals
double sigma = 10;                  // sigma value (Lorenz Attractor computation)
double beta = 2.6666;               // beta value (Lorenz Attractor computation)
double rho = 28;                    // rho value (Lorenz Attractor computation)
double dt = 0.001;                  // Time step
const double SCALING_FACTOR = 50.0; // Divide by this to scale down the Lorenz Attractor
const int LORENZ_STEPS = 50000;     // Number of Explicit Euler Integration steps

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

  // Display the axes and draw Lorenz Attractor
  createAxes();
  createLorenzAttractor(1.0, 1.0, 1.0);

  // Flush and swap buffers
  glFlush();
  glutSwapBuffers();
}

// reshape() member function
// Primary OpenGL window resize function
// Callback for glutReshapeFunc()
void LorenzAttractorHelper::reshape(int w, int h) {
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

// display() member function
// Primary OpenGL arrow key handler function
// Callback for glutSpecialFunc()
void LorenzAttractorHelper::special(int key, int x, int y) {
  // Handle key display navigation
  if (key == GLUT_KEY_RIGHT) { th += 2; }
  else if (key == GLUT_KEY_LEFT) { th -= 2; }
  else if (key == GLUT_KEY_UP) { ph += 2; }
  else if (key == GLUT_KEY_DOWN) { ph -= 2; }

  // Normalize azimuth and elevation; redisplay
  th %= 360;
  ph %= 360;
  glutPostRedisplay();
}

// display() member function
// Primary OpenGL keyboard handler function
// Callback for glutKeyboardFunc()
void LorenzAttractorHelper::key(unsigned char ch, int x, int y) {
  // Handle alphanumeric keys
  if (ch == 27) { exit(0) ;}
  else if (ch == '0') { th = 0; ph = 0; }
  else if (ch == '1') { mode = ch - '0'; printLorenzAttractorParameters(); }
  else if (ch == '2') { mode = ch - '0'; printLorenzAttractorParameters(); }
  else if (ch == '3') { mode = ch - '0'; printLorenzAttractorParameters(); }
  else if (ch == '4') { mode = ch - '0'; printLorenzAttractorParameters(); }
  else if (ch == '+') {
    if (mode == 1) { sigma += 0.1; std::cout << "[Sigma + 0.1] "; printLorenzAttractorParameters(); }
    else if (mode == 2) { beta += 0.1; std::cout << "[Beta + 0.1] "; printLorenzAttractorParameters(); }
    else if (mode == 3) { rho += 1.0; std::cout << "[Rho + 1.0] "; printLorenzAttractorParameters(); }
    else if (mode == 4) { dt += 0.001; std::cout << "[dt + 0.001] "; printLorenzAttractorParameters(); }
  }
  else if (ch == '-') {
    if (mode == 1) { sigma -= 0.1; std::cout << "[Sigma - 0.1] "; printLorenzAttractorParameters(); }
    else if (mode == 2) { beta -= 0.1; std::cout << "[Beta - 0.1] "; printLorenzAttractorParameters(); }
    else if (mode == 3) { rho -= 1.0; std::cout << "[Rho - 1.0] "; printLorenzAttractorParameters(); }
    else if (mode == 4) { dt -= 0.001; std::cout << "[dt - 0.001] "; printLorenzAttractorParameters(); }
  }
  else { return; }

  // Redisplay
  glutPostRedisplay();
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
  glLineWidth(3.0);
  glBegin(GL_LINES);
  glVertex3d(0.0, 0.0, 0.0);
  glVertex3d(1.0, 0.0, 0.0);
  glVertex3d(0.0, 0.0, 0.0);
  glVertex3d(0.0, 1.0, 0.0);
  glVertex3d(0.0, 0.0, 0.0);
  glVertex3d(0.0, 0.0, 1.0);
  glEnd();
  errorCheck("LorenzAttractor::createAxes()");

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
  errorCheck("LorenzAttractor::createAxes()");

  // Label axes in white
  glColor3d(1, 1, 1);
  glRasterPos3d(1.1, 0, 0);
  displayText("x");
  glRasterPos3d(0, 1.1, 0);
  displayText("y");
  glRasterPos3d(0, 0, 1.1);
  displayText("z");
  errorCheck("LorenzAttractor::createAxes()");
}

// createLorenzAttractor() private member function
// Helper method that computes & displays the Lorenz Attractor
void LorenzAttractorHelper::createLorenzAttractor(double x, double y, double z) {
  // Set color and line style
  glColor3d(0.0, 0.5, 0.5);
  glLineWidth(1.0);
  glBegin(GL_LINE_STRIP);

  // Iterate for Explicit Euler Integration
  for (int i = 0; i < LORENZ_STEPS; i++) {
    glVertex4d(x / SCALING_FACTOR, y / SCALING_FACTOR, z / SCALING_FACTOR, w);
    computeEulerStep(x, y, z);
  }
  glEnd();
  errorCheck("LorenzAttractor::createLorenzAttractor()");
}

// errorCheck() private member function
// Helper method that checks errors from OpenGL
void LorenzAttractorHelper::errorCheck(std::string where) {
   int error = glGetError();
   if (error) {
     std::cout << "LorenzAttractorHelper::errorCheck: [ERROR] " << gluErrorString(error) << ", " << where << std::endl;
   }
}

// printLorenzAttractorParameters() private member function
// Prints the Lorenz Attractor parameters to the terminal
void LorenzAttractorHelper::printLorenzAttractorParameters() {
  // Print Mode
  std::cout << "Mode: ";
  if (mode == 1) { std::cout << "1 (Update Sigma)"; }
  else if (mode == 2) { std::cout << "2 (Update Beta)"; }
  else if (mode == 3) { std::cout << "3 (Update Rho)"; }
  else if (mode == 4) { std::cout << "4 (Update dt)"; }

  // Display Lorenz Attractor 
  std::cout << ", Sigma: " << sigma;
  std::cout << ", Beta: " << beta;
  std::cout << ", Rho: " << rho;
  std::cout << ", dt: " << dt;
  std::cout << std::endl;
}
