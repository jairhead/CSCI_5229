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

// setExit() public member function
void WeatherData::setExit(bool val) {
  std::unique_lock dataLock(dataMutex);
  end = val;
}

// getExit() public member function
bool WeatherData::getExit() {
  std::unique_lock dataLock(dataMutex);
  return end;
}

// setLiveWeather() public member function
void WeatherData::setLiveWeather(bool val) {
  std::unique_lock dataLock(dataMutex);
  liveWeather = val;
}

// getLiveWeather() public member function
bool WeatherData::getLiveWeather() {
  std::unique_lock dataLock(dataMutex);
  return liveWeather;
}
