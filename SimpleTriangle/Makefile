FLAGS = 
LIBS = -lGL -lGLU -lglut -lGLEW -lX11 -lXxf86vm -lXrandr -lpthread -lXi

all: TriangoloOpengl.exe

TriangoloOpengl.exe: TriangoloOpengl.o ShaderMaker.o
	g++ ${FLAGS} -o TriangoloOpengl.exe TriangoloOpengl.o ShaderMaker.o ${LIBS}

TriangoloOpengl.o: TriangoloOpengl.cpp
	gcc -c ${FLAGS} TriangoloOpengl.cpp

ShaderMaker.o: ShaderMaker.cpp ShaderMaker.h Lib.h
	gcc -c ${FLAGS} ShaderMaker.cpp

.PHONY:	clean

clean:
	-rm -f *.o *.exe