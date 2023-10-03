/*
 * File: PrimaryGraphicsHelper.cpp
 * Author: Jared McKneely
 * Description: Implementation file for PrimaryGraphicsHelper, a helper class
 *              used for drawing a complex scene.
 */

#include "PrimaryGraphicsHelper.h"

#include "Cube.h"
#include "Sphere.h"
#include "RectangularPrism.h"
#include "Sun.h"
#include "Moon.h"
#include "Star.h"
#include "Road.h"
#include "House.h"
#include "DryGrass.h"
#include "MountainBackdrop.h"
#include "StreetLamp.h"

// Display Parameter Globals
int th = -10;                     // Azimuth of view angle
int ph = 20;                      // Elevation of view angle
int mode = 1;                     // Mode for modifying display values
double w = 1.0;                   // W variable
const double DIM = 2;             // Dimension of orthogonal box
const int IDLE_TIME = 2500;       // Time to pass between idle transitions
int prevTime = 0;                 // Time of previous transition
bool dayTime = true;              // Is the scene in daytime or nighttime?

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
Star *star1;
Star *star2;
Star *star3;
MountainBackdrop *mountains;
StreetLamp *streetLamp1;
StreetLamp *streetLamp2;

// Color / Position Globals {Current RGB, Day RGB, Night RGB, RGB Step}
double grassC[3][3] = {{0.14,0.82,0.0},{0.14,0.82,0.0},{0,0,0}};
double skyC[3][3] = {{0.0,0.24,0.76},{0.0,0.24,0.76},{0,0,0.11}};
double rHouseC[3][3] = {{0.61,0.15,0.15},{0.61,0.15,0.15},{0.0,0.0,0.0}};
double bHouseC[3][3] = {{0.21,0.42,0.61},{0.21,0.42,0.61},{0.0,0.0,0.0}};
double gHouseC[3][3] = {{0.21,0.61,0.34},{0.21,0.61,0.34},{0.0,0.0,0.0}};
double yHouseC[3][3] = {{0.61,0.59,0.21},{0.61,0.59,0.21},{0.0,0.0,0.0}};
double dryGrsC[3][3] = {{0.26,0.29,0.14},{0.26,0.29,0.14},{0.0,0.0,0.0}};
double spaceC[3][3] = {{0.0,0.24,0.76},{0.0,0.24,0.76},{0.64,0.64,0.64}};
double moonZ = -1.03; double sunZ = -0.97;

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
  star1 = new Star();
  star2 = new Star();
  star3 = new Star();
  mountains = new MountainBackdrop();
  streetLamp1 = new StreetLamp();
  streetLamp2 = new StreetLamp();
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
  grass->color(grassC[0][0], grassC[0][1], grassC[0][2]);
  grass->draw();
  errorCheck("PrimaryGraphicsHelper::display() grass");

  // Draw the road
  road->draw();
  errorCheck("PrimaryGraphicsHelper::display() road");

  // Draw sky
  skyLeft->scale(0.01, 0.5, 1.0);
  skyLeft->translate(-1.0, 0.5, 0.0);
  skyLeft->color(skyC[0][0], skyC[0][1], skyC[0][2]);
  skyRight->scale(0.01, 0.5, 1.0);
  skyRight->translate(1.0, 0.5, 0.0);
  skyRight->color(skyC[0][0], skyC[0][1], skyC[0][2]);
  skyBack->scale(1.0, 0.5, 0.01);
  skyBack->translate(0.0, 0.5, -1.0);
  skyBack->color(skyC[0][0], skyC[0][1], skyC[0][2]);
  skyLeft->draw();
  skyRight->draw();
  skyBack->draw();
  errorCheck("PrimaryGraphicsHelper::display() sky");

  // Draw the red house
  redHouse->color(rHouseC[0][0], rHouseC[0][1], rHouseC[0][2]);
  redHouse->translate(-0.60, 0.0, 0.55);
  redHouse->rotate(90.0);
  redHouse->draw();
  errorCheck("PrimaryGraphicsHelper::display() red house");

  // Draw the blue house
  blueHouse->color(bHouseC[0][0], bHouseC[0][1], bHouseC[0][2]);
  blueHouse->scale(0.15, 0.15, 0.20);
  blueHouse->translate(-0.55, 0.0, 0.10);
  blueHouse->rotate(90.0);
  blueHouse->draw();
  errorCheck("PrimaryGraphicsHelper::display() blue house");

  // Draw the green house
  greenHouse->color(gHouseC[0][0], gHouseC[0][1], gHouseC[0][2]);
  greenHouse->scale(0.15, 0.15, 0.22);
  greenHouse->translate(-0.57, 0.0, -0.35);
  greenHouse->rotate(90.0);
  greenHouse->draw();
  errorCheck("PrimaryGraphicsHelper::display() green house");

  // Draw the yellow house
  yellowHouse->color(yHouseC[0][0], yHouseC[0][1], yHouseC[0][2]);
  yellowHouse->translate(0.60, 0.0, 0.10);
  yellowHouse->rotate(270.0);
  yellowHouse->draw();
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
  sun->translate(0.25, 0.5, sunZ);
  sun->rotate(90.0);
  sun->draw();
  errorCheck("PrimaryGraphicsHelper::display() sun");

  // Draw the moon
  moon->translate(0.12, 0.58, moonZ);
  moon->rotate(90.0);
  moon->draw();
  errorCheck("PrimaryGraphicsHelper::display() moon");

  // Draw stars
  star1->color(spaceC[0][0], spaceC[0][1], spaceC[0][2]);
  star1->translate(-0.7, 0.7, -0.97);
  star1->scale(0.1, 0.1, 0.1);
  star1->draw();
  star2->color(spaceC[0][0], spaceC[0][1], spaceC[0][2]);
  star2->translate(-0.45, 0.45, -0.97);
  star2->scale(0.05, 0.05, 0.05);
  star2->draw();
  star3->color(spaceC[0][0], spaceC[0][1], spaceC[0][2]);
  star3->translate(0.8, 0.8, -0.97);
  star3->scale(0.07, 0.07, 0.07);
  star3->draw();
  errorCheck("PrimaryGraphicsHelper::display() stars");

  // Draw mountains
  mountains->translate(0.0, 0.0, -0.96);
  mountains->draw();
  errorCheck("PrimaryGraphicsHelper::display() mountains");

  // Draw street lamp
  streetLamp1->translate(-0.25, 0.0, -0.4);
  streetLamp1->draw();
  streetLamp2->translate(0.25, 0.0, 0.4);
  streetLamp2->rotate(180);
  streetLamp2->draw();
  errorCheck("PrimaryGraphicsHelper::display() street lamps");

  // Display parameters
  glColor3d(1.0, 1.0, 1.0);
  #ifdef USEGLEW
  glWindowPos2i(5,5);
  #endif
  displayParams();
  errorCheck("PrimaryGraphicsHelper::display() display parameters");

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

// idle() public member function
// Primary OpenGL idle handler function
// Callback for glutIdleFunc()
void PrimaryGraphicsHelper::idle() {
  int currTime = glutGet(GLUT_ELAPSED_TIME);
  if (currTime - prevTime > IDLE_TIME) {
    if (dayTime) { transitionToNight(); dayTime = false; }
    else { transitionToDay(); dayTime = true; }
    prevTime = currTime;
    glutPostRedisplay();
  }
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

// displayParams private member function
// Helper method that displays parameters to the window
void PrimaryGraphicsHelper::displayParams() {
  // Create string
  std::string parameters;
  parameters += "th = "; parameters += std::to_string(th);
  parameters += ", ph = "; parameters += std::to_string(ph);
  parameters += ", time: ";
  if (dayTime) { parameters += "day"; }
  else { parameters += "night"; }

  // Display
  #ifdef USEGLEW
  displayText(parameters);
  #else
  std::cout << parameters << std::endl;
  #endif
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

// transitionToNight() private member function
// Transitions the scene to a nocturnal one
void PrimaryGraphicsHelper::transitionToNight() {
  grassC[0][0] = grassC[2][0]; grassC[0][1] = grassC[2][1]; grassC[0][2] = grassC[2][2];
  skyC[0][0] = skyC[2][0]; skyC[0][1] = skyC[2][1]; skyC[0][2] = skyC[2][2];
  rHouseC[0][0] = rHouseC[2][0]; rHouseC[0][1] = rHouseC[2][1]; rHouseC[0][2] = rHouseC[2][2];
  bHouseC[0][0] = bHouseC[2][0]; bHouseC[0][1] = bHouseC[2][1]; bHouseC[0][2] = bHouseC[2][2];
  gHouseC[0][0] = gHouseC[2][0]; gHouseC[0][1] = gHouseC[2][1]; gHouseC[0][2] = gHouseC[2][2];
  yHouseC[0][0] = yHouseC[2][0]; yHouseC[0][1] = yHouseC[2][1]; yHouseC[0][2] = yHouseC[2][2];
  dryGrsC[0][0] = dryGrsC[2][0]; dryGrsC[0][1] = dryGrsC[2][1]; dryGrsC[0][2] = dryGrsC[2][2];
  spaceC[0][0] = spaceC[2][0]; spaceC[0][1] = spaceC[2][1]; spaceC[0][2] = spaceC[2][2];
  streetLamp1->color(false);
  streetLamp2->color(false);
  road->color(false);
  moonZ = -0.97; sunZ = -1.03;
  glutPostRedisplay();
}

// transitionToDay() private member function
// Transitions the scene to a nocturnal one
void PrimaryGraphicsHelper::transitionToDay() {
  grassC[0][0] = grassC[1][0]; grassC[0][1] = grassC[1][1]; grassC[0][2] = grassC[1][2];
  skyC[0][0] = skyC[1][0]; skyC[0][1] = skyC[1][1]; skyC[0][2] = skyC[1][2];
  rHouseC[0][0] = rHouseC[1][0]; rHouseC[0][1] = rHouseC[1][1]; rHouseC[0][2] = rHouseC[1][2];
  bHouseC[0][0] = bHouseC[1][0]; bHouseC[0][1] = bHouseC[1][1]; bHouseC[0][2] = bHouseC[1][2];
  gHouseC[0][0] = gHouseC[1][0]; gHouseC[0][1] = gHouseC[1][1]; gHouseC[0][2] = gHouseC[1][2];
  yHouseC[0][0] = yHouseC[1][0]; yHouseC[0][1] = yHouseC[1][1]; yHouseC[0][2] = yHouseC[1][2];
  dryGrsC[0][0] = dryGrsC[1][0]; dryGrsC[0][1] = dryGrsC[1][1]; dryGrsC[0][2] = dryGrsC[1][2];
  spaceC[0][0] = spaceC[1][0]; spaceC[0][1] = spaceC[1][1]; spaceC[0][2] = spaceC[1][2];
  streetLamp1->color(true);
  streetLamp2->color(true);
  road->color(false);
  moonZ = -1.03; sunZ = -0.97;
  glutPostRedisplay();
}
