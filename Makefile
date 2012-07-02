CFLAGS = -ggdb -Wall
CC = clang
OBJ = GLCube.o GLFace.o Matrix.o Operate.o Rubik.o main.o Rotation.o GLVertex.o Vector.o
Rubik: ${OBJ}
	${CC} -o Rubik ${OBJ} -lglut -lGLU -lm
GLCube.o:GLCube.c global_config.h
	${CC} -c GLCube.c ${CFLAGS}
GLFace.o:GLFace.c global_config.h
	${CC} -c GLFace.c ${CFLAGS}
Matrix.o:Matrix.c global_config.h
	${CC} -c Matrix.c ${CFLAGS}
Operate.o:Operate.c global_config.h
	${CC} -c Operate.c ${CFLAGS}
Rubik.o:Rubik.c global_config.h
	${CC} -c Rubik.c ${CFLAGS}
main.o:main.c global_config.h
	${CC} -c main.c ${CFLAGS}
Rotation.o:Rotation.c global_config.h
	${CC} -c Rotation.c ${CFLAGS}
GLVertex.o:GLVertex.c global_config.h
	${CC} -c GLVertex.c ${CFLAGS}
Vector.o:Vector.c global_config.h
	${CC} -c Vector.c ${CFLAGS}
clean:
	rm ${OBJ} Rubik
.PHONY:clean
