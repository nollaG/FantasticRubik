#include <GL/gl.h>
#include "global_config.h"
#include "Rotation.h"
#include "Matrix.h"
#include "Rubik.h"


//1代表需要继续旋转
//0代表旋转完毕
int rotate(Rotation* r) {
  for (GLsizei i=0;i<r->len;++i)
    for (GLsizei j=0;j<8;++j)
      mulVertex(r->m,&r->cubeArray[i]->vertexArray[j]);
  for (GLsizei i=0;i<r->len;++i)
    for (GLsizei j=0;j<6;++j)
      mulVector(r->m,&(r->cubeArray[i]->faceArray[j].normalVector));
  r->times--;
  if (r->times==0) {
    r->rotating=GL_FALSE;
    return 0;
  }
  else {
    return 1;
  }
}
void fixRotation(Rotation* r) {
  for (GLsizei i=0;i<r->len;++i)
    FixCube(r->cubeArray[i]);
  for (GLsizei i=0;i<r->len;++i)
    for (GLsizei j=0;j<6;++j) {
      r->cubeArray[i]->faceArray[j].faceIndex=convertVectorToIndex(&(r->cubeArray[i]->faceArray[j].normalVector));
      convertIndexToVector(r->cubeArray[i]->faceArray[j].faceIndex,&(r->cubeArray[i]->faceArray[j].normalVector));
    }

}

