FLAGS = 
LIBS = -lglfw -lGLU -lGL -lX11 -lXrandr -lpthread -lXi -ldl

glad = ./include/src/glad.c
gladh = ./include/glad/glad.h
win = ./Window/Window.cpp
winh = ./Window/Window.hpp
rect = ./Shape/Rect.cpp
recth = ./Shape/Rect.hpp
shape = ./Shape/Shape.cpp
shapeh = ./Shape/Shape.hpp
scene = ./Scene/Scene.cpp
sceneh = ./Scene/Scene.hpp
shader = ./Shader/Shader.cpp
shaderh = ./Shader/Shader.hpp
libh = Lib.hpp

all: main.exe

main.exe: main.o window.o shape.o shader.o scene.o rect.o glad.o
	g++ ${FLAGS} -o main.exe main.o window.o rect.o shape.o glad.o shader.o scene.o ${LIBS}

main.o: main.cpp ${gladh} ${libh}
	gcc -c ${FLAGS} main.cpp -o main.o

window.o: ${win} ${winh} ${libh} ${gladh}
	gcc -c ${FLAGS} ${win} -o window.o

shape.o: ${shape} ${shapeh} ${libh} ${gladh}
	gcc -c ${FLAGS} ${shape} -o shape.o

shader.o: ${shader} ${shaderh} ${shapeh} ${gladh}
	gcc -c ${FLAGS} ${shader} -o shader.o

scene.o: ${scene} ${sceneh} ${libh} ${gladh}
	gcc -c ${FLAGS} ${scene} -o scene.o

rect.o: ${rect} ${recth} ${libh} ${gladh}
	gcc -c ${FLAGS} ${rect} -o rect.o

glad.o: ${glad} ${gladh}
	gcc -c ${FLAGS} ${glad} -o glad.o

.PHONY:	clean

clean:
	-rm -f *.o *.exe

