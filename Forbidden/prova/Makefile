FLAGS = 
LIBS = -Linclude/src -lglad -lglfw -lGLU -lGL -lX11 -lXrandr -lpthread -lXi

win = ./Window/Window.cpp
winh = ./Window/Window.hpp

all: main.exe

main.exe: main.o
	g++ ${FLAGS} -o main.exe main.o ${LIBS}

main.o: main.cpp
	gcc -c ${FLAGS} main.cpp -o main.o

window: window.o
	g++ ${FLAGS} -o window window.o ${LIBS}

window.o: ${win} ${winh} ${libh}
	gcc -c ${FLAGS} ${win} -o window.o

.PHONY:	clean

clean:
	-rm -f *.o *.exe
