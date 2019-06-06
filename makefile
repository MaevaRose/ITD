CC     = g++
CFLAGS = -Wall -Wextra -O2 -Wno-unused-result -g
LDFLAGS	= -lSDL -lSDL_image -lGLU -lGL -lglut -lm
LIB    = -lm
OBJ    = main.o monstre.o tour.o carte.o foncOpenGL.o interface.o noeud.o chemin.o grapheNoeuds.o batiment.o
RM     = rm -f
BIN    = ./bin/itd
DIRNAME = $(shell basename $$PWD)
BACKUP  = $(shell date +`basename $$PWD`-%m.%d.%H.%M.zip)
STDNAME = $(DIRNAME).zip

all : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIB) -o $(BIN) $(LDFLAGS)
	@echo "--------------------------------------------------------------"
	@echo "            to execute type: $(BIN) "
	@echo "--------------------------------------------------------------"

foncOpenGL.o : src/foncOpenGL.cpp include/foncOpenGL.h
	@echo "compile foncOpenGL"
	$(CC) $(CFLAGS) -c $<  
	@echo "done..."

interface.o : src/interface.cpp include/interface.hpp
	@echo "compile interface"
	$(CC) $(CFLAGS) -c $<  
	@echo "done..."

monstre.o : src/monstre.cpp include/monstre.h
	@echo "compile monstre"
	$(CC) $(CFLAGS) -c $<  
	@echo "done..."

noeud.o : src/noeud.cpp include/noeud.h
	@echo "compile noeud"
	$(CC) $(CFLAGS) -c $<  
	@echo "done..."

chemin.o : src/chemin.cpp include/chemin.h
	@echo "compile chemin"
	$(CC) $(CFLAGS) -c $<  
	@echo "done..."

grapheNoeuds.o : src/grapheNoeuds.cpp include/grapheNoeuds.h
	@echo "compile grapheNoeuds"
	$(CC) $(CFLAGS) -c $<  
	@echo "done..."

tour.o : src/tour.cpp include/tour.h
	@echo "compile tour"
	$(CC) $(CFLAGS) -c $<  
	@echo "done..."

batiment.o : src/batiment.cpp include/batiment.h
	@echo "compile batiment"
	$(CC) $(CFLAGS) -c $<  
	@echo "done..."

carte.o : src/carte.cpp include/carte.h
	@echo "compile carte"
	$(CC) $(CFLAGS) -c $<  
	@echo "done..."



main.o : src/main.cpp monstre.o tour.o carte.o foncOpenGL.o interface.o noeud.o chemin.o grapheNoeuds.o
	@echo "compile main"
	$(CC) $(CFLAGS) -c $<  
	@echo "done..."

clean :	
	@echo "**************************"
	@echo "CLEAN"
	@echo "**************************"
	$(RM) *~ $(OBJ) $(BIN)    

bigclean :
	@echo "**************************"
	@echo "BIG CLEAN"
	@echo "**************************"
	find . -name '*~' -exec rm -fv {} \;
	$(RM) *~ $(OBJ) $(BIN)

zip : clean 
	@echo "**************************"
	@echo "ZIP"
	@echo "**************************"
	cd .. && zip -r $(BACKUP) $(DIRNAME)
