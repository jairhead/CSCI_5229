/*
 * File: WeatherData.cpp
 * Author: Jared McKneely
 * Description: Implementation file for the WeatherData class
 */

#include "WeatherData.h"

// Initialize instance to nullptr
WeatherData* WeatherData::instance = nullptr;

// Private constructor
WeatherData::WeatherData() { }

// Private destructor
WeatherData::~WeatherData() { }

// getInstance() member function (public)
// Returns a pointer to the WeatherData instance
WeatherData* WeatherData::getInstance() {
  if (instance == nullptr) {
    std::cout << "WeatherData::getInstance(): no instance yet! Creating one and returning the ptr..." << std::endl;
    WeatherData::instance = new WeatherData();
  }
  std::cout << "WeatherData::getInstance(): returning the ptr!" << std::endl;
  return WeatherData::instance;
}
