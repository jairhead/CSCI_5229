/*
 * File: final_project.cpp
 * Author: Jared McKneely
 * Description: Main runtime for final project (CSCI 5229)
 */

#include <iostream>
#include <thread>
#include "WeatherUpdater.h"
#include "PrimaryGraphicsHelper.h"

// Main
int main(int argc, char* argv[]) {
  // Enter program
  std::cout << "final_project::main(): starting program" << std::endl;

  // Init GLUT w/ user args, z-buffer, double buffer
  glutInit(&argc, argv);
  glutInitWindowSize(600, 600);
  glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
  glutCreateWindow("Jared McKneely - CSCI 5229, Final Project (Real-Time Weather Clock)");

  // Init GLEW
  try {Utilities::initializeGlew();}
  catch (GenericHomeworkException& e) {std::cout << e.what() << ": GLEW initialization failed!" << std::endl; exit(1);}

  // Add GLU callbacks 
  PrimaryGraphicsHelper::init();
  glutDisplayFunc(PrimaryGraphicsHelper::display);
  glutReshapeFunc(PrimaryGraphicsHelper::reshape);
  glutSpecialFunc(PrimaryGraphicsHelper::special);
  glutKeyboardFunc(PrimaryGraphicsHelper::key);
  glutIdleFunc(PrimaryGraphicsHelper::idle);

  // Fire up weather updater thread for demo purposes
  WeatherUpdater* updater = new WeatherUpdater();
  std::thread updaterThread(&WeatherUpdater::demoThread, updater);

  // Exit program
  glutMainLoop();
  updaterThread.join();
  std::cout << "final_project::main(): exiting program" << std::endl;
  return 0;
}
