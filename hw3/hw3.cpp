/*
 * File: hw3.cpp
 * Author: Jared McKneely
 * Description: Main runtime for Homework #3 (CSCI 5229)
 */

#include <stdio.h>
#include <iostream>
#include <PrimaryGraphicsHelper.h>

// Main
int main(int arc,char* argv[])
{
  // Enter program
  std::cout << "hw3::main(): starting program" << std::endl;

  // Initialize GLUT w/ user args, double buffer
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
  glutInitWindowSize(500, 500);
  glutCreateWindow("Jared McKneely - CSCI 5229, Homework 3");

  // Pass callback methods to GLUT
  glutDisplayFunc(PrimaryGraphicsHelper::display);
  glutReshapeFunc(PrimaryGraphicsHelper::reshape);
  glutSpecialFunc(PrimaryGraphicsHelper::special);
  glutKeyboardFunc(PrimaryGraphicsHelper::key);

  // Call GLUT main loop
  glutMainLoop();

  // Exit program
  std::cout << "hw3::main(): exiting program" << std::endl;
  return 0;
}
