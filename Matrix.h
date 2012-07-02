#include <GL/gl.h>
#include "GLVertex.h"
#include "Vector.h"
#ifndef _MATRIX_H
#define _MATRIX_H
typedef struct
{
  GLfloat matrix[9];
} Matrix;
#endif
void mulVertex(Matrix* ,GLVertex*);
void mulVector(Matrix* ,Vector*);
void loadMatrix(Matrix*,GLfloat []);
void getRotateMatrix(Matrix*,GLfloat,GLfloat,GLfloat,GLfloat);
void matrixInit();
