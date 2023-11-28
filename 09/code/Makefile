FLAGS = 
LIBS = -lfreetype -lassimp -lGL -lGLU -lglut -lGLEW -lX11 -lXxf86vm -lXrandr -lpthread -lXi

main = main.cpp
geom = ./geometria.cpp
geomh = ./geometria.h
vaoh = ./Gestione_VAO.h
vao = ./GestioneVAO.cpp
int = ./GestioneInterazioni.cpp
inth = ./GestioneInterazioni.h
tel = ./GestioneTelecamera.cpp
telh = ./GestioneTelecamera.h
text = ./GestioneTesto.cpp
texth = ./GestioneTesto.h
init = ./inizializzazioni.cpp
inith = ./inizializzazioni.h
structh = ./Strutture.h
initms = ./inizializzazioni_meshOBJ.cpp
lms = ./load_meshes_assimp.cpp
lmsh = ./load_meshes_assimp.hpp

enumh = ./enum.h
enumi.h = ./enum_illuminazione.h
mbh = ./Materiali_Base.h

all: main.exe

main.exe: main.o ShaderMaker.o GestioneInterazioni.o GestioneTesto.o Lib.h geom.o gvao.o gtel.o init.o lms.o 
	g++ ${FLAGS} -o main.exe main.o ShaderMaker.o GestioneInterazioni.o GestioneTesto.o Lib.h geom.o gvao.o gtel.o lms.o init.o ${LIBS}

main.o: ${main} ${texth} Lib.h
	gcc -c ${FLAGS} ${main}

lms.o: ${lms} ${lmsh} ${structh}
	gcc -c ${FLAGS} ${lms} -o lms.o

ShaderMaker.o: ShaderMaker.cpp  ShaderMaker.h Lib.h
	gcc -c ${FLAGS} ShaderMaker.cpp -o ShaderMaker.o

geom.o: ${geom} Lib.h ${structh} ${geomh}
	gcc -c ${FLAGS} ${geom} -o geom.o

GestioneInterazioni.o: ${int} ${inth} Lib.h ${geomh} ${vaoh} ${telh} enum.h
	gcc -c ${FLAGS} ${int} -o GestioneInterazioni.o

gtel.o: ${tel} Lib.h ${structh} ${telh}
	gcc -c ${FLAGS} ${tel} -o gtel.o

gvao.o: ${vao} Lib.h ${structh} ${vaoh}
	gcc -c ${FLAGS} ${vao} -o gvao.o

init.o: ${init} Lib.h ${structh} ${geomh} ShaderMaker.h ${vaoh}
	gcc -c ${FLAGS} ${init} -o init.o

GestioneTesto.o: ${text} ${texth} Lib.h Strutture.h
	gcc -c ${FLAGS} ${text} -o GestioneTesto.o

.PHONY:	clean

clean:
	-rm -f *.o *.exe
