#include <GL/gl.h>
#include "GLCube.h"
#include "Rotation.h"
#ifndef _RUBIK_H
#define _RUBIK_H
typedef struct
{
  GLCube cubeArray[27];
  GLCube* cubeArrayIndex[27];
  Rotation rotation;
} Rubik;
#endif
int RubikInitArray(Rubik*,GLfloat [],GLfloat []); //return index
void RubikInit(Rubik*);
GLboolean checkRubik(Rubik*);
void setRubikState(Rubik*,char state[20][4]);
void generateState(Rubik*,char state[20][4]);
extern GLColor ColorBlack;
extern GLColor ColorWhite;
extern GLColor ColorRed;
extern GLColor ColorGreen;
extern GLColor ColorBlue;
extern GLColor ColorYellow;
extern GLColor ColorOrange;
