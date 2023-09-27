/*
 * File: PrimaryGraphicsHelper.cpp
 * Author: Jared McKneely
 * Description: Implementation file for PrimaryGraphicsHelper, a helper class
 *              used for drawing a complex scene.
 */

#include "PrimaryGraphicsHelper.h"
#include "GenericHomeworkException.h"

#include "Cube.h"
#include "Sphere.h"
#include "RectangularPrism.h"
#include "Sun.h"
#include "Moon.h"
#include "Road.h"
#include "House.h"
#include "DryGrass.h"

// Display Parameter Globals
int th = -45;         // Azimuth of view angle
int ph = 30;          // Elevation of view angle
int mode = 1;         // Mode for modifying display values
double w = 1.0;       // W variable
const double DIM = 2; // Dimension of orthogonal box

// 3D Object Globals
RectangularPrism *grass;
RectangularPrism *skyLeft;
RectangularPrism *skyRight;
RectangularPrism *skyBack;
Road *road;
Sun *sun;
Moon *moon;
House *redHouse;
House *blueHouse;
House *greenHouse;
House *yellowHouse;
DryGrass *dryGrass1;
DryGrass *dryGrass2;
DryGrass *dryGrass3;
DryGrass *dryGrass4;

// Constructor
PrimaryGraphicsHelper::PrimaryGraphicsHelper() { }

// Destructor
PrimaryGraphicsHelper::~PrimaryGraphicsHelper() { }

// init() public member function
// Initializes all objects for displaying
void PrimaryGraphicsHelper::init() {
  grass = new RectangularPrism();
  skyLeft = new RectangularPrism();
  skyRight = new RectangularPrism();
  skyBack = new RectangularPrism();
  road = new Road();
  sun = new Sun();
  moon = new Moon();
  redHouse = new House();
  blueHouse = new House();
  greenHouse = new House();
  yellowHouse = new House();
  dryGrass1 = new DryGrass();
  dryGrass2 = new DryGrass();
  dryGrass3 = new DryGrass();
  dryGrass4 = new DryGrass();
}

// display() public member function
// Primary OpenGL display function
// Callback for glutDisplayFunc()
void PrimaryGraphicsHelper::display() {
  // Initialize the scene; set initial viewing angle
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);
  glLoadIdentity();
  glRotated(ph, 1, 0, 0);
  glRotated(th, 0, 1, 0);

  // Draw axes
  createAxes();

  // Draw grass
  grass->scale(1.0, 0.01, 1.0);
  grass->color(0.3, 0.69, 0.12);
  grass->draw();
  errorCheck("PrimaryGraphicsHelper::display() grass");

  // Draw the road
  road->draw();
  errorCheck("PrimaryGraphicsHelper::display() road");

  // Draw sky
  double skyRed = 0.0; double skyGreen = 0.24; double skyBlue = 0.76;
  skyLeft->scale(0.01, 0.5, 1.0);
  skyLeft->translate(-1.0, 0.5, 0.0);
  skyLeft->color(skyRed, skyGreen, skyBlue);
  skyRight->scale(0.01, 0.5, 1.0);
  skyRight->translate(1.0, 0.5, 0.0);
  skyRight->color(skyRed, skyGreen, skyBlue);
  skyBack->scale(1.0, 0.5, 0.01);
  skyBack->translate(0.0, 0.5, -1.0);
  skyBack->color(skyRed, skyGreen, skyBlue);
  skyLeft->draw();
  skyRight->draw();
  skyBack->draw();
  errorCheck("PrimaryGraphicsHelper::display() sky");

  // Draw the red house
  redHouse->color(0.61, 0.15, 0.15);
  redHouse->translate(-0.60, 0.0, 0.55);
  redHouse->rotate(90.0);
  redHouse->draw();
  errorCheck("PrimaryGraphicsHelper::display() red house");

  // Draw the blue house
  blueHouse->color(0.21, 0.42, 0.61);
  blueHouse->scale(0.15, 0.15, 0.20);
  blueHouse->translate(-0.55, 0.0, 0.10);
  blueHouse->rotate(90.0);
  blueHouse->draw();
  errorCheck("PrimaryGraphicsHelper::display() blue house");

  // Draw the green house
  greenHouse->color(0.21, 0.61, 0.34);
  greenHouse->scale(0.15, 0.15, 0.22);
  greenHouse->translate(-0.57, 0.0, -0.35);
  greenHouse->rotate(90.0);
  greenHouse->draw();
  errorCheck("PrimaryGraphicsHelper::display() green house");

  // Draw the yellow house
  redHouse->color(0.61, 0.59, 0.21);
  redHouse->translate(0.60, 0.0, 0.10);
  redHouse->rotate(90.0);
  redHouse->draw();
  errorCheck("PrimaryGraphicsHelper::display() red house");

  // Draw the unkempt grass
  dryGrass1->translate(0.60, 0.0, 0.45);
  dryGrass1->draw();
  dryGrass2->translate(0.45, 0.0, -0.60);
  dryGrass2->draw();
  dryGrass3->translate(-0.45, 0.0, -0.72);
  dryGrass3->draw();
  dryGrass4->translate(0.55, 0.0, 0.67);
  dryGrass4->draw();
  errorCheck("PrimaryGraphicsHelper::display() dry grass");

  // Draw the sun
  sun->translate(0.25, 0.5, -0.97);
  sun->rotate(90.0);
  sun->draw();
  errorCheck("PrimaryGraphicsHelper::display() sun");

  // Draw the moon
  moon->translate(0.12, 0.45, -0.98);
  moon->rotate(90.0);
  moon->draw();
  errorCheck("PrimaryGraphicsHelper::display() moon");

  // Flush and swap buffers
  glFlush();
  glutSwapBuffers();
}

// reshape() public member function
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

// special() public member function
// Primary OpenGL arrow key handler function
// Callback for glutSpecialFunc()
void PrimaryGraphicsHelper::special(int key, int x, int y) {
  // Handle key display navigation
  if (key == GLUT_KEY_RIGHT) { th += 1; }
  else if (key == GLUT_KEY_LEFT) { th -= 1; }
  else if (key == GLUT_KEY_UP) { ph += 1; }
  else if (key == GLUT_KEY_DOWN) { ph -= 1; }

  // Normalize azimuth and elevation; redisplay
  th %= 360;
  ph %= 360;
  glutPostRedisplay();
}

// key() public member function
// Primary OpenGL keyboard handler function
// Callback for glutKeyboardFunc()
void PrimaryGraphicsHelper::key(unsigned char ch, int x, int y) {
  // Handle alphanumeric keys
  if (ch == 27) { exit(0) ;}
  else if (ch == '0') { th = 0; ph = 0; }
  else { return; }

  // Redisplay
  glutPostRedisplay();
}

// initializeGlew() public member function
// Tries to initialize GLEW (throws a GlewException if it fails)
void PrimaryGraphicsHelper::initializeGlew() {
  if (glewInit() != GLEW_OK) { throw GenericHomeworkException(); }
  std::cout << "PrimaryGraphicsHelper::initializeGlew(): GLEW initialization successful!"
            << std::endl;
}

// createAxes() private member function
// Helper method that displays the x, y, and z axes, puts dots on the ends, and labels them
void PrimaryGraphicsHelper::createAxes() {
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
  errorCheck("PrimaryGraphicsHelper::createAxes() draw axes");

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
  errorCheck("PrimaryGraphicsHelper::createAxes() draw dots");

  // Label axes in white
  glColor3d(1.0, 1.0, 1.0);
  glRasterPos3d(1.1, 0, 0);
  displayText("x");
  glRasterPos3d(0, 1.1, 0);
  displayText("y");
  glRasterPos3d(0, 0, 1.1);
  displayText("z");
  errorCheck("PrimaryGraphicsHelper::createAxes() label axes");
}

// displayText private member function
// Helper method that displays a string to the scene
void PrimaryGraphicsHelper::displayText(std::string text) {
  for (size_t i = 0; i < text.size(); i++) {
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
  }
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
