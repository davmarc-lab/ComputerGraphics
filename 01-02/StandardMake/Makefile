FLAGS = 
LIBS = -lGL -lGLU -lglut -lGLEW -lglfw3 -lX11 -lXxf86vm -lXrandr -lpthread -lXi
# questo main utilizza -lglfw3, in lab si usa -lglu -lGLEW
all: main.exe

main.exe: main.o
	g++ ${FLAGS} -o main.exe main.o ${LIBS}

main.o: main.cpp
	gcc -c ${FLAGS} main.cpp

.PHONY:	clean

clean:
	-rm -f *.o *.exe