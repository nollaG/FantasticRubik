#include <GL/gl.h>
#include <math.h>
#include "Matrix.h"
#include "global_config.h"
#define PI 3.1415926535897
void loadMatrix(Matrix* m,GLfloat matrixArray[]) {
  for (int i=0;i<9;++i)
    m->matrix[i]=matrixArray[i];
}

void getRotateMatrix(Matrix* m,GLfloat Angle,GLfloat x,GLfloat y,GLfloat z) {
  GLfloat rotation[16];
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();
  glRotatef(Angle,x,y,z);
  glGetFloatv(GL_MODELVIEW_MATRIX,rotation);
  for (int i=0;i<9;++i)
    m->matrix[i]=rotation[i/3+i];
  glPopMatrix();
}
void mulVertex(Matrix* m,GLVertex* v) {
  GLfloat tmpx,tmpy,tmpz;
  tmpx=m->matrix[0]*v->x+m->matrix[1]*v->y+m->matrix[2]*v->z;
  tmpy=m->matrix[3]*v->x+m->matrix[4]*v->y+m->matrix[5]*v->z;
  tmpz=m->matrix[6]*v->x+m->matrix[7]*v->y+m->matrix[8]*v->z;
  v->x=tmpx;
  v->y=tmpy;
  v->z=tmpz;
}
void mulVector(Matrix* m,Vector* v) {
  GLfloat tmpx,tmpy,tmpz;
  tmpx=m->matrix[0]*v->x+m->matrix[1]*v->y+m->matrix[2]*v->z;
  tmpy=m->matrix[3]*v->x+m->matrix[4]*v->y+m->matrix[5]*v->z;
  tmpz=m->matrix[6]*v->x+m->matrix[7]*v->y+m->matrix[8]*v->z;
  v->x=tmpx;
  v->y=tmpy;
  v->z=tmpz;
}
