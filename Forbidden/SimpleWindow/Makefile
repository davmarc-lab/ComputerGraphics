FLAGS = 
LIBS = -lglfw -lGL -lX11 -lXrandr -lpthread -lXi

all: main.exe

main.exe: main.o 
	g++ ${FLAGS} -o main.exe main.o ${LIBS}

main.o: Window.cpp
	gcc -c ${FLAGS} Window.cpp -o main.o

.PHONY:	clean

clean:
	-rm -f *.o *.exe
