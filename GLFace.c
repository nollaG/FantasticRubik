#include <GL/gl.h>
#include "global_config.h"
#include "GLFace.h"
#include "Vector.h"
#include <stdio.h>
//indes means the count of face
void GLFaceAddVertex(GLFace* face, GLsizei index,GLfloat vertexArray[],GLfloat colorArray[]) {
  vertexArray[index*18]=face->vertexArray[0]->x;
  vertexArray[index*18+1]=face->vertexArray[0]->y;
  vertexArray[index*18+2]=face->vertexArray[0]->z;
  vertexArray[index*18+3]=face->vertexArray[1]->x;
  vertexArray[index*18+4]=face->vertexArray[1]->y;
  vertexArray[index*18+5]=face->vertexArray[1]->z;
  vertexArray[index*18+6]=face->vertexArray[2]->x;
  vertexArray[index*18+7]=face->vertexArray[2]->y;
  vertexArray[index*18+8]=face->vertexArray[2]->z;
  vertexArray[index*18+9]=face->vertexArray[2]->x;
  vertexArray[index*18+10]=face->vertexArray[2]->y;
  vertexArray[index*18+11]=face->vertexArray[2]->z;
  vertexArray[index*18+12]=face->vertexArray[3]->x;
  vertexArray[index*18+13]=face->vertexArray[3]->y;
  vertexArray[index*18+14]=face->vertexArray[3]->z;
  vertexArray[index*18+15]=face->vertexArray[0]->x;
  vertexArray[index*18+16]=face->vertexArray[0]->y;
  vertexArray[index*18+17]=face->vertexArray[0]->z;

  colorArray[index*18]=face->faceColor->red;
  colorArray[index*18+1]=face->faceColor->green;
  colorArray[index*18+2]=face->faceColor->blue;
  colorArray[index*18+3]=face->faceColor->red;
  colorArray[index*18+4]=face->faceColor->green;
  colorArray[index*18+5]=face->faceColor->blue;
  colorArray[index*18+6]=face->faceColor->red;
  colorArray[index*18+7]=face->faceColor->green;
  colorArray[index*18+8]=face->faceColor->blue;
  colorArray[index*18+9]=face->faceColor->red;
  colorArray[index*18+10]=face->faceColor->green;
  colorArray[index*18+11]=face->faceColor->blue;
  colorArray[index*18+12]=face->faceColor->red;
  colorArray[index*18+13]=face->faceColor->green;
  colorArray[index*18+14]=face->faceColor->blue;
  colorArray[index*18+15]=face->faceColor->red;
  colorArray[index*18+16]=face->faceColor->green;
  colorArray[index*18+17]=face->faceColor->blue;
}
GLsizei convertVectorToIndex(Vector* v) {
  for (int i=0;i<6;++i)
    if (compareVector(v,&FACE_VECTOR[i]))
      return i;
  return FACE_UNKNOWN;
}
void convertIndexToVector(GLsizei face,Vector* v) {
  if (face==FACE_UNKNOWN)
    return;
  copyVector(&FACE_VECTOR[face],v);
}
