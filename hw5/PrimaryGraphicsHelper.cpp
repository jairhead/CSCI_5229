/*
 * File: PrimaryGraphicsHelper.cpp
 * Author: Jared McKneely
 * Description: Implementation file for PrimaryGraphicsHelper, a helper class
 *              used for drawing a complex scene.
 */

#include "PrimaryGraphicsHelper.h"

// 3D Object Globals
ProjectionManager *pm;
LightManager *lm;
Axes *axes;
ChessBoard *chessBoard;
Pawn *whitePawn;
Pawn *blackPawn;

// Control Globals
float lightAngle = 0.0;       // Current angle at which the light is located (degrees)
float lightOrbitRadius = 1.5; // Radius with which the light will orbit
float lightHeight = 0.3;      // Y component of light position
float lightOrbitInc = 2.0;    // Orbit increment
const int IDLE_TIME = 50;     // Time to pass between idle transitions (ms)
int prevTime = 0;             // Time of previous transition
bool lightingEnabled = true;  // Lighting is enabled or no?
bool drawAxes = true;         // Draw the xyz axes or no?
bool moveLight = true;        // Execute light orbit animation or no?
int displayMode = 1;          // 1 = ortho; 2 = projection

// Constructor
PrimaryGraphicsHelper::PrimaryGraphicsHelper() { }

// Destructor
PrimaryGraphicsHelper::~PrimaryGraphicsHelper() { }

// init() public member function
// Initializes all objects
void PrimaryGraphicsHelper::init() {
  pm = new ProjectionManager();
  lm = new LightManager();
  axes = new Axes();
  chessBoard = new ChessBoard();
  whitePawn = new Pawn();
  blackPawn = new Pawn();
}

// display() public member function
// Callback for glutDisplayFunc()
void PrimaryGraphicsHelper::display() {
  // Initialize the scene
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);
  glLoadIdentity();

  // Set view
  if (displayMode == 1) {pm->setOrthogonal();}
  else if (displayMode == 2) {pm->setProjection();}

  // Enable or disable lighting
  if (lightingEnabled) {
    lm->init();
    lm->translateLight0(lightOrbitRadius * cosine(lightAngle),
                        lightHeight,
                        lightOrbitRadius * sine(lightAngle));
    lm->enableLight0();
    errorCheck("PrimaryGraphicsHelper::display(): light 0");
    chessBoard->enableLighting();
    whitePawn->enableLighting();
    blackPawn->enableLighting();
  }
  else {
    chessBoard->disableLighting();
    whitePawn->disableLighting();
    blackPawn->disableLighting();
  }

  // Draw rectangular prism
  chessBoard->draw();
  errorCheck("PrimaryGraphicsHelper::display(): chess board");

  // Draw the white pawn
  whitePawn->translate(-0.5, 0.0, -0.5);
  whitePawn->draw();
  errorCheck("PrimaryGraphicsHelper::display(): white pawn");

  // Draw the black pawn
  blackPawn->translate(+0.5, 0.0, -0.5);
  blackPawn->color(0.13, 0.13, 0.13);
  blackPawn->draw();
  errorCheck("PrimaryGraphicsHelper::display(): black pawn");
  
  // Draw the white rook
  errorCheck("PrimaryGraphicsHelper::display(): white rook");
  

  // Draw the axes
  if (drawAxes) {
    axes->draw();
    errorCheck("PrimaryGraphicsHelper::display(): axes");
  }

  // Display parameters
  #ifdef USEGLEW
  glColor3d(1.0, 1.0, 1.0);
  glWindowPos2i(5,5);
  displayParams();
  errorCheck("PrimaryGraphicsHelper::display() display parameters");
  #endif

  // Flush and swap buffers
  glFlush();
  glutSwapBuffers();
}

// reshape() public member function
// Callback for glutReshapeFunc()
void PrimaryGraphicsHelper::reshape(int w, int h) {
  if (h > 0) {pm->setAspectRatio((double)w / h);}
  glViewport(0, 0, w, h);
  pm->setOrthogonal();
}

// special() public member function
// Callback for glutSpecialFunc()
void PrimaryGraphicsHelper::special(int key, int x, int y) {
  // Handle key display navigation
  double th = pm->getTheta();
  double ph = pm->getPhi();
  if (key == GLUT_KEY_RIGHT) {th += 1; pm->setTheta(th);}
  else if (key == GLUT_KEY_LEFT) {th -= 1; pm->setTheta(th);}
  else if (key == GLUT_KEY_UP) {ph += 1; pm->setPhi(ph);}
  else if (key == GLUT_KEY_DOWN) {ph -= 1; pm->setPhi(ph);}
  else if (key == GLUT_KEY_F3) {
    lightOrbitRadius -= 0.05;
    if (lightOrbitRadius < 0.1) {lightOrbitRadius = 0.1;}
  }
  else if (key == GLUT_KEY_F4) {
    lightOrbitRadius += 0.05;
    if (lightOrbitRadius > 1.5) {lightOrbitRadius = 1.5;}
  }
  else if (key == GLUT_KEY_F8) {
    lightOrbitInc += 0.5;
    if (lightOrbitInc > 10.0) {lightOrbitInc = 10.0;}
  }
  else if (key == GLUT_KEY_F9) {
    lightOrbitInc -= 0.5;
    if (lightOrbitInc < 0.0) {lightOrbitInc = 0.0;}
  }

  // Redisplay
  glutPostRedisplay();
}

// key() public member function
// Callback for glutKeyboardFunc()
void PrimaryGraphicsHelper::key(unsigned char ch, int x, int y) {
  if (ch == 27) {exit(0);}
  else if (ch == '0') {pm->setTheta(0.0); pm->setPhi(0.0);}
  else if (ch == '1') {
    displayMode += 1;
    if (displayMode > 2) {displayMode = 1;}
  }
  else if (ch == 'x' || ch == 'X') {drawAxes = !drawAxes;}
  else if (ch == 'l' || ch == 'L') {lightingEnabled = !lightingEnabled;}
  else if (ch == 'm' || ch == 'M') {moveLight = !moveLight;}
  else if (ch == '<') {lightAngle += 1;}
  else if (ch == '>') {lightAngle -= 1;}
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
  else if (ch == '[') {
    lightHeight += 0.1;
    if (lightHeight > 1.5) {lightHeight = 1.5;}
  }
  else if (ch == ']') {
    lightHeight -= 0.1;
    if (lightHeight < 0.0) {lightHeight = 0.0;}
  }

  // Redisplay
  glutPostRedisplay();
}

// idle() public member function
// Primary OpenGL idle handler function
// Callback for glutIdleFunc()
void PrimaryGraphicsHelper::idle() {
  int currTime = glutGet(GLUT_ELAPSED_TIME);
  if (currTime - prevTime > IDLE_TIME && moveLight) {
    lightAngle += lightOrbitInc;
    if (lightAngle > 360) {lightAngle = 0.0;}
    prevTime = currTime;
    glutPostRedisplay();
  }
}

// initializeGlew() public member function
// Tries to initialize GLEW (throws a GenericHomeworkException if it fails)
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
  std::string parameters = "[NULL]";

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

// sine() private member function
// Returns the sine of the provided angle in degrees
double PrimaryGraphicsHelper::sine(double angle) {return sin(angle * (3.14159265 / 180));}

// cosine() private member function
// Returns the cosine of the provided angle in degrees
double PrimaryGraphicsHelper::cosine(double angle) {return cos(angle * (3.14159265 / 180));}
