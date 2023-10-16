// File: hw6.cpp
// Author: Jared McKneely
// Description: Main runtime for Homework #6 (CSCI 5229)

#include <iostream>
#include "PrimaryGraphicsHelper.h"

// Main
int main(int argc, char* argv[]) {
  // Enter program
  std::cout << "hw6::main(): starting program" << std::endl;

  // Init GLUT w/ user args, z-buffer, double buffer
  glutInit(&argc, argv);
  glutInitWindowSize(600, 600);
  glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
  glutCreateWindow("Jared McKneely - CSCI 5229, Homework 6");

  // Init GLEW
  #ifdef USEGLEW
  try {PrimaryGraphicsHelper::initializeGlew();}
  catch (GenericHomeworkException& e) {std::cout << e.what() << ": GLEW initialization failed!" << std::endl; exit(1);}
  #endif

  // Add callbacks for GLUT and call main loop
  PrimaryGraphicsHelper::init();
  glutDisplayFunc(PrimaryGraphicsHelper::display);
  glutReshapeFunc(PrimaryGraphicsHelper::reshape);
  glutSpecialFunc(PrimaryGraphicsHelper::special);
  glutKeyboardFunc(PrimaryGraphicsHelper::key);
  glutMainLoop();

  // Exit program
  std::cout << "hw6::main(): exiting program" << std::endl;
  return 0;
}
