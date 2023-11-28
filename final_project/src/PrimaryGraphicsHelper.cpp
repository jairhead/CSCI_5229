/*
 * File: PrimaryGraphicsHelper.cpp
 * Author: Jared McKneely
 * Description: Implementation file for PrimaryGraphicsHelper, a helper class
 *              used for drawing a complex scene.
 */

#include "PrimaryGraphicsHelper.h"

// Member Objects
ProjectionManager *projection = nullptr;
Scene* scene = nullptr;
WeatherData* dataPtr = nullptr;

// Control Globals
int displayMode = 1;
bool drawAxes = true;
const int LIGHT_IDLE_TIME = 50;  // Time to pass between idle transitions (ms)
const int TEXT_IDLE_TIME = 1000; // Texture mode idle time
int prevTime = 0;                // Time of previous transition (light)

// Constructor
PrimaryGraphicsHelper::PrimaryGraphicsHelper() { }

// Destructor
PrimaryGraphicsHelper::~PrimaryGraphicsHelper() { }

// init() public member function
// Initializes all objects
void PrimaryGraphicsHelper::init() {
  // Get pointer to data structure
  dataPtr = WeatherData::getInstance();

  // Initialize projection manager and scene
  std::cout << "PrimaryGraphicsHelper::init()" << std::endl;
  projection = new ProjectionManager();
  scene = new Scene();

  // Initialize first person position
  projection->setFirstPersonX(0.0);
  projection->setFirstPersonY(0.3);
  projection->setFirstPersonZ(1.55);
  projection->setFirstPersonTheta(270.0);
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
  if (displayMode == 1) {projection->setFirstPerson();}
  else if (displayMode == 2) {projection->setProjection();}

  // Draw the weather scene
  scene->draw();

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
  if (key == GLUT_KEY_RIGHT && displayMode != 1) {th += 1;}
  else if (key == GLUT_KEY_LEFT && displayMode != 1) {th -= 1;}
  else if (key == GLUT_KEY_UP && displayMode != 1) {ph += 1;}
  else if (key == GLUT_KEY_DOWN && displayMode != 1) {ph -= 1;}
  else if (key == GLUT_KEY_RIGHT && displayMode == 1) {projection->turnRight(); std::cout << "Looking right!" << std::endl;}
  else if (key == GLUT_KEY_LEFT && displayMode == 1) {projection->turnLeft(); std::cout << "Looking left!" << std::endl;}
  else if (key == GLUT_KEY_UP && displayMode == 1) {projection->lookUp(); std::cout << "Looking up!" << std::endl;}
  else if (key == GLUT_KEY_DOWN && displayMode == 1) {projection->lookDown(); std::cout << "Looking down!" << std::endl;}

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
    if (displayMode > 2) {displayMode = 1;}
    std::cout << "displayMode: " << displayMode << std::endl;
  }
  else if (ch == 'm' || ch == 'M') {
    char wc = dataPtr->getCurrentWeatherCondition();
    if (wc == 'n') {
      dataPtr->setCurrentWeatherCondition('r');
      int density = rand() % 1000;
      dataPtr->setPrecipDensity(density);
      dataPtr->setFahrenheit(68);
    }
    else if (wc == 'r') {
      dataPtr->setCurrentWeatherCondition('t');
      dataPtr->setPrecipDensity(1000);
      dataPtr->setFahrenheit(65);
    }
    else if (wc == 't') {
      dataPtr->setCurrentWeatherCondition('m');
      int density = rand() % 1000;
      dataPtr->setPrecipDensity(density);
      dataPtr->setFahrenheit(31);
    }
    else if (wc == 'm') {
      dataPtr->setCurrentWeatherCondition('s');
      dataPtr->setPrecipDensity(1000);
      dataPtr->setFahrenheit(23);
    }
    else if (wc == 's') {
      dataPtr->setCurrentWeatherCondition('n');
      dataPtr->setFahrenheit(78);
    }
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
void PrimaryGraphicsHelper::idle() {
  int currTime = glutGet(GLUT_ELAPSED_TIME);
  if (currTime - prevTime > LIGHT_IDLE_TIME) {
    // Redisplay
    prevTime = currTime;
    glutPostRedisplay();
  }
}

// displayParams private member function
// Helper method that displays parameters to the window
void PrimaryGraphicsHelper::displayParams() {
  // Create string
  char wc = dataPtr->getCurrentWeatherCondition();
  std::string parameters;
  parameters += "Time:";
  parameters += std::to_string(dataPtr->getHour());
  parameters += ":";
  parameters += std::to_string(dataPtr->getMinute());
  parameters += ", ";
  parameters += "Location: DEMO, ";
  parameters += "Temperature: ";
  parameters += std::to_string(dataPtr->getFahrenheit());
  parameters += "°F, ";
  parameters += "Current Weather: ";
  if (wc == 'n') {parameters += "Clear";}
  else if (wc == 'r') {parameters += "Rain";}
  else if (wc == 't') {parameters += "T-Storm";}
  else if (wc == 'm') {parameters += "Mixed Precip";}
  else if (wc == 's') {parameters += "Snow";}

  // Display
  Utilities::displayText(parameters);
}
