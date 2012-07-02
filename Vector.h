#include <GL/gl.h>
#ifndef _VECTOR_H
#define _VECTOR_H
typedef struct
{
  GLfloat x;
  GLfloat y;
  GLfloat z;
} Vector;
#endif
GLboolean compareVector(Vector*,Vector*);
void copyVector(Vector*,Vector*);
void vectorMulVector(Vector*,Vector*,Vector*);
GLboolean parallelVector(Vector* ,Vector*);
//extern Vector FRONT_VECTOR;
//extern Vector BACK_VECTOR;
//extern Vector TOP_VECTOR;
//extern Vector BOTTOM_VECTOR;
//extern Vector LEFT_VECTOR;
//extern Vector RIGHT_VECTOR;
extern Vector FACE_VECTOR[6];
extern Vector ZERO_VECTOR;
