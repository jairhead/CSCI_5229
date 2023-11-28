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

// updateThread() public member function
// Used as a looping thread for weather updates
void WeatherUpdater::updateThread(int loopTime) {
  std::cout << "WeatherUpdater::updateThread(): beginning loop" << std::endl;
  while(!data->getExit()) {
    // TODO: implement
    std::cout << "WeatherUpdater::updateThread(): loop iteration" << std::endl;

    // Sleep
    sleep(loopTime);
  }
}

// demoThread() public member function
// Used to demo all the weather conditions
void WeatherUpdater::demoThread() {
  std::cout << "WeatherUpdater::thread(): beginning loop" << std::endl;
  while(!data->getExit()) {
    // Get the current conditions
    int hour = data->getHour();
    int minute = data->getMinute();
    char weatherCondition = data->getCurrentWeatherCondition();

    // Update time and weather condition
    minute += 10;
    if (minute >= 60) {
      // Reset the minute
      minute = minute % 60;
      data->setMinute(minute);

      // Handle the hour
      hour += 1;
      if (hour > 23) {
        data->setHour(0);
        demoIncrementWeatherCondition(weatherCondition);
        std::cout << "Current hour is " << data->getHour() << std::endl;
      }
      else {
        data->setHour(hour);
      }
    }
    else {
      data->setHour(hour);
      data->setMinute(minute);
    }

    // Sleep
    usleep(100000);
  }
}

// demoIncrementWeatherCondition() public member function
// Used to iterate through weather conditions in a demo scenario
void WeatherUpdater::demoIncrementWeatherCondition(char &wc) {
  if (wc == 'n') {
    data->setCurrentWeatherCondition('r');
    int density = rand() % 1000;
    data->setPrecipDensity(density);
  }
  else if (wc == 'r') {
    data->setCurrentWeatherCondition('s');
    int density = rand() % 1000;
    data->setPrecipDensity(density);
  }
  else if (wc == 's') {
    data->setCurrentWeatherCondition('n');
    data->setFog(0);
  }
  std::cout << "WeatherUpdater::demoIncrementWeatherCondition(): weather is " << data->getCurrentWeatherCondition() << std::endl;
}
