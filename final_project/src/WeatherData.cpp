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

// getInstance() public member function
// Returns a pointer to the WeatherData instance
WeatherData* WeatherData::getInstance() {
  if (instance == nullptr) {WeatherData::instance = new WeatherData();}
  return WeatherData::instance;
}

// setLiveWeather() public member function
// Sets the liveWeather boolean (thread safe)
void WeatherData::setLiveWeather(bool val) {
  std::unique_lock dataLock(dataMutex);
  liveWeather = val;
}
