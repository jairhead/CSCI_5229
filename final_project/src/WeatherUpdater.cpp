/*
 * File: WeatherUpdater.cpp
 * Author: Jared McKneely
 * Description: Implementation file for the WeatherUpdater class
 */

#include "WeatherUpdater.h"

// Constructor
WeatherUpdater::WeatherUpdater() {
  data = WeatherData::getInstance();
}

// Destructor
WeatherUpdater::~WeatherUpdater() { }

// thread() public member function
// Used as a looping thread for weather updates
void WeatherUpdater::thread(int loopTime) {
  std::cout << "WeatherUpdater::thread(): beginning loop" << std::endl;
  while(!data->getExit()) {
    // TODO: implement
    std::cout << "WeatherUpdater::thread(): loop iteration" << std::endl;

    // Sleep
    sleep(loopTime);
  }
}
