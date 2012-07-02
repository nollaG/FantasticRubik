#include <GL/gl.h>
#include "GLVertex.h"
#include "GLColor.h"
#include "Vector.h"
#ifndef _GLFACE_H
#define _GLFACE_H
typedef struct 
{
  GLVertex* vertexArray[4];
  GLColor* faceColor;
  GLsizei faceIndex; //Indicate which face this is FACE_XXX
  Vector normalVector;
} GLFace;
#endif
void GLFaceAddVertex(GLFace* face, GLsizei index,GLfloat [],GLfloat []);
GLsizei convertVectorToIndex(Vector*);
void convertIndexToVector(GLsizei, Vector*);
