#include <GL/gl.h>
#include <math.h>
#include "GLVertex.h"
void FixVertex(GLVertex* v) {
  v->x=round(v->x*10)/10;
  v->y=round(v->y*10)/10;
  v->z=round(v->z*10)/10;
}
