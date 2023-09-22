/*
 * File: GlewException.h
 * Author: Jared McKneely
 * Description: Exception defined for GLEW initialization failure
 */

#include <iostream>
#include <exception>
using namespace std;

class GlewException : public std::exception {
  public:
    virtual const char* what() const throw() { 
      return "[ERROR] GLEW failed to initialize!"; 
    }    
};
