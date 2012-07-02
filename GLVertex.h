#include <GL/gl.h>
#ifndef _GLVERTEX_H
#define _GLVERTEX_H
typedef struct
{
  GLfloat x;
  GLfloat y;
  GLfloat z;
} GLVertex;
#endif
void FixVertex(GLVertex*);
