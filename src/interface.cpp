#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string>
#include "../include/interface.hpp"
#include "../include/foncOpenGL.h"

Interface::Interface(){};


bool Interface::clicOnInterface(int x, int y){

	printf("suis je sur l'interface ?\n");
	if(y>=850 && y<=950 && x>=400 && x<=1200){
		clicOnMenuBas(x);
		return true;
	}
	return false;
}

void Interface::clicOnMenuBas(int x){
	printf("Je suis dans le menu bas\n");
	if(x>=400 && x<=500){
		this->select = 1;
	}
	if(x>500 && x<=600){
		this->select = 2;
	}
	if(x>600 && x<=700){
		this->select = 3;
	}
	if(x>700 && x<=800){
		this->select = 4;
	}
	if(x>800 && x<=900){
		this->select = 5;
	}
	if(x>900 && x<=1000){
		this->select = 6;
	}
	if(x>1000 && x<=1100){
		this->select = 7;
	}
}

void Interface::setAllTexture(){
	this->texMenuBas = setPNGTexture("./images/menubas.png");
}

void Interface::drawInterface() {
	drawMenuHaut();
	drawMenuBas();
}


void Interface::drawMenuHaut() {
	drawSquare(1700, 150, 3., 5., 1, 0, 0, 255);
	//convertir un int en string
	//sprintf(machaine,"%d",interface->lvl);
	glColor3ub(0,0,0);
	writeString(14, 7,  "Tour :");
	//printf("echo loul\n");
}


void Interface::drawMenuBas() {
	//drawSquare(900, 950, 10., 2., 1, 0, 0, 255);
	//float x = (-1 + 2. * 800. / 1800.)*15.;
	//float y = -(-1 + 2. * 900. / 1012.)*8.4;
	//printf("%f %f\n", x, y);
	drawTexture(this->texMenuBas, 800, 900, 800, 100);
}

