#include <GL/gl.h>
#include "Rubik.h"
void turnFace(Rubik*,GLsizei,GLsizei,GLsizei);
void initRotation(Rubik*,GLsizei,GLsizei,GLsizei);
void mouseTurn(Rubik*,GLsizei,GLsizei,GLsizei,GLsizei);
void convertCoordinateToFace(GLfloat,GLfloat,GLfloat,GLsizei*,GLsizei*);
void convertToCoordinate(GLsizei,GLsizei,GLfloat*,GLfloat*,GLfloat*);
GLboolean checkFace(Rubik*,GLsizei);
