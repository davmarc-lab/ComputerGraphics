FLAGS = 
LIBS = -lfreetype -lGL -lGLU -lglut -lGLEW -lX11 -lXxf86vm -lXrandr -lpthread -lXi

main = main.cpp
int = ./Gestione_Interazioni.cpp
inth = ./Gestione_Interazioni.h
text = ./GestioneTesto.cpp
texth = ./GestioneTesto.h

all: main.exe

main.exe: main.o ShaderMaker.o GestioneInterazioni.o GestioneTesto.o
	g++ ${FLAGS} -o main.exe main.o ShaderMaker.o GestioneTesto.o GestioneInterazioni.o ${LIBS}

main.o: main.cpp ${texth}
	gcc -c ${FLAGS} main.cpp

ShaderMaker.o: ShaderMaker.cpp  ShaderMaker.h Lib.h
	gcc -c ${FLAGS} ShaderMaker.cpp

GestioneInterazioni.o: ${int} ${inth} Lib.h
	gcc -c ${FLAGS} ${int} -o GestioneInterazioni.o

GestioneTesto.o: ${text} ${texth} Lib.h Strutture.h
	gcc -c ${FLAGS} ${text} -o GestioneTesto.o

.PHONY:	clean

clean:
	-rm -f *.o *.exe
