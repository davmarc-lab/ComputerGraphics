FLAGS = 
LIBS = -lGL -lGLU -lglut -lGLEW -lX11 -lXxf86vm -lXrandr -lpthread -lXi

all: main.exe

main.exe: main.o ShaderMaker.o
	g++ ${FLAGS} -o main.exe main.o ShaderMaker.o ${LIBS}

main.o: main.cpp
	gcc -c ${FLAGS} main.cpp

ShaderMaker.o: ShaderMaker.cpp ShaderMaker.h Lib.h
	gcc -c ${FLAGS} ShaderMaker.cpp

GestioneTesto.o: GestioneTesto.cpp GestioneTesto.h Lib.h
	gcc -c ${FLAGS} GestioneTesto.cpp

.PHONY:	clean

clean:
	-rm -f *.o *.exe