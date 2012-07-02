#include <GL/gl.h>
#include "global_config.h"
#include "GLCube.h"
#include "Matrix.h"
#ifndef _ROTATION_H
#define _ROTATION_H
typedef struct
{
  GLboolean rotating;
  GLsizei times; //旋转次数
  GLsizei len; //数组长度
  GLCube* cubeArray[9]; //旋转Cube数组
  Matrix* m;//旋转矩阵
} Rotation;
#endif
int rotate(Rotation*);
void fixRotation(Rotation*); //修正浮点误差
