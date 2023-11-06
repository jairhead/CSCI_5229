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
  skyLeft = new RectangularPrism();
  skyRight = new RectangularPrism();
  skyBack = new RectangularPrism();
  skyFront = new RectangularPrism();
  skyTop = new RectangularPrism();
}

// Destructor
WeatherScene::~WeatherScene() { }

// draw() public member function
// Contains logic to draw the entire scene
void WeatherScene::draw() {
  // Draw the sky
  drawSky();

  // Draw the clock
}

// drawSky() private member function
// Draws the sky box and sets its color
void WeatherScene::drawSky() {
  skyLeft->scale(0.01, 0.5, 1.0);
  skyLeft->translate(-1.0, 0.5, 0.0);
  skyLeft->color(0.0,0.24,0.76);
  skyRight->scale(0.01, 0.5, 1.0);
  skyRight->translate(1.0, 0.5, 0.0);
  skyRight->color(0.0,0.24,0.76);
  skyBack->scale(1.0, 0.5, 0.01);
  skyBack->translate(0.0, 0.5, -1.0);
  skyBack->color(0.0,0.24,0.76);
  skyFront->scale(1.0, 0.5, 0.01);
  skyFront->translate(0.0, 0.5, 1.0);
  skyFront->color(0.0,0.24,0.76);
  skyTop->scale(1.0, 0.01, 1.0);
  skyTop->translate(0.0, 1.0, 0.0);
  skyTop->color(0.0,0.24,0.76);
  skyLeft->draw();
  skyRight->draw();
  skyFront->draw();
  skyBack->draw();
  skyTop->draw();
  Utilities::errorCheck("WeatherScene::drawSky()");
}

// setSunPosition() private member function
// Sets the sun's position based on the time of day
void WeatherScene::setSunPosition() { }

// setMoonPosition() private member funcion
// Sets the moon's position based on the time of day
void WeatherScene::setMoonPosition() { }
