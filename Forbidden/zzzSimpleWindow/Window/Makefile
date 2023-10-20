FLAGS = 
LIBS = -lglfw -lGL -lX11 -lXrandr -lpthread -lXi

all: main.exe

main.exe: main.o window.o
	g++ ${FLAGS} -o main.exe main.o window.o ${LIBS}

main.o: mainWindow.cpp
	gcc -c ${FLAGS} mainWindow.cpp -o main.o

window.o: Window.hpp
	gcc -c ${FLAGS} Window.cpp -o window.o

.PHONY:	clean

clean:
	-rm -f *.o *.exe
