FLAGS = 
LIBS = -Linclude/src -lglad -lglfw -lGLU -lGL -lX11 -lXrandr -lpthread -lXi

glad = ./include/src/glad.c
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

main.o: main.cpp
	gcc -c ${FLAGS} main.cpp -o main.o

window.o: ${win} ${winh} ${libh}
	gcc -c ${FLAGS} ${win} -o window.o

shape.o: ${shape} ${shapeh} ${libh}
	gcc -c ${FLAGS} ${shape} -o shape.o


.PHONY:	clean

clean:
	-rm -f *.o *.exe
