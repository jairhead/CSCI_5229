/*
 * File: Mat4Ops.h
 * Author: Jared McKneely
 * Description: Library for matrix 4x4 operations (carried over from ex26 mat4.h)
 */

#ifndef _MAT_OPS_H
#define _MAT_OPS_H

#include <stdio.h>
#include <string.h>
#include <math.h>

class Mat4Ops {
  public:
    static void mat4vulkan(int k);
    static void mat4identity(float mat[]);
    static void mat4copy(float mat[],float m[]);
    static void mat4multMatrix(float mat[],float m[]);
    static void mat4rotate(float mat[],float th,float x,float y,float z);
    static void mat4translate(float mat[],float dx,float dy,float dz);
    static void mat4scale(float mat[],float Sx,float Sy,float Sz);
    static void mat4lookAt(float mat[16] , float Ex,float Ey,float Ez , float Cx,float Cy,float Cz , float Ux,float Uy,float Uz);
    static void mat3normalMatrix(float mat[16],float inv[9]);
    static void mat4normalMatrix(float mat[16],float inv[16]);
    static void mat4ortho(float mat[],float left,float right,float bottom,float top,float zNear,float zFar);
    static void mat4perspective(float mat[],float fovy,float asp,float zNear,float zFar);
    static void mat4print(const char* text,float m[16]);
    static void mat3print(const char* text,float m[9]);
  private:
    static int normalize(float* x,float* y,float* z);
};

#endif
