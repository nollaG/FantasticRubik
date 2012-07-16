#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>
#include "GLCube.h"
#include "GLFace.h"
#include "GLColor.h"
#include "global_config.h"
#include "Rubik.h"
#include "Operate.h"
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


void setRubikState(Rubik* rubik,char state[20][4]) {
  GLCubeSetFaceColor(rubik->cubeArrayIndex[7],FACE_TOP,convertFaceCharToColor(state[0][0]));
  GLCubeSetFaceColor(rubik->cubeArrayIndex[7],FACE_FRONT,convertFaceCharToColor(state[0][1]));
  GLCubeSetFaceColor(rubik->cubeArrayIndex[5],FACE_TOP,convertFaceCharToColor(state[1][0]));
  GLCubeSetFaceColor(rubik->cubeArrayIndex[5],FACE_RIGHT,convertFaceCharToColor(state[1][1]));
  GLCubeSetFaceColor(rubik->cubeArrayIndex[1],FACE_TOP,convertFaceCharToColor(state[2][0]));
  GLCubeSetFaceColor(rubik->cubeArrayIndex[1],FACE_BACK,convertFaceCharToColor(state[2][1]));
  GLCubeSetFaceColor(rubik->cubeArrayIndex[3],FACE_TOP,convertFaceCharToColor(state[3][0]));
  GLCubeSetFaceColor(rubik->cubeArrayIndex[3],FACE_LEFT,convertFaceCharToColor(state[3][1]));
  GLCubeSetFaceColor(rubik->cubeArrayIndex[25],FACE_BOTTOM,convertFaceCharToColor(state[4][0]));
  GLCubeSetFaceColor(rubik->cubeArrayIndex[25],FACE_FRONT,convertFaceCharToColor(state[4][1]));
  GLCubeSetFaceColor(rubik->cubeArrayIndex[23],FACE_BOTTOM,convertFaceCharToColor(state[5][0]));
  GLCubeSetFaceColor(rubik->cubeArrayIndex[23],FACE_RIGHT,convertFaceCharToColor(state[5][1]));
  GLCubeSetFaceColor(rubik->cubeArrayIndex[19],FACE_BOTTOM,convertFaceCharToColor(state[6][0]));
  GLCubeSetFaceColor(rubik->cubeArrayIndex[19],FACE_BACK,convertFaceCharToColor(state[6][1]));
  GLCubeSetFaceColor(rubik->cubeArrayIndex[21],FACE_BOTTOM,convertFaceCharToColor(state[7][0]));
  GLCubeSetFaceColor(rubik->cubeArrayIndex[21],FACE_LEFT,convertFaceCharToColor(state[7][1]));
  GLCubeSetFaceColor(rubik->cubeArrayIndex[17],FACE_FRONT,convertFaceCharToColor(state[8][0]));
  GLCubeSetFaceColor(rubik->cubeArrayIndex[17],FACE_RIGHT,convertFaceCharToColor(state[8][1]));
  GLCubeSetFaceColor(rubik->cubeArrayIndex[15],FACE_FRONT,convertFaceCharToColor(state[9][0]));
  GLCubeSetFaceColor(rubik->cubeArrayIndex[15],FACE_LEFT,convertFaceCharToColor(state[9][1]));
  GLCubeSetFaceColor(rubik->cubeArrayIndex[11],FACE_BACK,convertFaceCharToColor(state[10][0]));
  GLCubeSetFaceColor(rubik->cubeArrayIndex[11],FACE_RIGHT,convertFaceCharToColor(state[10][1]));
  GLCubeSetFaceColor(rubik->cubeArrayIndex[9],FACE_BACK,convertFaceCharToColor(state[11][0]));
  GLCubeSetFaceColor(rubik->cubeArrayIndex[9],FACE_LEFT,convertFaceCharToColor(state[11][1]));
  GLCubeSetFaceColor(rubik->cubeArrayIndex[8],FACE_TOP,convertFaceCharToColor(state[12][0]));
  GLCubeSetFaceColor(rubik->cubeArrayIndex[8],FACE_FRONT,convertFaceCharToColor(state[12][1]));
  GLCubeSetFaceColor(rubik->cubeArrayIndex[8],FACE_RIGHT,convertFaceCharToColor(state[12][2]));
  GLCubeSetFaceColor(rubik->cubeArrayIndex[2],FACE_TOP,convertFaceCharToColor(state[13][0]));
  GLCubeSetFaceColor(rubik->cubeArrayIndex[2],FACE_RIGHT,convertFaceCharToColor(state[13][1]));
  GLCubeSetFaceColor(rubik->cubeArrayIndex[2],FACE_BACK,convertFaceCharToColor(state[13][2]));
  GLCubeSetFaceColor(rubik->cubeArrayIndex[0],FACE_TOP,convertFaceCharToColor(state[14][0]));
  GLCubeSetFaceColor(rubik->cubeArrayIndex[0],FACE_BACK,convertFaceCharToColor(state[14][1]));
  GLCubeSetFaceColor(rubik->cubeArrayIndex[0],FACE_LEFT,convertFaceCharToColor(state[14][2]));
  GLCubeSetFaceColor(rubik->cubeArrayIndex[6],FACE_TOP,convertFaceCharToColor(state[15][0]));
  GLCubeSetFaceColor(rubik->cubeArrayIndex[6],FACE_LEFT,convertFaceCharToColor(state[15][1]));
  GLCubeSetFaceColor(rubik->cubeArrayIndex[6],FACE_FRONT,convertFaceCharToColor(state[15][2]));
  GLCubeSetFaceColor(rubik->cubeArrayIndex[26],FACE_BOTTOM,convertFaceCharToColor(state[16][0]));
  GLCubeSetFaceColor(rubik->cubeArrayIndex[26],FACE_RIGHT,convertFaceCharToColor(state[16][1]));
  GLCubeSetFaceColor(rubik->cubeArrayIndex[26],FACE_FRONT,convertFaceCharToColor(state[16][2]));
  GLCubeSetFaceColor(rubik->cubeArrayIndex[24],FACE_BOTTOM,convertFaceCharToColor(state[17][0]));
  GLCubeSetFaceColor(rubik->cubeArrayIndex[24],FACE_FRONT,convertFaceCharToColor(state[17][1]));
  GLCubeSetFaceColor(rubik->cubeArrayIndex[24],FACE_LEFT,convertFaceCharToColor(state[17][2]));
  GLCubeSetFaceColor(rubik->cubeArrayIndex[18],FACE_BOTTOM,convertFaceCharToColor(state[18][0]));
  GLCubeSetFaceColor(rubik->cubeArrayIndex[18],FACE_LEFT,convertFaceCharToColor(state[18][1]));
  GLCubeSetFaceColor(rubik->cubeArrayIndex[18],FACE_BACK,convertFaceCharToColor(state[18][2]));
  GLCubeSetFaceColor(rubik->cubeArrayIndex[20],FACE_BOTTOM,convertFaceCharToColor(state[19][0]));
  GLCubeSetFaceColor(rubik->cubeArrayIndex[20],FACE_BACK,convertFaceCharToColor(state[19][1]));
  GLCubeSetFaceColor(rubik->cubeArrayIndex[20],FACE_RIGHT,convertFaceCharToColor(state[19][2]));
  glutPostRedisplay();
}



void generateState(Rubik* rubik,char state[20][4]) {
  state[0][0]=convertColorToFaceChar(GLCubeGetFaceColor(rubik->cubeArrayIndex[7],FACE_TOP));
  state[0][1]=convertColorToFaceChar(GLCubeGetFaceColor(rubik->cubeArrayIndex[7],FACE_FRONT));
  state[0][2]='\0';
  state[1][0]=convertColorToFaceChar(GLCubeGetFaceColor(rubik->cubeArrayIndex[5],FACE_TOP));
  state[1][1]=convertColorToFaceChar(GLCubeGetFaceColor(rubik->cubeArrayIndex[5],FACE_RIGHT));
  state[1][2]='\0';
  state[2][0]=convertColorToFaceChar(GLCubeGetFaceColor(rubik->cubeArrayIndex[1],FACE_TOP));
  state[2][1]=convertColorToFaceChar(GLCubeGetFaceColor(rubik->cubeArrayIndex[1],FACE_BACK));
  state[2][2]='\0';
  state[3][0]=convertColorToFaceChar(GLCubeGetFaceColor(rubik->cubeArrayIndex[3],FACE_TOP));
  state[3][1]=convertColorToFaceChar(GLCubeGetFaceColor(rubik->cubeArrayIndex[3],FACE_LEFT));
  state[3][2]='\0';
  state[4][0]=convertColorToFaceChar(GLCubeGetFaceColor(rubik->cubeArrayIndex[25],FACE_BOTTOM));
  state[4][1]=convertColorToFaceChar(GLCubeGetFaceColor(rubik->cubeArrayIndex[25],FACE_FRONT));
  state[4][2]='\0';
  state[5][0]=convertColorToFaceChar(GLCubeGetFaceColor(rubik->cubeArrayIndex[23],FACE_BOTTOM));
  state[5][1]=convertColorToFaceChar(GLCubeGetFaceColor(rubik->cubeArrayIndex[23],FACE_RIGHT));
  state[5][2]='\0';
  state[6][0]=convertColorToFaceChar(GLCubeGetFaceColor(rubik->cubeArrayIndex[19],FACE_BOTTOM));
  state[6][1]=convertColorToFaceChar(GLCubeGetFaceColor(rubik->cubeArrayIndex[19],FACE_BACK));
  state[6][2]='\0';
  state[7][0]=convertColorToFaceChar(GLCubeGetFaceColor(rubik->cubeArrayIndex[21],FACE_BOTTOM));
  state[7][1]=convertColorToFaceChar(GLCubeGetFaceColor(rubik->cubeArrayIndex[21],FACE_LEFT));
  state[7][2]='\0';
  state[8][0]=convertColorToFaceChar(GLCubeGetFaceColor(rubik->cubeArrayIndex[17],FACE_FRONT));
  state[8][1]=convertColorToFaceChar(GLCubeGetFaceColor(rubik->cubeArrayIndex[17],FACE_RIGHT));
  state[8][2]='\0';
  state[9][0]=convertColorToFaceChar(GLCubeGetFaceColor(rubik->cubeArrayIndex[15],FACE_FRONT));
  state[9][1]=convertColorToFaceChar(GLCubeGetFaceColor(rubik->cubeArrayIndex[15],FACE_LEFT));
  state[9][2]='\0';
  state[10][0]=convertColorToFaceChar(GLCubeGetFaceColor(rubik->cubeArrayIndex[11],FACE_BACK));
  state[10][1]=convertColorToFaceChar(GLCubeGetFaceColor(rubik->cubeArrayIndex[11],FACE_RIGHT));
  state[10][2]='\0';
  state[11][0]=convertColorToFaceChar(GLCubeGetFaceColor(rubik->cubeArrayIndex[9],FACE_BACK));
  state[11][1]=convertColorToFaceChar(GLCubeGetFaceColor(rubik->cubeArrayIndex[9],FACE_LEFT));
  state[11][2]='\0';
  state[12][0]=convertColorToFaceChar(GLCubeGetFaceColor(rubik->cubeArrayIndex[8],FACE_TOP));
  state[12][1]=convertColorToFaceChar(GLCubeGetFaceColor(rubik->cubeArrayIndex[8],FACE_FRONT));
  state[12][2]=convertColorToFaceChar(GLCubeGetFaceColor(rubik->cubeArrayIndex[8],FACE_RIGHT));
  state[12][3]='\0';
  state[13][0]=convertColorToFaceChar(GLCubeGetFaceColor(rubik->cubeArrayIndex[2],FACE_TOP));
  state[13][1]=convertColorToFaceChar(GLCubeGetFaceColor(rubik->cubeArrayIndex[2],FACE_RIGHT));
  state[13][2]=convertColorToFaceChar(GLCubeGetFaceColor(rubik->cubeArrayIndex[2],FACE_BACK));
  state[13][3]='\0';
  state[14][0]=convertColorToFaceChar(GLCubeGetFaceColor(rubik->cubeArrayIndex[0],FACE_TOP));
  state[14][1]=convertColorToFaceChar(GLCubeGetFaceColor(rubik->cubeArrayIndex[0],FACE_BACK));
  state[14][2]=convertColorToFaceChar(GLCubeGetFaceColor(rubik->cubeArrayIndex[0],FACE_LEFT));
  state[14][3]='\0';
  state[15][0]=convertColorToFaceChar(GLCubeGetFaceColor(rubik->cubeArrayIndex[6],FACE_TOP));
  state[15][1]=convertColorToFaceChar(GLCubeGetFaceColor(rubik->cubeArrayIndex[6],FACE_LEFT));
  state[15][2]=convertColorToFaceChar(GLCubeGetFaceColor(rubik->cubeArrayIndex[6],FACE_FRONT));
  state[15][3]='\0';
  state[16][0]=convertColorToFaceChar(GLCubeGetFaceColor(rubik->cubeArrayIndex[26],FACE_BOTTOM));
  state[16][1]=convertColorToFaceChar(GLCubeGetFaceColor(rubik->cubeArrayIndex[26],FACE_RIGHT));
  state[16][2]=convertColorToFaceChar(GLCubeGetFaceColor(rubik->cubeArrayIndex[26],FACE_FRONT));
  state[16][3]='\0';
  state[17][0]=convertColorToFaceChar(GLCubeGetFaceColor(rubik->cubeArrayIndex[24],FACE_BOTTOM));
  state[17][1]=convertColorToFaceChar(GLCubeGetFaceColor(rubik->cubeArrayIndex[24],FACE_FRONT));
  state[17][2]=convertColorToFaceChar(GLCubeGetFaceColor(rubik->cubeArrayIndex[24],FACE_LEFT));
  state[17][3]='\0';
  state[18][0]=convertColorToFaceChar(GLCubeGetFaceColor(rubik->cubeArrayIndex[18],FACE_BOTTOM));
  state[18][1]=convertColorToFaceChar(GLCubeGetFaceColor(rubik->cubeArrayIndex[18],FACE_LEFT));
  state[18][2]=convertColorToFaceChar(GLCubeGetFaceColor(rubik->cubeArrayIndex[18],FACE_BACK));
  state[18][3]='\0';
  state[19][0]=convertColorToFaceChar(GLCubeGetFaceColor(rubik->cubeArrayIndex[20],FACE_BOTTOM));
  state[19][1]=convertColorToFaceChar(GLCubeGetFaceColor(rubik->cubeArrayIndex[20],FACE_BACK));
  state[19][2]=convertColorToFaceChar(GLCubeGetFaceColor(rubik->cubeArrayIndex[20],FACE_RIGHT));
  state[19][3]='\0';
}
