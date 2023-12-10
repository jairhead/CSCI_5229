/*
 * File: Mat4Ops.cpp
 * Author: Jared McKneely
 * Description: Implementation file for the Mat4Ops class (carried over from ex26 mat4.c)
 */

#include "Mat4Ops.h"

//  OpenGL or Vulkan
static int vulkan=0;

//  Identity matrix
static const float I[] = {1,0,0,0 , 0,1,0,0 , 0,0,1,0 , 0,0,0,1};

// mat4vulkan() public member function
// Set mat4 mode to OpenGL or Vulkan
void Mat4Ops::mat4vulkan(int k) {
   vulkan = k;
}

// mat4identity() public member function
// Identity 4x4 matrix
void Mat4Ops::mat4identity(float mat[]) {
   memcpy(mat,I,sizeof(I));
}

// mat4copy() public member function
// Copies 4x4 matrix
void Mat4Ops::mat4copy(float mat[],float m[]) {
   memcpy(mat,m,sizeof(I));
}

// mat4multMatrix() public member function
// Right multiply 4x4 matrix
void Mat4Ops::mat4multMatrix(float mat[],float m[]) {
   //  res = mat*m
   float res[16];
   for (int i=0;i<4;i++)
      for (int j=0;j<4;j++)
         res[4*i+j] = mat[j]*m[4*i] + mat[4+j]*m[4*i+1] + mat[8+j]*m[4*i+2] + mat[12+j]*m[4*i+3];
   //  Copy matrix back
   memcpy(mat,res,sizeof(res));
}

// mat4rotate() public member function
// Rotates the matrix
void Mat4Ops::mat4rotate(float mat[],float th,float x,float y,float z) {
   //  Normalize axis
   float l = sqrt(x*x+y*y+z*z);
   if (l==0) return;
   x /= l;
   y /= l;
   z /= l;
   //  Calculate sin and cos
   float s = sin(th*M_PI/180);
   float c = cos(th*M_PI/180);
   //  Rotation matrix
   float R[16] =
   {
      (1-c)*x*x+c   , (1-c)*x*y+z*s , (1-c)*z*x-y*s , 0 ,
      (1-c)*x*y-z*s , (1-c)*y*y+c   , (1-c)*y*z+x*s , 0 ,
      (1-c)*z*x+y*s , (1-c)*y*z-x*s , (1-c)*z*z+c   , 0 ,
            0       ,       0       ,       0       , 1 ,
   };
   //  Multiply
   mat4multMatrix(mat,R);
}

// mat4translate() public member function
// Translates the matrix
void Mat4Ops::mat4translate(float mat[],float dx,float dy,float dz) {
   //  Scale matrix
   float T[16];
   mat4identity(T);
   T[12] = dx;
   T[13] = dy;
   T[14] = dz;
   //  Multiply
   mat4multMatrix(mat,T);
}

// mat4scale() public member function
// Scales the matrix
void Mat4Ops::mat4scale(float mat[],float Sx,float Sy,float Sz) {
   //  Scale matrix
   float S[16];
   memset(S,0,sizeof(S));
   S[0]  = Sx;
   S[5]  = Sy;
   S[10] = Sz;
   S[15] = 1;
   //  Multiply
   mat4multMatrix(mat,S);
}

// normalize() public member function
// Normalizes vector
int Mat4Ops::normalize(float* x,float* y,float* z) {
   float l = sqrt((*x)*(*x)+(*y)*(*y)+(*z)*(*z));
   if (l==0) return -1;
   *x /= l;
   *y /= l;
   *z /= l;
   return 0;
}

// mat4lookAt() public member function
// Set eye position
void Mat4Ops::mat4lookAt(float mat[16] , float Ex,float Ey,float Ez , float Cx,float Cy,float Cz , float Ux,float Uy,float Uz) {
   //  Forward = C-E
   float Fx = Cx-Ex;
   float Fy = Cy-Ey;
   float Fz = Cz-Ez;
   if (normalize(&Fx,&Fy,&Fz)) return;
   // Side = Forward x Up
   float Sx = Fy*Uz-Uy*Fz;
   float Sy = Fz*Ux-Uz*Fx;
   float Sz = Fx*Uy-Ux*Fy;
   if (normalize(&Sx,&Sy,&Sz)) return;
   //  Recalculate Up = Side x Forward
   Ux = Sy*Fz-Fy*Sz;
   Uy = Sz*Fx-Fz*Sx;
   Uz = Sx*Fy-Fx*Sy;
   //  Rotation (inverse read transposed)
   float R[16] =
   {
    Sx, Ux, -Fx, 0,
    Sy, Uy, -Fy, 0,
    Sz, Uz, -Fz, 0,
    0,  0,    0, 1,
   };
   mat4multMatrix(mat,R);
   //  Set eye at the origin
   mat4translate(mat,-Ex,-Ey,-Ez);
}

// mat3normalMatrix() public member function
// Computes inverse of a general 3d transformation matrix.
// Adapted from graphics gems II.
void Mat4Ops::mat3normalMatrix(float mat[16],float inv[9]) {
   // Calculate the determinant of upper left 3x3 submatrix
   float det = mat[0]*mat[5]*mat[10]
              +mat[1]*mat[6]*mat[8]
              +mat[2]*mat[4]*mat[9]
              -mat[2]*mat[5]*mat[8]
              -mat[1]*mat[4]*mat[10]
              -mat[0]*mat[6]*mat[9];
   if (det*det<1e-25) return;
   //  Compute inverse using Cramer's rule
   inv[0] =  (mat[5]*mat[10]-mat[6]*mat[9])/det;
   inv[1] = -(mat[4]*mat[10]-mat[6]*mat[8])/det;
   inv[2] =  (mat[4]*mat[ 9]-mat[5]*mat[8])/det;
   inv[3] = -(mat[1]*mat[10]-mat[2]*mat[9])/det;
   inv[4] =  (mat[0]*mat[10]-mat[2]*mat[8])/det;
   inv[5] = -(mat[0]*mat[ 9]-mat[1]*mat[8])/det;
   inv[6] =  (mat[1]*mat[ 6]-mat[2]*mat[5])/det;
   inv[7] = -(mat[0]*mat[ 6]-mat[2]*mat[4])/det;
   inv[8] =  (mat[0]*mat[ 5]-mat[1]*mat[4])/det;
}

// mat4normalMatrix() public member function
// 4x4 version of normal matrix to fix alignment
void Mat4Ops::mat4normalMatrix(float mat[16],float inv[16]) {
   //  Compute 3x3 normal matrix
   mat3normalMatrix(mat,inv);
   //  Expand 3x3 to 4x4
   inv[15] = 1;
   inv[14] = 0;
   inv[13] = 0;
   inv[12] = 0;
   inv[11] = 0;
   inv[10] = inv[8];
   inv[9] = inv[7];
   inv[8] = inv[6];
   inv[7] = 0;
   inv[6] = inv[5];
   inv[5] = inv[4];
   inv[4] = inv[3];
   inv[3] = 0;
   inv[2] = inv[2];
   inv[1] = inv[1];
   inv[0] = inv[0];
}

// mat4ortho() public member function
// Orthogonal projection matrix
void Mat4Ops::mat4ortho(float mat[],float left,float right,float bottom,float top,float zNear,float zFar) {
   //  Projection matrix
   float P[16];
   memset(P,0,sizeof(P));
   P[0] = 2/(right-left);
   P[12] = -(right+left)/(right-left);
   P[13] = -(top+bottom)/(top-bottom);
   P[15] = 1;
   if (vulkan)
   {
      P[5]  = -2/(top-bottom);
      P[10] = 1/(zFar-zNear);
      P[14] = 0.5-(zFar+zNear)/(zFar-zNear);
   }
   else
   {
      P[5]  = 2/(top-bottom);
      P[10] = -2/(zFar-zNear);
      P[14] = -(zFar+zNear)/(zFar-zNear);
   }
   //  Multiply
   mat4multMatrix(mat,P);
}

// mat4perspective() public member function
// Perspective projection matrix
void Mat4Ops::mat4perspective(float mat[],float fovy,float asp,float zNear,float zFar) {
   //  Cotangent
   float s = sin(fovy/2*M_PI/180);
   float c = cos(fovy/2*M_PI/180);
   if (s==0) return;
   float cot = c/s;
   //  Matrix
   float P[16];
   memset(P,0,sizeof(P));
   P[0]  = cot/asp;
   P[11] = -1;
   if (vulkan)
   {
      P[5]  = -cot;
      P[10] = zNear/(zFar-zNear);
      P[14] = zFar*P[10];
   }
   else
   {
      P[5]  = cot;
      P[10] = -(zFar+zNear)/(zFar-zNear);
      P[14] = -2*zNear*zFar/(zFar-zNear);
   }
   //  Multiply
   mat4multMatrix(mat,P);
}

// mat4print() public member function
// Prints 4x4 matrix to stderr
void Mat4Ops::mat4print(const char* text,float m[16]) {
   fprintf(stderr,"%s %s\n",text,vulkan?"Vulkan":"OpenGL");
   for (int i=0;i<4;i++)
      fprintf(stderr,"%10.6f %10.6f %10.6f %10.6f\n",m[i],m[i+4],m[i+8],m[i+12]);
}

// mat3print() public member function
// Prints 3x3 matrix to stderr
void Mat4Ops::mat3print(const char* text,float m[9]) {
   fprintf(stderr,"%s\n",text);
   for (int i=0;i<3;i++)
      fprintf(stderr,"%10.6f %10.6f %10.6f\n",m[i],m[i+3],m[i+6]);
}
