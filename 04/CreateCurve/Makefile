FLAGS = 
LIBS = -lGL -lGLU -lglut -lGLEW -lX11 -lXxf86vm -lXrandr -lpthread -lXi


ShaderMaker.o: ShaderMaker.cpp ShaderMaker.h lib.h
	gcc -c ${FLAGS} ShaderMaker.cpp

draw: draw.o ShaderMaker.o
	g++ ${FLAGS} -o draw.exe draw.o ShaderMaker.o ${LIBS}

draw.o: draw.cpp
	gcc -c ${FLAGS} draw.cpp

main: main.o ShaderMaker.o
	g++ ${FLAGS} -o main.exe main.o ShaderMaker.o ${LIBS}

main.o: main.cpp
	gcc -c ${FLAGS} main.cpp

.PHONY:	clean

clean:
	-rm -f *.o *.exe