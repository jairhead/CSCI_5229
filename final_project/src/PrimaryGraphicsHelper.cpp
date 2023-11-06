/*
 * File: PrimaryGraphicsHelper.cpp
 * Author: Jared McKneely
 * Description: Implementation file for PrimaryGraphicsHelper, a helper class
 *              used for drawing a complex scene.
 */

#include "PrimaryGraphicsHelper.h"

// Member Objects
ProjectionManager *projection = nullptr;
WeatherScene* scene = nullptr;

// Control Globals
int displayMode = 1;
bool drawAxes = true;

// Constructor
PrimaryGraphicsHelper::PrimaryGraphicsHelper() { }

// Destructor
PrimaryGraphicsHelper::~PrimaryGraphicsHelper() { }

// init() public member function
// Initializes all objects
void PrimaryGraphicsHelper::init() {
  projection = new ProjectionManager();
  scene = new WeatherScene();
}

// display() public member function
// Callback for glutDisplayFunc()
void PrimaryGraphicsHelper::display() {
  // Initialize the scene
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);
  glLoadIdentity();

  // Set view
  if (displayMode == 1) {projection->setOrthogonal();}
  else if (displayMode == 2) {projection->setProjection();}

  // Draw the weather scene
  scene->draw();

  // Flush and swap buffers
  glFlush();
  glutSwapBuffers();
}

// reshape() public member function
// Callback for glutReshapeFunc()
void PrimaryGraphicsHelper::reshape(int w, int h) { }

// special() public member function
// Callback for glutSpecialFunc()
void PrimaryGraphicsHelper::special(int key, int x, int y) {
  // Handle keys
  double th = projection->getTheta();
  double ph = projection->getPhi();
  if (key == GLUT_KEY_RIGHT) {th += 1; projection->setTheta(th); std::cout << "Sucks!" << std::endl;}
  else if (key == GLUT_KEY_LEFT) {th -= 1; projection->setTheta(th);}
  else if (key == GLUT_KEY_UP) {ph += 1; projection->setPhi(ph);}
  else if (key == GLUT_KEY_DOWN) {ph -= 1; projection->setPhi(ph);}

  // Display params (if compiled without GLEW)
  #ifndef USEGLEW
  displayParams();
  #endif

  // Redisplay
  glutPostRedisplay();
}

// key() public member function
// Callback for glutKeyboardFunc()
void PrimaryGraphicsHelper::key(unsigned char ch, int x, int y) {
  // Handle keys
  if (ch == 27) {exit(0);}
  else if (ch == '0') {projection->setTheta(0.0); projection->setPhi(0.0);}
  else if (ch == '1') {
    displayMode += 1;
    if (displayMode > 2) {displayMode = 1;}
  }
  else if (ch == 'x' || ch == 'X') {drawAxes = !drawAxes;}
  else if (ch == '+' && displayMode == 2) {
    double fovy = projection->getFieldOfView() + 2.0;
    projection->setFieldOfView(fovy);
  }
  else if (ch == '-' && displayMode == 2) {
    double fovy = projection->getFieldOfView() - 2.0;
    projection->setFieldOfView(fovy);
  }

  // Display params (if compiled without GLEW)
  #ifndef USEGLEW
  displayParams();
  #endif

  // Redisplay
  glutPostRedisplay();
}

// idle() public member function
// Primary OpenGL idle handler function
// Callback for glutIdleFunc()
void PrimaryGraphicsHelper::idle() { }

// displayParams private member function
// Helper method that displays parameters to the window
void PrimaryGraphicsHelper::displayParams() { }
