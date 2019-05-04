CC     = g++
CFLAGS = -Wall -Wextra -O2 -Wno-unused-result -g
LDFLAGS	= -lSDL -lSDL_image -lGLU -lGL -lm
LIB    = -lm
OBJ    = main.o monstre.o tour.o carte.o image.o sprites.o
RM     = rm -f
BIN    = ./testv1
DIRNAME = $(shell basename $$PWD)
BACKUP  = $(shell date +`basename $$PWD`-%m.%d.%H.%M.zip)
STDNAME = $(DIRNAME).zip

all : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIB) -o $(BIN) $(LDFLAGS)
	@echo "--------------------------------------------------------------"
	@echo "            to execute type: $(BIN) "
	@echo "--------------------------------------------------------------"

monstre.o : monstre.cpp monstre.h
	@echo "compile monstre"
	$(CC) $(CFLAGS) -c $<  
	@echo "done..."

tour.o : tour.cpp tour.h
	@echo "compile tour"
	$(CC) $(CFLAGS) -c $<  
	@echo "done..."

carte.o : carte.cpp carte.h
	@echo "compile carte"
	$(CC) $(CFLAGS) -c $<  
	@echo "done..."

image.o : image.cpp image.h
	@echo "compile image"
	$(CC) $(CFLAGS) -c $<  
	@echo "done..."

sprites.o : sprites.cpp sprites.h
	@echo "compile sprites"
	$(CC) $(CFLAGS) -c $<  
	@echo "done..."

main.o : main.cpp monstre.o tour.o carte.o image.o sprites.o
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
