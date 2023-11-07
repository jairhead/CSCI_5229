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
WeatherScene::~WeatherScene() { }

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
}

// drawSky() private member function
// Draws the sky box and sets its color
void WeatherScene::drawSky() {
  // Position the sun or moon
  light->init();
  light->translateLight0(0.0, 0.2, -0.6);
  light->enableLight0();
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
  grass->translate(0.0, -1.0, 0.0);
  grass->color(0.14,0.82,0.0);
  grass->draw();

  Utilities::errorCheck("WeatherScene::drawLandscape()");
}
