#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include "global_config.h"
#include "Rubik.h"
#include "Matrix.h"
#include "Rotation.h"
#include "Vector.h"
#include "Operate.h"

extern GLColor ColorBlack;
extern GLColor ColorWhite;
extern GLColor ColorRed;
extern GLColor ColorGreen;
extern GLColor ColorBlue;
extern GLColor ColorYellow;
extern GLColor ColorOrange;
void doAnimation(void);
extern float perspective;
extern int cameraType;
extern int upOrDown;
extern float AngleYZ;
extern float AngleZX;
extern float eye_direction;
static Matrix rotateMatrix;

void mouseTurn(Rubik* rubik,GLsizei lx,GLsizei ly,GLsizei nx,GLsizei ny) {
  GLfloat beginX,beginY,beginZ;
  GLfloat endX,endY,endZ;
  GLsizei beginface,endface,beginindex,endindex;
  convertToCoordinate(lx,ly,&beginX,&beginY,&beginZ);
  convertToCoordinate(nx,ny,&endX,&endY,&endZ);
  convertCoordinateToFace(beginX,beginY,beginZ,&beginface,&beginindex);
  convertCoordinateToFace(endX,endY,endZ,&endface,&endindex);
  if (beginface!=endface)
    return;
  if (beginindex==endindex)
    return;
  if (beginindex==-1 || endindex==-1)
    return;
  Vector beginLocation,endLocation;
  convertCubeIndexToVector(beginindex,&beginLocation);
  convertCubeIndexToVector(endindex,&endLocation);
  Vector DisplacementVector={endLocation.x-beginLocation.x,endLocation.y-beginLocation.y,endLocation.z-beginLocation.z};
  Vector rotateVector;
  vectorMulVector(&FACE_VECTOR[beginface],&DisplacementVector,&rotateVector);
  if (parallelVector(&rotateVector,&FACE_VECTOR[FACE_TOP])) {
    if (beginLocation.y==2)
      turnFace(rubik,FACE_TOP,TURN_CCW,ANIMATION_TRUE);
    if (beginLocation.y==0)
      turnFace(rubik,FACE_BOTTOM,TURN_CW,ANIMATION_TRUE);
  }
  if (parallelVector(&rotateVector,&FACE_VECTOR[FACE_BOTTOM])) {
    if (beginLocation.y==2)
      turnFace(rubik,FACE_TOP,TURN_CW,ANIMATION_TRUE);
    if (beginLocation.y==0)
      turnFace(rubik,FACE_BOTTOM,TURN_CCW,ANIMATION_TRUE);
  }
  if (parallelVector(&rotateVector,&FACE_VECTOR[FACE_LEFT])) {
    if (beginLocation.x==2)
      turnFace(rubik,FACE_RIGHT,TURN_CW,ANIMATION_TRUE);
    if (beginLocation.x==0)
      turnFace(rubik,FACE_LEFT,TURN_CCW,ANIMATION_TRUE);
  }
  if (parallelVector(&rotateVector,&FACE_VECTOR[FACE_RIGHT])) {
    if (beginLocation.x==2)
      turnFace(rubik,FACE_RIGHT,TURN_CCW,ANIMATION_TRUE);
    if (beginLocation.x==0)
      turnFace(rubik,FACE_LEFT,TURN_CW,ANIMATION_TRUE);
  }
  if (parallelVector(&rotateVector,&FACE_VECTOR[FACE_FRONT])) {
    if (beginLocation.z==2)
      turnFace(rubik,FACE_FRONT,TURN_CCW,ANIMATION_TRUE);
    if (beginLocation.z==0)
      turnFace(rubik,FACE_BACK,TURN_CW,ANIMATION_TRUE);
  }
  if (parallelVector(&rotateVector,&FACE_VECTOR[FACE_BACK])) {
    if (beginLocation.z==2)
      turnFace(rubik,FACE_FRONT,TURN_CW,ANIMATION_TRUE);
    if (beginLocation.z==0)
      turnFace(rubik,FACE_BACK,TURN_CCW,ANIMATION_TRUE);
  }
}
void convertToCoordinate(GLsizei inX,GLsizei inY,GLfloat* outX,GLfloat* outY,GLfloat* outZ) {
  GLint viewport[4];
  glGetIntegerv(GL_VIEWPORT,viewport);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(perspective,(float)viewport[2]/(float)viewport[3],0.1f,100.0f);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(EYE_DISTANCE*cos(AngleYZ/180*PI)*sin(AngleZX/180*PI),EYE_DISTANCE*sin(AngleYZ/180*PI),EYE_DISTANCE*cos(AngleYZ/180*PI)*cos(AngleZX/180*PI),0,0,0,0,eye_direction,0);
  GLdouble modelviewMatrix[16];
  GLdouble projectionMatrix[16];
  glGetDoublev(GL_MODELVIEW_MATRIX,modelviewMatrix);
  glGetDoublev(GL_PROJECTION_MATRIX,projectionMatrix);
  GLdouble x,y,z;
  GLfloat winX,winY,winZ;
  winX=(GLfloat)inX;
  winY=viewport[3]-(GLfloat)inY;
  glReadPixels(winX,winY,1,1,GL_DEPTH_COMPONENT,GL_FLOAT,&winZ);
  gluUnProject(winX,winY,winZ,modelviewMatrix,projectionMatrix,viewport,&x,&y,&z);
  *outX=x;
  *outY=y;
  *outZ=z;
}

void convertCoordinateToFace(GLfloat x,GLfloat y,GLfloat z,GLsizei* face,GLsizei* cubeindex) {
  GLsizei index;
  *face=FACE_UNKNOWN;
  if (fabs(x-CUBE_POINT1)<MOUSE_IDENTIFY_ACCURACY)
    *face=FACE_LEFT;
  if (fabs(x-CUBE_POINT6)<MOUSE_IDENTIFY_ACCURACY)
    *face=FACE_RIGHT;
  if (fabs(y-CUBE_POINT1)<MOUSE_IDENTIFY_ACCURACY)
    *face=FACE_BOTTOM;
  if (fabs(y-CUBE_POINT6)<MOUSE_IDENTIFY_ACCURACY)
    *face=FACE_TOP;
  if (fabs(z-CUBE_POINT1)<MOUSE_IDENTIFY_ACCURACY)
    *face=FACE_BACK;
  if (fabs(z-CUBE_POINT6)<MOUSE_IDENTIFY_ACCURACY)
    *face=FACE_FRONT;
  //index为对应面cube编号从小到大的顺序
  GLsizei i,j;
  index=9;
  if (*face==FACE_LEFT || *face==FACE_RIGHT) {
    if (y>CUBE_POINT1 && y<CUBE_POINT2)
      j=2;
    if (y>CUBE_POINT3 && y<CUBE_POINT4)
      j=1;
    if (y>CUBE_POINT5 && y<CUBE_POINT6)
      j=0;
    if (z>CUBE_POINT1 && z<CUBE_POINT2)
      i=0;
    if (z>CUBE_POINT3 && z<CUBE_POINT4)
      i=1;
    if (z>CUBE_POINT5 && z<CUBE_POINT6)
      i=2;
    index=j*3+i;
  }
  if (*face==FACE_BOTTOM || *face==FACE_TOP) {
    if (z>CUBE_POINT1 && z<CUBE_POINT2)
      j=0;
    if (z>CUBE_POINT3 && z<CUBE_POINT4)
      j=1;
    if (z>CUBE_POINT5 && z<CUBE_POINT6)
      j=2;
    if (x>CUBE_POINT1 && x<CUBE_POINT2)
      i=0;
    if (x>CUBE_POINT3 && x<CUBE_POINT4)
      i=1;
    if (x>CUBE_POINT5 && x<CUBE_POINT6)
      i=2;
    index=j*3+i;
  }
  if (*face==FACE_FRONT || *face==FACE_BACK) {
    if (x>CUBE_POINT1 && x<CUBE_POINT2)
      j=0;
    if (x>CUBE_POINT3 && x<CUBE_POINT4)
      j=1;
    if (x>CUBE_POINT5 && x<CUBE_POINT6)
      j=2;
    if (y>CUBE_POINT1 && y<CUBE_POINT2)
      i=2;
    if (y>CUBE_POINT3 && y<CUBE_POINT4)
      i=1;
    if (y>CUBE_POINT5 && y<CUBE_POINT6)
      i=0;
    index=i*3+j;
  }
  *cubeindex=-1;
  switch (*face)
  {
    case FACE_TOP:
      *cubeindex=index;
      break;
    case FACE_BOTTOM:
      *cubeindex=18+index;
      break;
    case FACE_LEFT:
      *cubeindex=3*(index);
      break;
    case FACE_RIGHT:
      *cubeindex=3*(index)+2;
      break;
    case FACE_FRONT:
      *cubeindex=9*(index/3)+6+(index%3);
      break;
    case FACE_BACK:
      *cubeindex=9*(index/3)+(index%3);
      break;
    default:break;
  }
}

void initRotation(Rubik* rubik,GLsizei face,GLsizei direction,GLsizei ani) {
  GLfloat rotateAngle;
  if (ani==ANIMATION_TRUE)
    rotateAngle=PER_ROTATE_ANGLE;
  else
    rotateAngle=90.0f;
  switch (face)
  {
    case FACE_TOP:
      if (direction==TURN_CCW) {
        for (int i=0;i<9;++i)
          rubik->rotation.cubeArray[i]=rubik->cubeArrayIndex[i];
        getRotateMatrix(&rotateMatrix,-rotateAngle,0.0f,1.0f,0.0f);
      } else {
        for (int i=0;i<9;++i)
          rubik->rotation.cubeArray[i]=rubik->cubeArrayIndex[i];
        getRotateMatrix(&rotateMatrix,rotateAngle,0.0f,1.0f,0.0f);
      }
      break;
    case FACE_BOTTOM:
      if (direction==TURN_CCW) {
        for (int i=0;i<9;++i)
          rubik->rotation.cubeArray[i]=rubik->cubeArrayIndex[18+i];
        getRotateMatrix(&rotateMatrix,rotateAngle,0.0f,1.0f,0.0f);
      } else {
        for (int i=0;i<9;++i)
          rubik->rotation.cubeArray[i]=rubik->cubeArrayIndex[18+i];
        getRotateMatrix(&rotateMatrix,-rotateAngle,0.0f,1.0f,0.0f);
      }
      break;
    case FACE_LEFT:
      if (direction==TURN_CCW) {
        for (int i=0;i<9;++i)
          rubik->rotation.cubeArray[i]=rubik->cubeArrayIndex[3*i];
        getRotateMatrix(&rotateMatrix,rotateAngle,1.0f,0.0f,0.0f);
      } else {
        for (int i=0;i<9;++i)
          rubik->rotation.cubeArray[i]=rubik->cubeArrayIndex[3*i];
        getRotateMatrix(&rotateMatrix,-rotateAngle,1.0f,0.0f,0.0f);
      }
      break;
    case FACE_RIGHT:
      if (direction==TURN_CCW) {
        for (int i=0;i<9;++i)
          rubik->rotation.cubeArray[i]=rubik->cubeArrayIndex[3*i+2];
        getRotateMatrix(&rotateMatrix,-rotateAngle,1.0f,0.0f,0.0f);
      } else {
        for (int i=0;i<9;++i)
          rubik->rotation.cubeArray[i]=rubik->cubeArrayIndex[3*i+2];
        getRotateMatrix(&rotateMatrix,rotateAngle,1.0f,0.0f,0.0f);
      }
      break;
    case FACE_FRONT:
      if (direction==TURN_CCW) {
        for (int i=0;i<3;++i)
          for (int k=0;k<3;++k)
            rubik->rotation.cubeArray[i*3+k]=rubik->cubeArrayIndex[9*i+k+6];
        getRotateMatrix(&rotateMatrix,-rotateAngle,0.0f,0.0f,1.0f);
      } else {
        for (int i=0;i<3;++i)
          for (int k=0;k<3;++k)
            rubik->rotation.cubeArray[i*3+k]=rubik->cubeArrayIndex[9*i+k+6];
        getRotateMatrix(&rotateMatrix,rotateAngle,0.0f,0.0f,1.0f);
      }
      break;
    case FACE_BACK:
      if (direction==TURN_CCW) {
        for (int i=0;i<3;++i)
          for (int k=0;k<3;++k)
            rubik->rotation.cubeArray[i*3+k]=rubik->cubeArrayIndex[9*i+k];
        getRotateMatrix(&rotateMatrix,rotateAngle,0.0f,0.0f,1.0f);
      } else {
        for (int i=0;i<3;++i)
          for (int k=0;k<3;++k)
            rubik->rotation.cubeArray[i*3+k]=rubik->cubeArrayIndex[9*i+k];
        getRotateMatrix(&rotateMatrix,-rotateAngle,0.0f,0.0f,1.0f);
      }
      break;
    default:return;break;
  }
  rubik->rotation.len=9;
  rubik->rotation.rotating=GL_TRUE;
  rubik->rotation.times=90/rotateAngle;
  rubik->rotation.m=&rotateMatrix;
}
static int nextIndex[][27]={
  //Top
  { 2, 5, 8, 1, 4, 7, 0 ,3 ,6 ,9 ,10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26},
  //Bottom
  { 0, 1, 2, 3, 4, 5, 6 ,7 ,8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 24, 21, 18, 25, 22, 19, 26, 23, 20},
  //LEFT
  { 6, 1, 2, 15, 4, 5, 24, 7, 8, 3, 10, 11, 12, 13, 14, 21, 16, 17, 0, 19, 20, 9, 22, 23, 18, 25, 26 },
  //RIGHT
  { 0, 1, 20, 3, 4, 11, 6, 7, 2, 9, 10, 23, 12, 13, 14, 15, 16, 5, 18, 19, 26, 21, 22, 17, 24, 25, 8 },
  //FRONT
  { 0, 1, 2, 3, 4, 5, 8, 17, 26, 9, 10, 11, 12, 13, 14, 7, 16, 25, 18, 19, 20, 21, 22, 23, 6, 15, 24 },
  //BACK
  { 18, 9, 0, 3, 4, 5, 6, 7, 8, 19, 10, 1, 12, 13, 14, 15, 16, 17, 20, 11, 2, 21, 22, 23, 24, 25, 26 },
};
//旋转角块
void turnFace(Rubik* rubik,GLsizei face,GLsizei direction,GLsizei animation) {
  if (rubik->rotation.rotating)
    return;
  if (face!=FACE_TOP && face!=FACE_BOTTOM && face!=FACE_LEFT && face!=FACE_RIGHT && face!=FACE_FRONT && face!=FACE_BACK)
    return;
  if (direction!=TURN_CCW && direction!=TURN_CW)
    return;
  GLCube* tmp[27];
  if (direction==TURN_CCW) {
    for (int i=0;i<27;++i)
      tmp[i]=rubik->cubeArrayIndex[nextIndex[face][i]];
    for (int i=0;i<27;++i)
      rubik->cubeArrayIndex[i]=tmp[i];
  } else {
    for (int i=0;i<27;++i)
      tmp[nextIndex[face][i]]=rubik->cubeArrayIndex[i];
    for (int i=0;i<27;++i)
      rubik->cubeArrayIndex[i]=tmp[i];
  }
  if (animation==ANIMATION_TRUE) {
    initRotation(rubik,face,direction,animation);
    glutIdleFunc(doAnimation);
  }
  else {
    initRotation(rubik,face,direction,animation);
    while (rotate(&rubik->rotation)) {
      glutPostRedisplay();
    }
  }
}
//检查面颜色是否一致
GLboolean checkFace(Rubik* rubik,GLsizei face) {
  switch (face)
  {
    case FACE_TOP:
      for (int i=0;i<9;++i)
        if (GLCubeGetFaceColor(rubik->cubeArrayIndex[i],face)!=&ColorGreen)
          return GL_FALSE;
      break;
    case FACE_BOTTOM:
      for (int i=0;i<9;++i)
        if (GLCubeGetFaceColor(rubik->cubeArrayIndex[i+18],face)!=&ColorBlue)
          return GL_FALSE;
      break;
    case FACE_LEFT:
      for (int i=0;i<9;++i)
        if (GLCubeGetFaceColor(rubik->cubeArrayIndex[3*i],face)!=&ColorYellow)
          return GL_FALSE;
      break;
    case FACE_RIGHT:
      for (int i=0;i<9;++i)
        if (GLCubeGetFaceColor(rubik->cubeArrayIndex[3*i+2],face)!=&ColorWhite) {
          return GL_FALSE;
        }
      break;
    case FACE_FRONT:
      for (int i=0;i<3;++i)
        for (int k=0;k<3;++k)
          if (GLCubeGetFaceColor(rubik->cubeArrayIndex[9*i+k+6],face)!=&ColorRed)
            return GL_FALSE;
      break;
    case FACE_BACK:
      for (int i=0;i<3;++i)
        for (int k=0;k<3;++k)
          if (GLCubeGetFaceColor(rubik->cubeArrayIndex[9*i+k],face)!=&ColorOrange)
            return GL_FALSE;
      break;
    default:return GL_FALSE;break;
  }
  return GL_TRUE;
}
