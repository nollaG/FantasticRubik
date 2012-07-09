#include <GL/gl.h>
#ifndef _GLCOLOR_H
#define _GLCOLOR_H
typedef struct
{
  GLfloat red;
  GLfloat green;
  GLfloat blue;
} GLColor;
#endif
char convertColorToFaceChar(GLColor*);
extern GLColor ColorBlack;
extern GLColor ColorWhite;
extern GLColor ColorRed;
extern GLColor ColorGreen;
extern GLColor ColorBlue;
extern GLColor ColorYellow;
extern GLColor ColorOrange;
