/*
 * File: PrimaryGraphicsHelper.cpp
 * Author: Jared McKneely
 * Description: Implementation file for PrimaryGraphicsHelper, a helper class
 *              used for drawing a complex scene.
 */

#include "PrimaryGraphicsHelper.h"

#include "GenericHomeworkException.h"
#include "ProjectionManager.h"

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
#include "Cloud.h"
#include "Tree.h"

// Display Parameter Globals
int displayMode = 1;        // displayMode for modifying display values
double w = 1.0;             // w value
const int IDLE_TIME = 2500; // Time to pass between idle transitions
int prevTime = 0;           // Time of previous transition
int timeMode = 1;           // Is the scene in auto or manual?
bool dayTime = true;        // Day or night?
bool axesMode = true;       // Draw axes, or no?
ProjectionManager *pm;      // Object that swaps between projection displayModes     

// 3D Object Globals
RectangularPrism *grass;
RectangularPrism *skyLeft;
RectangularPrism *skyRight;
RectangularPrism *skyBack;
RectangularPrism *skyFront;
RectangularPrism *skyTop;
Cloud *cloud1;
Cloud *cloud2;
Road *road;
Sun *sun;
Moon *moon;
House *redHouse;
House *blueHouse;
House *greenHouse;
House *yellowHouse;
Tree *tree1;
Tree *tree2;
Tree *tree3;
Tree *tree4;
Tree *tree5;
Tree *tree6;
DryGrass *dryGrass1;
DryGrass *dryGrass2;
DryGrass *dryGrass3;
DryGrass *dryGrass4;
Star *star1;
Star *star2;
Star *star3;
Star *star4;
Star *star5;
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

// Constructor
PrimaryGraphicsHelper::PrimaryGraphicsHelper() { }

// Destructor
PrimaryGraphicsHelper::~PrimaryGraphicsHelper() { }

// init() public member function
// Initializes all objects for displaying
void PrimaryGraphicsHelper::init() {
  // Initialize projection object
  pm = new ProjectionManager();

  // Initialize 3D objects
  grass = new RectangularPrism();
  skyLeft = new RectangularPrism();
  skyRight = new RectangularPrism();
  skyBack = new RectangularPrism();
  skyFront = new RectangularPrism();
  skyTop = new RectangularPrism();
  cloud1 = new Cloud();
  cloud2 = new Cloud();
  road = new Road();
  sun = new Sun();
  moon = new Moon();
  redHouse = new House();
  blueHouse = new House();
  greenHouse = new House();
  yellowHouse = new House();
  tree1 = new Tree();
  tree2 = new Tree();
  tree3 = new Tree();
  tree4 = new Tree();
  tree5 = new Tree();
  tree6 = new Tree();
  dryGrass1 = new DryGrass();
  dryGrass2 = new DryGrass();
  dryGrass3 = new DryGrass();
  dryGrass4 = new DryGrass();
  star1 = new Star();
  star2 = new Star();
  star3 = new Star();
  star4 = new Star();
  star5 = new Star();
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
  
  // Set view
  if (displayMode == 1) {pm->setOrthogonal();}
  else if (displayMode == 2) {pm->setProjection();}
  else if (displayMode == 3) {pm->setFirstPerson();}

  // Draw axes
  if (axesMode) {createAxes();}

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
  skyFront->scale(1.0, 0.5, 0.01);
  skyFront->translate(0.0, 0.5, 1.0);
  skyFront->color(skyC[0][0], skyC[0][1], skyC[0][2]);
  skyTop->scale(1.0, 0.01, 1.0);
  skyTop->translate(0.0, 1.0, 0.0);
  skyTop->color(skyC[0][0], skyC[0][1], skyC[0][2]);
  skyLeft->draw();
  skyRight->draw();
  skyBack->draw();
  if (displayMode == 3) {
    skyFront->draw();
    skyTop->draw();
  }
  errorCheck("PrimaryGraphicsHelper::display() sky");

  // Draw the clouds
  cloud1->translate(0.45, 0.7, 0.25);
  cloud1->draw();
  cloud2->translate(-0.45, 0.7, -0.25);
  cloud2->rotate(180);
  cloud2->draw();
  errorCheck("PrimaryGraphicsHelper::display() clouds");

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

  // Draw the trees
  tree1->translate(0.28, 0.0, 0.0);
  tree1->draw();
  tree2->translate(-0.28, 0.0, 0.0);
  tree2->draw();
  tree3->translate(0.28, 0.0, -0.65);
  tree3->draw();
  tree4->translate(-0.28, 0.0, -0.65);
  tree4->draw();
  tree5->translate(0.28, 0.0, 0.65);
  tree5->draw();
  tree6->translate(-0.28, 0.0, 0.65);
  tree6->draw();
  errorCheck("PrimaryGraphicsHelper::display() trees");

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

  // Draw the sun or moon and stars
  if (dayTime) {
    sun->translate(0.25, 0.5, -0.97);
    sun->rotate(90.0);
    sun->draw();
    errorCheck("PrimaryGraphicsHelper::display() sun");
  }
  else {
    moon->translate(0.12, 0.58, -0.97);
    moon->rotate(90.0);
    moon->draw();
    star1->color(spaceC[0][0], spaceC[0][1], spaceC[0][2]);
    star1->translate(-0.7, 0.7, -0.97);
    star1->scale(0.1, 0.1, 0.1);
    star2->color(spaceC[0][0], spaceC[0][1], spaceC[0][2]);
    star2->translate(-0.45, 0.45, -0.97);
    star2->scale(0.05, 0.05, 0.05);
    star3->color(spaceC[0][0], spaceC[0][1], spaceC[0][2]);
    star3->translate(0.8, 0.8, -0.97);
    star3->scale(0.07, 0.07, 0.07);
    star3->color(spaceC[0][0], spaceC[0][1], spaceC[0][2]);
    star1->draw();
    star2->draw();
    star3->draw();
    if (displayMode == 3) {
      star4->translate(-0.45, 0.45, 0.97);
      star4->scale(0.07, 0.07, 0.07);
      star4->color(spaceC[0][0], spaceC[0][1], spaceC[0][2]);
      star5->translate(0.5, 0.7, 0.97);
      star5->scale(0.06, 0.06, 0.06);
      star5->color(spaceC[0][0], spaceC[0][1], spaceC[0][2]);
      star4->draw();
      star5->draw();
    }
    errorCheck("PrimaryGraphicsHelper::display() moon and stars");
  }

  // Draw mountains
  mountains->translate(0.0, 0.0, -0.96);
  mountains->draw();
  errorCheck("PrimaryGraphicsHelper::display() mountains");

  // Draw street lamps
  streetLamp1->translate(-0.25, 0.0, -0.4);
  streetLamp1->draw();
  streetLamp2->translate(0.25, 0.0, 0.4);
  streetLamp2->rotate(180);
  streetLamp2->draw();
  errorCheck("PrimaryGraphicsHelper::display() street lamps");

  // Set day or night
  if (dayTime) {transitionToDay();}
  else if (!dayTime) {transitionToNight();}

  // Display parameters
  glColor3d(1.0, 1.0, 1.0);
  #ifdef USEGLEW
  glWindowPos2i(5,5);
  displayParams();
  #endif
  errorCheck("PrimaryGraphicsHelper::display() display parameters");

  // Flush and swap buffers
  glFlush();
  glutSwapBuffers();
}

// reshape() public member function
// Primary OpenGL window resize function
// Callback for glutReshapeFunc()
void PrimaryGraphicsHelper::reshape(int w, int h) {
  if (h > 0) {pm->setAspectRatio((double)w / h);}
  glViewport(0, 0, w, h);
  pm->setOrthogonal();
}

// special() public member function
// Primary OpenGL arrow key handler function
// Callback for glutSpecialFunc()
void PrimaryGraphicsHelper::special(int key, int x, int y) {
  // Handle key display navigation
  double th = pm->getTheta();
  double ph = pm->getPhi();
  if (key == GLUT_KEY_RIGHT && displayMode != 3) {th += 1;}
  else if (key == GLUT_KEY_LEFT && displayMode != 3) {th -= 1;}
  else if (key == GLUT_KEY_UP && displayMode != 3) {ph += 1;}
  else if (key == GLUT_KEY_DOWN && displayMode != 3) {ph -= 1;}
  else if (key == GLUT_KEY_RIGHT && displayMode == 3) {pm->turnRight();}
  else if (key == GLUT_KEY_LEFT && displayMode == 3) {pm->turnLeft();}
  else if (key == GLUT_KEY_UP && displayMode == 3) {pm->lookUp();}
  else if (key == GLUT_KEY_DOWN && displayMode == 3) {pm->lookDown();}

  // Set theta and phi
  pm->setTheta(th);
  pm->setPhi(ph);

  // Redisplay
  glutPostRedisplay();
}

// key() public member function
// Primary OpenGL keyboard handler function
// Callback for glutKeyboardFunc()
void PrimaryGraphicsHelper::key(unsigned char ch, int x, int y) {
  // Handle alphanumeric keys
  if (ch == 27) {exit(0);}
  else if (ch == '0') {pm->setTheta(0.0); pm->setPhi(0.0);}
  else if (ch == 'c') {axesMode = !axesMode;}
  else if (ch == 'm') {
    displayMode += 1;
    if (displayMode > 3) {displayMode = 1;}
    #ifndef USEGLEW
    displayParams();
    #endif
  }
  else if (ch == 't') {
    timeMode += 1;
    if (timeMode > 2) {timeMode = 1;}
  }
  else if (ch == 'T') {
    dayTime = !dayTime;
    #ifndef USEGLEW
    displayParams();
    #endif
  }
  else if (ch == '+' && displayMode == 2) {
    double fovy = pm->getFieldOfView() + 2.0;
    pm->setFieldOfView(fovy);
    #ifndef USEGLEW
    displayParams();
    #endif
  }
  else if (ch == '-' && displayMode == 2) {
    double fovy = pm->getFieldOfView() - 2.0;
    pm->setFieldOfView(fovy);
    #ifndef USEGLEW
    displayParams();
    #endif
  }
  else if (ch == 'w' && displayMode == 3) {pm->moveForward();}
  else if (ch == 'a' && displayMode == 3) {pm->moveLeft();}
  else if (ch == 's' && displayMode == 3) {pm->moveBackward();}
  else if (ch == 'd' && displayMode == 3) {pm->moveRight();}
  else if (ch == 'r') {
    #ifndef USEGLEW
    displayParams();
    #endif
  }
  else {return;}

  // Redisplay
  glutPostRedisplay();
}

// idle() public member function
// Primary OpenGL idle handler function
// Callback for glutIdleFunc()
void PrimaryGraphicsHelper::idle() {
  int currTime = glutGet(GLUT_ELAPSED_TIME);
  if (currTime - prevTime > IDLE_TIME && timeMode == 1) {
    if (dayTime) { transitionToNight(); }
    else { transitionToDay(); }
    prevTime = currTime;
    glutPostRedisplay();
  }
}

// initializeGlew() public member function
// Tries to initialize GLEW (throws a GlewException if it fails)
void PrimaryGraphicsHelper::initializeGlew() {
  #ifdef USEGLEW
  if (glewInit() != GLEW_OK) {throw GenericHomeworkException();}
  std::cout << "PrimaryGraphicsHelper::initializeGlew(): GLEW initialization successful!"
            << std::endl;
  #else
  std::cout << "PrimaryGraphicsHelper::initializeGlew(): Skipped GLEW initialization"
            << std::endl;
  #endif
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
  if (displayMode == 3) {
    parameters += "th = "; parameters += std::to_string((int)pm->getFirstPersonTheta()); parameters += ", ";
    parameters += "view: first person, ";
    parameters += "xPos = "; parameters += std::to_string(pm->getFirstPersonX()); parameters += ", ";
    parameters += "yPos = "; parameters += std::to_string(pm->getFirstPersonY()); parameters += ", ";
    parameters += "zPos = "; parameters += std::to_string(pm->getFirstPersonZ()); parameters += ", ";
  }
  else {
    parameters += "th = "; parameters += std::to_string((int)pm->getTheta()); parameters += ", ";
    parameters += "ph = "; parameters += std::to_string((int)pm->getPhi()); parameters += ", ";
    if (displayMode == 1) {parameters += "view: ortho, ";}
    else if (displayMode == 2) {parameters += "view: projection, fovy = "; parameters += std::to_string(pm->getFieldOfView()); parameters += ", ";}
  }
  parameters += "day / night cycle: ";
  if (timeMode == 1) { parameters += "auto, "; }
  else { parameters += "manual, "; }
  parameters += "time: ";
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
  tree1->color(false);
  tree2->color(false);
  tree3->color(false);
  tree4->color(false);
  tree5->color(false);
  tree6->color(false);
  cloud1->color(false);
  cloud2->color(false);
  road->color(false);
  dayTime = false;
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
  tree1->color(true);
  tree2->color(true);
  tree3->color(true);
  tree4->color(true);
  tree5->color(true);
  tree6->color(true);
  cloud1->color(true);
  cloud2->color(true);
  road->color(true);
  dayTime = true;
  glutPostRedisplay();
}
