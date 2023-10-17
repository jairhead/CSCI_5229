/*
 * File: PrimaryGraphicsHelper.cpp
 * Author: Jared McKneely
 * Description: Implementation file for PrimaryGraphicsHelper, a helper class
 *              used for drawing a complex scene.
 */

#include "PrimaryGraphicsHelper.h"

// 3D Object & View Globals
ProjectionManager *pm;
LightManager *lm;
Axes *axes;
ChessBoard *chessBoard;
Pawn *whitePawn;
Pawn *blackPawn;
Rook *whiteRook;

// Control Globals
float lightAngle = 0.0;          // Current angle at which the light is located (degrees)
float lightOrbitRadius = 1.5;    // Radius with which the light will orbit
float lightHeight = 0.8;         // Y component of light position
float lightOrbitInc = 2.0;       // Orbit increment
const int LIGHT_IDLE_TIME = 50;  // Time to pass between idle transitions (ms)
const int TEXT_IDLE_TIME = 2000; // Texture mode idle time
int prevTimeLight = 0;           // Time of previous transition (light)
int prevTimeText = 0;            // Time of previous transition (texture)
bool lightingEnabled = true;     // Lighting is enabled or no?
int textureMode = 0;             // Textures are enabled or no?
bool drawAxes = true;            // Draw the xyz axes or no?
bool animate = true;             // Execute light orbit animation or no?
int displayMode = 1;             // 1 = ortho; 2 = projection
unsigned int boardTextures[2];   // Array containing texture references
unsigned int chessTexturesW[6];  // Array containing textures for white chess pieces
unsigned int chessTexturesB[6];  // Array containing textures for black chess pieces
int textureIndex = 0;            // Texture index for chess pieces

// Constructor
PrimaryGraphicsHelper::PrimaryGraphicsHelper() { }

// Destructor
PrimaryGraphicsHelper::~PrimaryGraphicsHelper() { }

// init() public member function
// Initializes all objects
void PrimaryGraphicsHelper::init() {
  // Initialize managers and axes
  pm = new ProjectionManager();
  lm = new LightManager();
  axes = new Axes();

  // Initialize 3D objects
  chessBoard = new ChessBoard();
  whitePawn = new Pawn();
  blackPawn = new Pawn();
  whiteRook = new Rook();

  // Load textures
  boardTextures[0] = Utilities::loadBmp("images/granite-512x512.bmp");

  chessTexturesW[0] = Utilities::loadBmp("images/white-marble-32x32.bmp");
  chessTexturesW[1] = Utilities::loadBmp("images/light-wood-grain-32x32.bmp");
  chessTexturesW[2] = Utilities::loadBmp("images/watermelon-32x32.bmp");
  chessTexturesW[3] = Utilities::loadBmp("images/tv-snow-1-32x32.bmp");
  chessTexturesW[4] = Utilities::loadBmp("images/tv-snow-2-32x32.bmp");
  chessTexturesW[5] = Utilities::loadBmp("images/tv-snow-3-32x32.bmp");

  chessTexturesB[0] = Utilities::loadBmp("images/black-marble-32x32.bmp");
  chessTexturesB[1] = Utilities::loadBmp("images/dark-wood-grain-32x32.bmp");
  chessTexturesB[2] = Utilities::loadBmp("images/pumpkin-32x32.bmp");
  chessTexturesB[3] = Utilities::loadBmp("images/tv-snow-1-32x32.bmp");
  chessTexturesB[4] = Utilities::loadBmp("images/tv-snow-2-32x32.bmp");
  chessTexturesB[5] = Utilities::loadBmp("images/tv-snow-3-32x32.bmp");
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

  // Handle lighting
  if (lightingEnabled) {
    lm->init();
    lm->translateLight0(lightOrbitRadius * Utilities::cosine(lightAngle),
                        lightHeight,
                        lightOrbitRadius * Utilities::sine(lightAngle));
    lm->enableLight0();
    Utilities::errorCheck("PrimaryGraphicsHelper::display(): light 0");
    chessBoard->enableLighting();
    whitePawn->enableLighting();
    whiteRook->enableLighting();
  }
  else {
    chessBoard->disableLighting();
    whitePawn->disableLighting();
    whiteRook->disableLighting();
  }

  // Handle textures
  chessBoard->enableTexture();
  whitePawn->enableTexture();
  blackPawn->enableTexture();
  whiteRook->enableTexture();

  // Draw the chess board
  chessBoard->setTextureFactor(2.0);
  chessBoard->setTexture(&boardTextures[0]);
  chessBoard->draw();
  Utilities::errorCheck("PrimaryGraphicsHelper::display(): chess board");

  // Draw the white pawn
  whitePawn->translate(-0.5, 0.0, -0.5);
  whitePawn->setTextureFactor(1.0);
  whitePawn->setTexture(&chessTexturesW[textureIndex]);
  whitePawn->draw();
  Utilities::errorCheck("PrimaryGraphicsHelper::display(): white pawn");

  // Draw the black pawn
  blackPawn->translate(+0.5, 0.0, -0.5);
  blackPawn->setTextureFactor(1.0);
  blackPawn->setTexture(&chessTexturesB[textureIndex]);
  blackPawn->draw();
  Utilities::errorCheck("PrimaryGraphicsHelper::display(): black pawn");

  // Draw the white rook
  whiteRook->translate(+0.5, 0.0, +0.5);
  whiteRook->setTextureFactor(1.0);
  whiteRook->setTexture(&chessTexturesW[textureIndex]);
  whiteRook->draw();
  Utilities::errorCheck("PrimaryGraphicsHelper::display(): white rook");

  // Draw the axes
  if (drawAxes) {
    axes->draw();
    Utilities::errorCheck("PrimaryGraphicsHelper::display(): axes");
  }

  // Display parameters
  #ifdef USEGLEW
  glColor3d(1.0, 1.0, 1.0);
  glWindowPos2i(5,5);
  displayParams();
  Utilities::errorCheck("PrimaryGraphicsHelper::display() display parameters");
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
  // Handle keys
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
  else if (ch == '0') {pm->setTheta(0.0); pm->setPhi(0.0);}
  else if (ch == '1') {
    displayMode += 1;
    if (displayMode > 2) {displayMode = 1;}
  }
  else if (ch == 'x' || ch == 'X') {drawAxes = !drawAxes;}
  else if (ch == 'l' || ch == 'L') {lightingEnabled = !lightingEnabled;}
  else if (ch == 'm' || ch == 'M') {animate = !animate;}
  else if (ch == '<') {lightAngle += 1;}
  else if (ch == '>') {lightAngle -= 1;}
  else if (ch == '+' && displayMode == 2) {
    double fovy = pm->getFieldOfView() + 2.0;
    pm->setFieldOfView(fovy);
  }
  else if (ch == '-' && displayMode == 2) {
    double fovy = pm->getFieldOfView() - 2.0;
    pm->setFieldOfView(fovy);
  }
  else if (ch == '[') {
    lightHeight += 0.1;
    if (lightHeight > 1.5) {lightHeight = 1.5;}
  }
  else if (ch == ']') {
    lightHeight -= 0.1;
    if (lightHeight < 0.0) {lightHeight = 0.0;}
  }
  else if (ch == 'a') {
    int amb = lm->getAmbient() - 5;
    lm->setAmbient(amb);
  }
  else if (ch == 'A') {
    int amb = lm->getAmbient() + 5;
    lm->setAmbient(amb);
  }
  else if (ch == 'd') {
    int diff = lm->getDiffuse() - 5;
    lm->setDiffuse(diff);
  }
  else if (ch == 'D') {
    int diff = lm->getDiffuse() + 5;
    lm->setDiffuse(diff);
  }
  else if (ch == 's') {
    int spec = lm->getSpecular() - 5;
    lm->setSpecular(spec);
  }
  else if (ch == 'S') {
    int spec = lm->getSpecular() + 5;
    lm->setSpecular(spec);
  }
  else if (ch == 't' || ch == 'T') {
    textureMode += 1;
    if (textureMode > 3) {textureMode = 0;}
    textureIndex = textureMode;
    std::cout << "Texture mode is " << textureMode << std::endl;
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
void PrimaryGraphicsHelper::idle() {
  int currTime = glutGet(GLUT_ELAPSED_TIME);
  if (currTime - prevTimeLight > LIGHT_IDLE_TIME && animate) {
    // Adjust lightAngle
    lightAngle += lightOrbitInc;
    if (lightAngle > 360) {lightAngle = 0.0;}

    // TV snow
    if (textureMode == 3) {
      textureIndex += 1;
      if (textureIndex > 5) {textureIndex = 3;}
    }
    
    // Redisplay
    prevTimeLight = currTime;
    glutPostRedisplay();
  }

  // Cycle texture mode
  if (currTime - prevTimeText > TEXT_IDLE_TIME && animate) {
    textureMode += 1;
    if (textureMode > 3) {textureMode = 0;}
    textureIndex = textureMode;
    prevTimeText = currTime;
    glutPostRedisplay();
  }
}

// displayParams private member function
// Helper method that displays parameters to the window
void PrimaryGraphicsHelper::displayParams() {
  // Create string
  std::string parameters;
  parameters += "Angle: "; parameters += std::to_string((int)pm->getTheta()); parameters += ",";
  parameters += std::to_string((int)pm->getPhi()); parameters += "; ";
  parameters += "View: ";
  if (displayMode == 1) {parameters += "Ortho; ";}
  else {parameters += "Persp, Fovy = "; parameters += std::to_string(pm->getFieldOfView()); parameters += "; ";}
  parameters += "Lite: ";
  if (lightingEnabled) {parameters += "ON; ";}
  else {parameters += "OFF; ";}
  parameters += "Ambient: "; parameters += std::to_string(lm->getAmbient()); parameters += ", ";
  parameters += "Diffuse: "; parameters += std::to_string(lm->getDiffuse()); parameters += ", ";
  parameters += "Specular: "; parameters += std::to_string(lm->getSpecular()); parameters += ", ";
  parameters += "Texture: ";
  if (textureMode == 0) {parameters += "Marble";}
  else if (textureMode == 1) {parameters += "Wood";}
  else if (textureMode == 2) {parameters += "Watermelon / Pumpkin";}
  else if (textureMode == 3) {parameters += "TV Snow";}

  // Display
  Utilities::displayText(parameters);
}
