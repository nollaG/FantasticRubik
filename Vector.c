#include <GL/gl.h>
#include <math.h>
#include "Vector.h"
#include "global_config.h"
Vector FACE_VECTOR[6]={
  {0.0f,1.0f,0.0f},
  {0.0f,-1.0f,0.0f},
  {-1.0f,0.0f,0.0f},
  {1.0f,0.0f,0.0f},
  {0.0f,0.0f,1.0f},
  {0.0f,0.0f,-1.0f}
};
Vector ZERO_VECTOR={0.0f,0.0f,0.0f};
GLboolean compareVector(Vector* a,Vector* b) {
  return (fabs(a->x-b->x)<ACCURACY && fabs(a->y-b->y)<ACCURACY && fabs(a->z-b->z)<ACCURACY);
}

void copyVector(Vector* src,Vector* des) {
  des->x=src->x;
  des->y=src->y;
  des->z=src->z;
}

void vectorMulVector(Vector* src1,Vector* src2,Vector* des) {
  des->x=src1->y*(src2->z)-src1->z*(src2->y);
  des->y=src1->z*(src2->x)-src1->x *(src2->z);
  des->z=src1->x*(src2->y)-src1->y *(src2->x);
}
GLboolean parallelVector(Vector* v1,Vector* v2) {//同向平行
  Vector tmp;
  vectorMulVector(v1,v2,&tmp);
  /*return compareVector(&tmp,&ZERO_VECTOR);*/
  return compareVector(&tmp,&ZERO_VECTOR) && (v1->x*v2->x+v1->y*v2->y+v1->z*v2->z>=0);
}
