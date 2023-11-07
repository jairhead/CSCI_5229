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
void WeatherData::setLiveWeather(bool val) {
  std::unique_lock dataLock(dataMutex);
  liveWeather = val;
}

// getLiveWeather() public member function
bool WeatherData::getLiveWeather() {
  std::unique_lock dataLock(dataMutex);
  bool returnVal = liveWeather;
  return returnVal;
}

// setExit() public member function
void WeatherData::setExit(bool val) {
  std::unique_lock dataLock(dataMutex);
  exit = val;
}

// getExit() public member function
bool WeatherData::getExit() {
  std::unique_lock dataLock(dataMutex);
  bool returnVal = exit;
  return returnVal;
}

// setHour() public member function
void WeatherData::setHour(int val) {
  if (val < 1) {val = 1;}
  else if (val > 12) {val = 12;}
  std::unique_lock dataLock(dataMutex);
  hour = val;
}

// getHour() public member function
int WeatherData::getHour() {
  std::unique_lock dataLock(dataMutex);
  int returnVal = hour;
  return returnVal;
}

// setMinute() public member function
void WeatherData::setMinute(int val) {
  if (val < 0) {val = 0;}
  else if (val > 59) {val = 59;}
  std::unique_lock dataLock(dataMutex);
  minute = val;
}

// getMinute() public member function
int WeatherData::getMinute() {
  std::unique_lock dataLock(dataMutex);
  int returnVal = minute;
  return returnVal;
}
