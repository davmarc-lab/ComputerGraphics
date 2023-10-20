FLAGS = 
LIBS = -Linclude/src/glad.o -lglfw -lGLU -lGL -lX11 -lXrandr -lpthread -lXi

glad = ./include/src/glad.o
gladh = ./include/glad/glad.h
win = ./Window/Window.cpp
winh = ./Window/Window.hpp
shape = ./Shape/Shape.cpp
shapeh = ./Shape/Shape.hpp
shader = ./Shader/ShaderReader.cpp
shaderh = ./Shader/ShaderReader.hpp
libh = Lib.hpp

all: main.exe

main.exe: main.o window.o shape.o
	g++ ${FLAGS} -o main.exe main.o window.o shape.o ${glad} ${LIBS}

main.o: main.cpp ${gladh} ${libh}
	gcc -c ${FLAGS} main.cpp -o main.o

window.o: ${win} ${winh} ${libh} ${gladh}
	gcc -c ${FLAGS} ${win} -o window.o

shape.o: ${shape} ${shapeh} ${libh} ${gladh}
	gcc -c ${FLAGS} ${shape} -o shape.o


.PHONY:	clean

clean:
	-rm -f *.o *.exe

