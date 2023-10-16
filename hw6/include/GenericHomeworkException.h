/*
 * File: GenericHomeworkException.h
 * Author: Jared McKneely
 * Description: Generic exception defined for homework errors
 */

#ifndef _HOMEWORK_EXCEPTION_H
#define _HOMEWORK_EXCEPTION_H

#include <exception>
#include <string>
using namespace std;

class GenericHomeworkException : public std::exception {
  public:
    virtual const char* what() const throw() {
      return "[ERROR] Homework Exception Caught"; 
    }
};

#endif
