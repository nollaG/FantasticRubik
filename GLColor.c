#include "GLColor.h"
GLColor ColorBlack={0.0,0.0,0.0};
GLColor ColorWhite={1.0,1.0,1.0};
GLColor ColorRed={1.0,0.0,0.0};
GLColor ColorGreen={0.0,1.0,0.0};
GLColor ColorBlue={0.0,0.0,1.0};
GLColor ColorYellow={1.0,1.0,0.0};
GLColor ColorOrange={1.0,0.5,0.0};
char convertColorToFaceChar(GLColor* c) {
  if (c==&ColorWhite)
    return 'R';
  if (c==&ColorRed)
    return 'F';
  if (c==&ColorBlue)
    return 'D';
  if (c==&ColorGreen)
    return 'U';
  if (c==&ColorYellow)
    return 'L';
  if (c==&ColorOrange)
    return 'B';
  return 'N';
}
