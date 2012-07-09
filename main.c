#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>
#include <time.h>
#include <stdio.h>
#include "global_config.h"
#include "GLCube.h"
#include "GLFace.h"
#include "Rubik.h"
#include "GLVertex.h"
#include "Matrix.h"
#include "Rotation.h"
#include "Operate.h"
static Rubik rubik;
static GLfloat vertices[10000];
static GLfloat colors[10000];
void turnFace(Rubik*,GLsizei,GLsizei,GLsizei);
int cameraType=0;
int upOrDown=0;

float perspective=45.0f;
float AngleZX=45.0f;
float AngleYZ=45.0f;
float eye_direction=1.0f;

static GLsizei lastLeftClickX,lastLeftClickY;
static GLsizei lastRightX,lastRightY;
static GLsizei rightButtonDown;

static char rubikState[20][4];
static char solveResult[1000];
static int resultLen=0;
static int resultPointer=0;
static char currentState='\0';
static int currentTimes=0;
static int stepCounter=0;


int solveCube(char state[20][4],char result[1000]);
void render(int total,GLfloat vertexArray[],GLfloat colorArray[]);
void init(void);
void reshape(int w,int h);
void display(void);
void specialKeyListener(int key,int x,int y);
void keyBoardListener(unsigned char key,int x,int y);
void print(void);
void disorderRubik(Rubik*);
void render(int total,GLfloat vertexArray[],GLfloat colorArray[]) {
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_COLOR_ARRAY);
  glVertexPointer(3,GL_FLOAT,0,vertexArray);
  glColorPointer(3,GL_FLOAT,0,colorArray);
  glDrawArrays(GL_TRIANGLES,0,total);
  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_COLOR_ARRAY);
}
void init(void) {
  glClearColor(0.0f,0.0f,0.0f,0.0f);
  glShadeModel(GL_FLAT);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);
  glFrontFace(GL_CCW);
  glCullFace(GL_BACK);
  glEnable(GL_CULL_FACE);
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
  /*glPointSize(8);*/
  /*glLineWidth(5);*/
  /*glEnable(GL_POINT_SMOOTH);*/
  /*glEnable(GL_LINE_SMOOTH);*/
  /*glEnable(GL_POLYGON_SMOOTH);*/
  /*glHint(GL_POINT_SMOOTH,GL_NICEST);*/
  /*glHint(GL_LINE_SMOOTH,GL_NICEST);*/
  /*glHint(GL_POLYGON_SMOOTH,GL_NICEST);*/
  /*glEnable(GL_BLEND);*/
  /*glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);*/
  RubikInit(&rubik);
}

void reshape(int w,int h) {
  glViewport(0,0,w,h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
   /*glFrustum (-1.0, 1.0, 1.0, -1.0, 1.5, 50.0);*/
  gluPerspective(perspective,(float)w/(float)h,0.1f,100.0f);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void display(void) {
  int tmp;
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(EYE_DISTANCE*cos(AngleYZ/180*PI)*sin(AngleZX/180*PI),EYE_DISTANCE*sin(AngleYZ/180*PI),EYE_DISTANCE*cos(AngleYZ/180*PI)*cos(AngleZX/180*PI),0,0,0,0,eye_direction,0);
  tmp=RubikInitArray(&rubik,vertices,colors);
  glEnable(GL_MULTISAMPLE_ARB);
  render(tmp*6,vertices,colors);
  glDisable(GL_MULTISAMPLE_ARB);
  glutSwapBuffers();
}

void disorderRubik(Rubik* r) {
  srand(time(NULL));
  int n=rand()%1000+100;
  while (n) {
    int face=rand()%6;
    int direction=rand()%2;
    if (r->rotation.rotating==GL_FALSE) {
      turnFace(r,face,direction,ANIMATION_FALSE);
      n--;
    }
  }
  glutPostRedisplay();
}

void mouseClickListener(int button,int state,int x,int y) {
  if (state == GLUT_UP && button == GLUT_WHEEL_UP) {
    if (perspective>=10)
      perspective-=WHEEL_SENSITIVITY;
  }
  if (state == GLUT_UP && button == GLUT_WHEEL_DOWN) {
    if (perspective<=80)
      perspective+=WHEEL_SENSITIVITY;
  }
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  GLint viewport[4];
  glGetIntegerv(GL_VIEWPORT,viewport);
  gluPerspective(perspective,(float)viewport[2]/(float)viewport[3],0.1f,100.0f);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
    lastLeftClickX=x;
    lastLeftClickY=y;
  }
  if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
    if (!rubik.rotation.rotating)
      mouseTurn(&rubik,lastLeftClickX,lastLeftClickY,x,y);
  }
  if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
    rightButtonDown=GL_TRUE;
    lastRightY=y;
    lastRightX=x;
  }
  if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP) {
    rightButtonDown=GL_FALSE;
  }
  glutPostRedisplay();
}

void mouseMotionListener(int x,int y) {
  if (rightButtonDown) {
    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT,viewport);
    float tmpAngleYZ=AngleYZ+(GLfloat)(y-lastRightY)/(GLfloat)viewport[3]*360;
    float tmpAngleZX=AngleZX-eye_direction*(GLfloat)(x-lastRightX)/(GLfloat)viewport[3]*360;
    if (cos(tmpAngleYZ/180*PI)*cos(AngleYZ/180*PI)<0)
      eye_direction=-eye_direction;
    AngleYZ=tmpAngleYZ;
    AngleZX=tmpAngleZX;
    lastRightY=y;
    lastRightX=x;
  }
  glutPostRedisplay();
}

void solveRubik(Rubik* rubik) {
  generateState(rubik,rubikState);
  resultLen=solveCube(rubikState,solveResult);
  resultPointer=0;
  currentState='\0';
  currentTimes=0;
  printf("%s\n",solveResult);
  stepCounter=0;
}

void displaySolution() {
  if (resultPointer>=resultLen) {
    printf("TotalSteps=%d\n",stepCounter);
    return;
  }
  stepCounter++;
  currentState=solveResult[resultPointer];
  currentTimes=solveResult[resultPointer+1]-'0';
  resultPointer+=2;
  while (currentState==solveResult[resultPointer]) {
    currentTimes+=solveResult[resultPointer+1]-'0';
    resultPointer+=2;
  }
  currentTimes=currentTimes%4;
  int face=FACE_UNKNOWN;
  switch (currentState) {
    case 'U':
      face=FACE_TOP;
      break;
    case 'D':
      face=FACE_BOTTOM;
      break;
    case 'F':
      face=FACE_FRONT;
      break;
    case 'B':
      face=FACE_BACK;
      break;
    case 'L':
      face=FACE_LEFT;
      break;
    case 'R':
      face=FACE_RIGHT;
      break;
    default:break;
  }
  if (currentTimes==0 || face==FACE_UNKNOWN)
    return;
  if (currentTimes==1)
    turnFace(&rubik,face,TURN_CW,ANIMATION_TRUE);
  if (currentTimes==2)
    for (int i=0;i<2;++i)
      turnFace(&rubik,face,TURN_CW,ANIMATION_TRUE);
  if (currentTimes==3)
    turnFace(&rubik,face,TURN_CCW,ANIMATION_TRUE);
}


void specialKeyListener(int key,int x,int y) {
  switch (key)
  {
    case GLUT_KEY_F2:
      disorderRubik(&rubik);
      break;
    case GLUT_KEY_F3:
      solveRubik(&rubik);
      break;
    case GLUT_KEY_F4:
      displaySolution();
      break;
    case GLUT_KEY_LEFT:
      cameraType-=1;
      cameraType=(cameraType+4)%4;
      break;
    case GLUT_KEY_RIGHT:
      cameraType+=1;
      cameraType=(cameraType+4)%4;
      break;
    case GLUT_KEY_UP:
      upOrDown=0;
      break;
    case GLUT_KEY_DOWN:
      upOrDown=1;
      break;
    default:break;
  }
  glutPostRedisplay();
}

void keyBoardListener(unsigned char key,int x,int y) {
  if (rubik.rotation.rotating)
    return;
}
int main(int argc,char** argv) {
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB | GLUT_MULTISAMPLE);
   glutInitWindowSize (500, 500); 
   glutInitWindowPosition (100, 100);
   glutCreateWindow (argv[0]);
   init();
   glutDisplayFunc(display);
   glutIdleFunc(display);
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyBoardListener);
   glutMouseFunc(mouseClickListener);
   glutMotionFunc(mouseMotionListener);
   glutSpecialFunc(specialKeyListener);
   glutMainLoop();
   return 0;
}
