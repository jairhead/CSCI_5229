/*
 * File: hw3.cpp
 * Author: Jared McKneely
 * Description: Main runtime for Homework #3 (CSCI 5229)
 */

#include <iostream>
#include "GenericHomeworkException.h"
#include "PrimaryGraphicsHelper.h"

// Main
int main(int argc,char* argv[])
{
  // Enter program
  std::cout << "hw3::main(): starting program" << std::endl;

  // Initialize GLUT w/ user args, z buffer, double buffer
  glutInit(&argc, argv);
  glutInitWindowSize(600, 600);
  glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
  glutCreateWindow("Jared McKneely - CSCI 5229, Homework 3");

  // Initialize GLEW
  #ifdef USEGLEW
  try {PrimaryGraphicsHelper::initializeGlew();}
  catch (GenericHomeworkException& e) { std::cout << e.what() << ": GLEW initialization failed!" << std::endl; }
  #endif

  // Pass callback methods to GLUT
  PrimaryGraphicsHelper::init();
  glutDisplayFunc(PrimaryGraphicsHelper::display);
  glutReshapeFunc(PrimaryGraphicsHelper::reshape);
  glutSpecialFunc(PrimaryGraphicsHelper::special);
  glutKeyboardFunc(PrimaryGraphicsHelper::key);
  glutIdleFunc(PrimaryGraphicsHelper::idle);

  // Call GLUT main loop
  glutMainLoop();

  // Exit program
  std::cout << "hw3::main(): exiting program" << std::endl;
  return 0;
}
