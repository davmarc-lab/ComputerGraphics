FLAGS =
LIBS = -lglfw -lGL -lGLEW -lX11 -lXrandr -lpthread -lXi

all: main.exe

main.exe: main.o utils.o window.o
	g++ ${FLAGS} -o main.exe main.o utils.o window.o ${LIBS}

main.o: main.cpp
	gcc ${FLAGS} -c main.cpp -o main.o

utils.o: Utils.cpp Utils.hpp
	gcc ${FLAGS} -c Utils.cpp -o utils.o

window.o: Window.cpp Window.hpp
	gcc ${FLAGS} -c Window.cpp -o window.o

.PHONY:	clean

clean:
	-rm -f *.o *.exe
