#include <GL/gl.h>
#include "GLCube.h"
#include "GLFace.h"
#include "GLVertex.h"
#include "Vector.h"
#include "global_config.h"
void FixCube(GLCube* cube) {
  for (int i=0;i<8;++i)
    FixVertex(&cube->vertexArray[i]);
}
void CubeInit(GLCube* cube,GLfloat left,GLfloat right,GLfloat bottom,GLfloat top,GLfloat back,GLfloat front) {
  //leftTopBack
  cube->vertexArray[0].x=left;
  cube->vertexArray[0].y=top;
  cube->vertexArray[0].z=back;
  //leftTopFront
  cube->vertexArray[1].x=left;
  cube->vertexArray[1].y=top;
  cube->vertexArray[1].z=front;
  //leftBottomBack
  cube->vertexArray[2].x=left;
  cube->vertexArray[2].y=bottom;
  cube->vertexArray[2].z=back;
  //leftBottomFront
  cube->vertexArray[3].x=left;
  cube->vertexArray[3].y=bottom;
  cube->vertexArray[3].z=front;
  //rightTopBack
  cube->vertexArray[4].x=right;
  cube->vertexArray[4].y=top;
  cube->vertexArray[4].z=back;
  //rightTopFront
  cube->vertexArray[5].x=right;
  cube->vertexArray[5].y=top;
  cube->vertexArray[5].z=front;
  //rightBottomBack
  cube->vertexArray[6].x=right;
  cube->vertexArray[6].y=bottom;
  cube->vertexArray[6].z=back;
  //rightBottomFront
  cube->vertexArray[7].x=right;
  cube->vertexArray[7].y=bottom;
  cube->vertexArray[7].z=front;
  //top
  cube->faceArray[FACE_TOP].vertexArray[0]=&cube->vertexArray[1];
  cube->faceArray[FACE_TOP].vertexArray[1]=&cube->vertexArray[5];
  cube->faceArray[FACE_TOP].vertexArray[2]=&cube->vertexArray[4];
  cube->faceArray[FACE_TOP].vertexArray[3]=&cube->vertexArray[0];
  cube->faceArray[FACE_TOP].faceIndex=FACE_TOP;
  copyVector(&FACE_VECTOR[FACE_TOP],&cube->faceArray[FACE_TOP].normalVector);
  //bottom
  cube->faceArray[FACE_BOTTOM].vertexArray[0]=&cube->vertexArray[3];
  cube->faceArray[FACE_BOTTOM].vertexArray[1]=&cube->vertexArray[2];
  cube->faceArray[FACE_BOTTOM].vertexArray[2]=&cube->vertexArray[6];
  cube->faceArray[FACE_BOTTOM].vertexArray[3]=&cube->vertexArray[7];
  cube->faceArray[FACE_BOTTOM].faceIndex=FACE_BOTTOM;
  copyVector(&FACE_VECTOR[FACE_BOTTOM],&cube->faceArray[FACE_BOTTOM].normalVector);
  //left
  cube->faceArray[FACE_LEFT].vertexArray[0]=&cube->vertexArray[1];
  cube->faceArray[FACE_LEFT].vertexArray[1]=&cube->vertexArray[0];
  cube->faceArray[FACE_LEFT].vertexArray[2]=&cube->vertexArray[2];
  cube->faceArray[FACE_LEFT].vertexArray[3]=&cube->vertexArray[3];
  cube->faceArray[FACE_LEFT].faceIndex=FACE_LEFT;
  copyVector(&FACE_VECTOR[FACE_LEFT],&cube->faceArray[FACE_LEFT].normalVector);
  //right
  cube->faceArray[FACE_RIGHT].vertexArray[0]=&cube->vertexArray[7];
  cube->faceArray[FACE_RIGHT].vertexArray[1]=&cube->vertexArray[6];
  cube->faceArray[FACE_RIGHT].vertexArray[2]=&cube->vertexArray[4];
  cube->faceArray[FACE_RIGHT].vertexArray[3]=&cube->vertexArray[5];
  cube->faceArray[FACE_RIGHT].faceIndex=FACE_RIGHT;
  copyVector(&FACE_VECTOR[FACE_RIGHT],&cube->faceArray[FACE_RIGHT].normalVector);
  //FRONT
  cube->faceArray[FACE_FRONT].vertexArray[0]=&cube->vertexArray[3];
  cube->faceArray[FACE_FRONT].vertexArray[1]=&cube->vertexArray[7];
  cube->faceArray[FACE_FRONT].vertexArray[2]=&cube->vertexArray[5];
  cube->faceArray[FACE_FRONT].vertexArray[3]=&cube->vertexArray[1];
  cube->faceArray[FACE_FRONT].faceIndex=FACE_FRONT;
  copyVector(&FACE_VECTOR[FACE_FRONT],&cube->faceArray[FACE_FRONT].normalVector);
  //BACK
  cube->faceArray[FACE_BACK].vertexArray[0]=&cube->vertexArray[0];
  cube->faceArray[FACE_BACK].vertexArray[1]=&cube->vertexArray[4];
  cube->faceArray[FACE_BACK].vertexArray[2]=&cube->vertexArray[6];
  cube->faceArray[FACE_BACK].vertexArray[3]=&cube->vertexArray[2];
  cube->faceArray[FACE_BACK].faceIndex=FACE_BACK;
  copyVector(&FACE_VECTOR[FACE_BACK],&cube->faceArray[FACE_BACK].normalVector);
}

void GLCubeSetFaceColor(GLCube* cube,GLsizei face,GLColor* color) {
  for (int i=0;i<6;++i)
    if (cube->faceArray[i].faceIndex==face)
      cube->faceArray[i].faceColor=color;
}
GLColor* GLCubeGetFaceColor(GLCube* cube,GLsizei face) {
  for (int i=0;i<6;++i)
    if (cube->faceArray[i].faceIndex==face)
      return cube->faceArray[i].faceColor;
  return NULL;
}
void convertCubeIndexToVector(GLsizei i,Vector* v) {
  v->y=2-(GLfloat)(i/9);
  v->z=(GLfloat)((i%9)/3);
  v->x=(GLfloat)(i%3);
}
