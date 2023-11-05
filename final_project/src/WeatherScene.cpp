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

  // Instantiate objects

}

// Destructor
WeatherScene::~WeatherScene() { }

// draw() public member function
// Contains logic to draw the entire scene
void WeatherScene::draw() {
  // Draw the skybox and ground
  std::cout << "WeatherScene::draw()" << std::endl;

  // Draw the sun and moon
  setSunPosition();
  setMoonPosition();

  // Draw scene details
}

// setSunPosition() private member function
// Sets the sun's position based on the time of day
void WeatherScene::setSunPosition() { }

// setMoonPosition() private member funcion
// Sets the moon's position based on the time of day
void WeatherScene::setMoonPosition() { }
