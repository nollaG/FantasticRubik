#include <GL/gl.h>
#include <stdio.h>
#include "GLCube.h"
#include "GLFace.h"
#include "global_config.h"
#include "Rubik.h"
#include "Operate.h"
GLColor ColorBlack={0.0,0.0,0.0};
GLColor ColorWhite={1.0,1.0,1.0};
GLColor ColorRed={1.0,0.0,0.0};
GLColor ColorGreen={0.0,1.0,0.0};
GLColor ColorBlue={0.0,0.0,1.0};
GLColor ColorYellow={1.0,1.0,0.0};
GLColor ColorOrange={1.0,0.5,0.0};
int RubikInitArray(Rubik* rubik,GLfloat vertexArray[],GLfloat colorArray[]) {
  GLsizei index=0;
  for (int i=0;i<27;++i)
    for (int j=0;j<6;++j) {
      GLFaceAddVertex(&(rubik->cubeArray[i].faceArray[j]), index, vertexArray, colorArray);
      index+=1;
    }
  return index;
}
GLboolean checkRubik(Rubik* rubik) {
  for (int i=0;i<6;++i)
    if (!checkFace(rubik,i)) {
      return GL_FALSE;
    }
  return GL_TRUE;
}
void RubikInit(Rubik* rubik) {
  //TopBack left->right
  CubeInit(&rubik->cubeArray[0],CUBE_POINT1,CUBE_POINT2,CUBE_POINT5,CUBE_POINT6,CUBE_POINT1,CUBE_POINT2);
  CubeInit(&rubik->cubeArray[1],CUBE_POINT3,CUBE_POINT4,CUBE_POINT5,CUBE_POINT6,CUBE_POINT1,CUBE_POINT2);
  CubeInit(&rubik->cubeArray[2],CUBE_POINT5,CUBE_POINT6,CUBE_POINT5,CUBE_POINT6,CUBE_POINT1,CUBE_POINT2);
  //TopMiddle left->right
  CubeInit(&rubik->cubeArray[3],CUBE_POINT1,CUBE_POINT2,CUBE_POINT5,CUBE_POINT6,CUBE_POINT3,CUBE_POINT4);
  CubeInit(&rubik->cubeArray[4],CUBE_POINT3,CUBE_POINT4,CUBE_POINT5,CUBE_POINT6,CUBE_POINT3,CUBE_POINT4);
  CubeInit(&rubik->cubeArray[5],CUBE_POINT5,CUBE_POINT6,CUBE_POINT5,CUBE_POINT6,CUBE_POINT3,CUBE_POINT4);
  //TopFront left->right
  CubeInit(&rubik->cubeArray[6],CUBE_POINT1,CUBE_POINT2,CUBE_POINT5,CUBE_POINT6,CUBE_POINT5,CUBE_POINT6);
  CubeInit(&rubik->cubeArray[7],CUBE_POINT3,CUBE_POINT4,CUBE_POINT5,CUBE_POINT6,CUBE_POINT5,CUBE_POINT6);
  CubeInit(&rubik->cubeArray[8],CUBE_POINT5,CUBE_POINT6,CUBE_POINT5,CUBE_POINT6,CUBE_POINT5,CUBE_POINT6);
  //MiddleBack left->right
  CubeInit(&rubik->cubeArray[9],CUBE_POINT1,CUBE_POINT2,CUBE_POINT3,CUBE_POINT4,CUBE_POINT1,CUBE_POINT2);
  CubeInit(&rubik->cubeArray[10],CUBE_POINT3,CUBE_POINT4,CUBE_POINT3,CUBE_POINT4,CUBE_POINT1,CUBE_POINT2);
  CubeInit(&rubik->cubeArray[11],CUBE_POINT5,CUBE_POINT6,CUBE_POINT3,CUBE_POINT4,CUBE_POINT1,CUBE_POINT2);
  //MiddleMiddle left->right
  CubeInit(&rubik->cubeArray[12],CUBE_POINT1,CUBE_POINT2,CUBE_POINT3,CUBE_POINT4,CUBE_POINT3,CUBE_POINT4);
  CubeInit(&rubik->cubeArray[13],CUBE_POINT3,CUBE_POINT4,CUBE_POINT3,CUBE_POINT4,CUBE_POINT3,CUBE_POINT4);
  CubeInit(&rubik->cubeArray[14],CUBE_POINT5,CUBE_POINT6,CUBE_POINT3,CUBE_POINT4,CUBE_POINT3,CUBE_POINT4);
  //MiddleFront left->right
  CubeInit(&rubik->cubeArray[15],CUBE_POINT1,CUBE_POINT2,CUBE_POINT3,CUBE_POINT4,CUBE_POINT5,CUBE_POINT6);
  CubeInit(&rubik->cubeArray[16],CUBE_POINT3,CUBE_POINT4,CUBE_POINT3,CUBE_POINT4,CUBE_POINT5,CUBE_POINT6);
  CubeInit(&rubik->cubeArray[17],CUBE_POINT5,CUBE_POINT6,CUBE_POINT3,CUBE_POINT4,CUBE_POINT5,CUBE_POINT6);
  //BottomBack left->right
  CubeInit(&rubik->cubeArray[18],CUBE_POINT1,CUBE_POINT2,CUBE_POINT1,CUBE_POINT2,CUBE_POINT1,CUBE_POINT2);
  CubeInit(&rubik->cubeArray[19],CUBE_POINT3,CUBE_POINT4,CUBE_POINT1,CUBE_POINT2,CUBE_POINT1,CUBE_POINT2);
  CubeInit(&rubik->cubeArray[20],CUBE_POINT5,CUBE_POINT6,CUBE_POINT1,CUBE_POINT2,CUBE_POINT1,CUBE_POINT2);
  //BottomMiddle left->right
  CubeInit(&rubik->cubeArray[21],CUBE_POINT1,CUBE_POINT2,CUBE_POINT1,CUBE_POINT2,CUBE_POINT3,CUBE_POINT4);
  CubeInit(&rubik->cubeArray[22],CUBE_POINT3,CUBE_POINT4,CUBE_POINT1,CUBE_POINT2,CUBE_POINT3,CUBE_POINT4);
  CubeInit(&rubik->cubeArray[23],CUBE_POINT5,CUBE_POINT6,CUBE_POINT1,CUBE_POINT2,CUBE_POINT3,CUBE_POINT4);
  //BottomFront left->right
  CubeInit(&rubik->cubeArray[24],CUBE_POINT1,CUBE_POINT2,CUBE_POINT1,CUBE_POINT2,CUBE_POINT5,CUBE_POINT6);
  CubeInit(&rubik->cubeArray[25],CUBE_POINT3,CUBE_POINT4,CUBE_POINT1,CUBE_POINT2,CUBE_POINT5,CUBE_POINT6);
  CubeInit(&rubik->cubeArray[26],CUBE_POINT5,CUBE_POINT6,CUBE_POINT1,CUBE_POINT2,CUBE_POINT5,CUBE_POINT6);
  for (int i=0;i<27;++i)
    rubik->cubeArrayIndex[i]=&(rubik->cubeArray[i]);


  for (int i=0;i<27;++i)
    for (int j=0;j<6;++j)
      GLCubeSetFaceColor(&rubik->cubeArray[i],j,&ColorBlack);
  for (int i=0;i<9;++i)
    GLCubeSetFaceColor(&rubik->cubeArray[i],FACE_TOP,&ColorGreen);
  for (int i=0;i<9;++i)
    GLCubeSetFaceColor(&rubik->cubeArray[i+18],FACE_BOTTOM,&ColorBlue);
  for (int i=0;i<3;++i)
    for (int j=0;j<3;++j)
      GLCubeSetFaceColor(&rubik->cubeArray[i*9+j+6],FACE_FRONT,&ColorRed);
  for (int i=0;i<3;++i)
    for (int j=0;j<3;++j)
      GLCubeSetFaceColor(&rubik->cubeArray[i*9+j],FACE_BACK,&ColorOrange);
  for (int i=0;i<9;++i)
    GLCubeSetFaceColor(&rubik->cubeArray[3*i],FACE_LEFT,&ColorYellow);
  for (int i=0;i<9;++i)
    GLCubeSetFaceColor(&rubik->cubeArray[3*i+2],FACE_RIGHT,&ColorWhite);
}

