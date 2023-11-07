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
  std::cout << "PrimaryGraphicsHelper::init()" << std::endl;
  projection = new ProjectionManager();
  scene = new WeatherScene();
}

// tearDown() public member function
void PrimaryGraphicsHelper::tearDown() {
  std::cout << "PrimaryGraphicsHelper::tearDown()" << std::endl;
  delete projection; projection = nullptr;
  delete scene; scene = nullptr;
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
  else if (displayMode == 3) {projection->setFirstPerson();}

  // Draw the weather scene
  scene->draw();

  // Flush and swap buffers
  glFlush();
  glutSwapBuffers();
}

// reshape() public member function
// Callback for glutReshapeFunc()
void PrimaryGraphicsHelper::reshape(int w, int h) {
  if (h > 0) {projection->setAspectRatio((double)w / h);}
  glViewport(0, 0, w, h);
  projection->setOrthogonal();
}

// special() public member function
// Callback for glutSpecialFunc()
void PrimaryGraphicsHelper::special(int key, int x, int y) {
  // Handle keys
  double th = projection->getTheta();
  double ph = projection->getPhi();
  if (key == GLUT_KEY_RIGHT && displayMode != 3) {th += 1;}
  else if (key == GLUT_KEY_LEFT && displayMode != 3) {th -= 1;}
  else if (key == GLUT_KEY_UP && displayMode != 3) {ph += 1;}
  else if (key == GLUT_KEY_DOWN && displayMode != 3) {ph -= 1;}
  else if (key == GLUT_KEY_RIGHT && displayMode == 3) {projection->turnRight(); std::cout << "Looking right!" << std::endl;}
  else if (key == GLUT_KEY_LEFT && displayMode == 3) {projection->turnLeft(); std::cout << "Looking left!" << std::endl;}
  else if (key == GLUT_KEY_UP && displayMode == 3) {projection->lookUp(); std::cout << "Looking up!" << std::endl;}
  else if (key == GLUT_KEY_DOWN && displayMode == 3) {projection->lookDown(); std::cout << "Looking down!" << std::endl;}

  // Set theta and phi
  projection->setTheta(th);
  projection->setPhi(ph);

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
  if (ch == 27) {tearDown(); exit(0);}
  else if (ch == '0') {projection->setTheta(0.0); projection->setPhi(0.0);}
  else if (ch == '1') {
    displayMode += 1;
    if (displayMode > 3) {displayMode = 1;}
    std::cout << "displayMode: " << displayMode << std::endl;
  }
  else if (ch == 'x' || ch == 'X') {drawAxes = !drawAxes;}
  else if (ch == '+' && displayMode == 2) {
    double fovy = projection->getFieldOfView() + 2.0;
    projection->setFieldOfView(fovy);
    std::cout << "Field of view: " << fovy << std::endl;
  }
  else if (ch == '-' && displayMode == 2) {
    double fovy = projection->getFieldOfView() - 2.0;
    projection->setFieldOfView(fovy);
    std::cout << "Field of view: " << fovy << std::endl;
  }
  else if (ch == 'w' && displayMode == 3) {projection->moveForward();}
  else if (ch == 'a' && displayMode == 3) {projection->moveLeft();}
  else if (ch == 's' && displayMode == 3) {projection->moveBackward();}
  else if (ch == 'd' && displayMode == 3) {projection->moveRight();}
  else if (ch == 'r') {
    #ifndef USEGLEW
    displayParams();
    #endif
  }
  else {return;}


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
