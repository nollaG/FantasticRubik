#include "GLFace.h"
#include <GL/gl.h>
#ifndef _GLCUBE_H
#define _GLCUBE_H
typedef struct
{
  GLFace faceArray[6];
  GLVertex vertexArray[8];
} GLCube;
#endif
void CubeInit(GLCube*,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat);
void GLCubeSetFaceColor(GLCube*,GLsizei,GLColor*);
GLColor* GLCubeGetFaceColor(GLCube*,GLsizei);
void FixCube(GLCube*);
void convertCubeIndexToVector(GLsizei,Vector*);
