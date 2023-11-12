/*
 * File: WeatherScene.cpp
 * Author: Jared McKneely
 * Description: Implementation file for the Scene class
 */

#include "WeatherScene.h"

// Constructor
WeatherScene::WeatherScene() {
  // Get pointer to data structure
  data = WeatherData::getInstance();

  // Allocate objects
  xyz = new Axes();
  light = new LightManager();
  grass = new RectangularPrism();
  skyLeft = new RectangularPrism();
  skyRight = new RectangularPrism();
  skyBack = new RectangularPrism();
  skyFront = new RectangularPrism();
  skyTop = new RectangularPrism();
  clock = new AnalogClock();
}

// Destructor
WeatherScene::~WeatherScene() {
  delete xyz;
  delete light;
  delete grass;
  delete skyLeft;
  delete skyRight;
  delete skyBack;
  delete skyFront;
  delete skyTop;
  delete clock;
}

// draw() public member function
// Contains logic to draw the entire scene
void WeatherScene::draw() {
  // Draw the sky & landscape
  drawSky();
  drawLandscape();

  // Draw the axes
  if (drawAxes) {
    xyz->draw();
    Utilities::errorCheck("PrimaryGraphicsHelper::display(): axes");
  }

  // Draw the clock
  clock->draw();

  // Draw the sun
  data->setHour(8);
  data->setMinute(20);
  drawLight();
}

// drawSky() private member function
// Draws the sky box and sets its color
void WeatherScene::drawSky() {
  // Position the sun or moon
  drawLight();
  Utilities::errorCheck("WeatherScene::drawSky(): sun / moon");

  // Draw the sky box
  skyLeft->scale(0.01, 2.0, 2.0);
  skyLeft->translate(-2.0, 0.5, 0.0);
  skyLeft->color(0.0,0.24,0.76);
  skyLeft->draw();
  skyRight->scale(0.01, 2.0, 2.0);
  skyRight->translate(2.0, 0.5, 0.0);
  skyRight->color(0.0,0.24,0.76);
  skyRight->draw();
  skyBack->scale(2.0, 2.0, 0.01);
  skyBack->translate(0.0, 0.5, -2.0);
  skyBack->color(0.0,0.24,0.76);
  skyBack->draw();
  /*skyFront->scale(2.0, 2.0, 0.01);
  skyFront->translate(0.0, 0.5, 2.0);
  skyFront->color(0.0,0.24,0.76);
  skyFront->draw();*/
  skyTop->scale(2.0, 0.01, 2.0);
  skyTop->translate(0.0, 2.0, 0.0);
  skyTop->color(0.0,0.24,0.76);
  skyTop->draw();
  Utilities::errorCheck("WeatherScene::drawSky(): sky box");
}

// drawLandscape() private member function
// Draws the entire landscape
void WeatherScene::drawLandscape() {
  grass->scale(2.0, 0.01, 2.0);
  grass->translate(0.0, 0.0, 0.0);
  grass->color(0.14,0.82,0.0);
  grass->draw();

  Utilities::errorCheck("WeatherScene::drawLandscape()");
}

// drawLight() private member function
// Draws the sun / moon in position
void WeatherScene::drawLight() {
  // Get the current hour
  int hour = data->getHour();
  int minute = data->getMinute();
  double th = (minute * 0.25);
  if (hour != 12) {th += (hour * 15.0);}

  // Create the light source
  double xPos = Utilities::cosine(th) * 1.8;
  double yPos = Utilities::sine(th) * 1.8;
  double zPos = -1.5;
  if (th < 180.0) {light->setDrawColor(1.0, 0.97, 0.0);}
  else {light->setDrawColor(0.70, 0.70, 0.70);}
  light->init();
  light->translateLight0(xPos, yPos, zPos);
  light->enableLight0();

  Utilities::errorCheck("WeatherScene::drawLight()");
}
