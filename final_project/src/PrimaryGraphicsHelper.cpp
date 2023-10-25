/*
 * File: PrimaryGraphicsHelper.cpp
 * Author: Jared McKneely
 * Description: Implementation file for PrimaryGraphicsHelper, a helper class
 *              used for drawing a complex scene.
 */

#include "PrimaryGraphicsHelper.h"

// Constructor
PrimaryGraphicsHelper::PrimaryGraphicsHelper() { }

// Destructor
PrimaryGraphicsHelper::~PrimaryGraphicsHelper() { }

// init() public member function
// Initializes all objects
void PrimaryGraphicsHelper::init() { }

// display() public member function
// Callback for glutDisplayFunc()
void PrimaryGraphicsHelper::display() { }

// reshape() public member function
// Callback for glutReshapeFunc()
void PrimaryGraphicsHelper::reshape(int w, int h) { }

// special() public member function
// Callback for glutSpecialFunc()
void PrimaryGraphicsHelper::special(int key, int x, int y) { }

// key() public member function
// Callback for glutKeyboardFunc()
void PrimaryGraphicsHelper::key(unsigned char ch, int x, int y) { }

// idle() public member function
// Primary OpenGL idle handler function
// Callback for glutIdleFunc()
void PrimaryGraphicsHelper::idle() { }

// displayParams private member function
// Helper method that displays parameters to the window
void PrimaryGraphicsHelper::displayParams() { }
