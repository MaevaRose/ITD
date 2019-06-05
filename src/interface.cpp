#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <vector>
#include <string>
#include "../include/interface.hpp"
//#include "../include/foncOpenGL.h"


using namespace std;

Interface::Interface(){};


bool Interface::clicOnInterface(int x, int y){

	printf("suis je sur l'interface ?\n");
	if(y>=850 && y<=950 && x>=400 && x<=1200){
		this->x = x;
		this->y = y;
		clicOnMenuBas();
		return true;
	}
	if(x>= 1600 && x<= 1800 && y>=0 && y<= 300){
		this->x = x;
		this->y = y;
		clicOnMenuHaut();
	}
	return false;
}

void Interface::clicOnMenuBas(){
	printf("Je suis dans le menu bas\n");
	int x = this->x;
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

void Interface::clicOnMenuHaut(){

	printf("Je suis dans le menu haut\n");
	int x = this->x;
	int y = this->y;
	if(y>= 170 && y<= 230 && x>=1670 && x<= 1730){
		
	}

}

void Interface::setAllTexture(){
	this->texMenuBas = setPNGTexture("./images/menubas.png");
}

void Interface::drawInterface(vector<TourBleue> &tabTourBleue, vector<TourJaune> &tabTourJaune, vector<TourRouge> &tabTourRouge, vector<TourVerte> &tabTourVerte) {
	drawMenuHaut(tabTourBleue, tabTourJaune, tabTourRouge, tabTourVerte);
	drawMenuBas();
}


void Interface::drawMenuHaut(vector<TourBleue> &tabTourBleue, vector<TourJaune> &tabTourJaune, vector<TourRouge> &tabTourRouge, vector<TourVerte> &tabTourVerte) {
	drawSquare(1700, 150, 3., 5., 1, 0, 0, 255);

	drawSquare(1700, 200, 1., 1., 1, 255, 0, 0);
	//convertir un int en string
	//sprintf(machaine,"%d",interface->lvl);
	glColor3ub(0,0,0);
	writeString(13, 7,  "Tour :");
	//printf("echo loul\n");
	if(this->tour_select == 1){
        int x = tabTourBleue[indice_tour].getPositionX();
		char info[50];
		char texte[50] = "La tour est à la position : ";
		sprintf (info, "%d", x);
		strcat (texte, info);
		writeString(10, 6.9,  texte);

    }
    if(this->tour_select == 2){
    	int x = tabTourVerte[indice_tour].getPositionX();
		char info[50];
		char texte[50] = "La tour est à la position : ";
		sprintf (info, "%d", x);
		strcat (texte, info);
		writeString(10, 6.9,  texte);
    }
    if(this->tour_select == 3){
        int x = tabTourJaune[indice_tour].getPositionX();
		char info[50];
		char texte[50] = "La tour est à la position : ";
		sprintf (info, "%d", x);
		strcat (texte, info);
		writeString(10, 6.9,  texte);
   	}
    if(this->tour_select == 4){
       int x = tabTourRouge[indice_tour].getPositionX();
		char info[50];
		char texte[50] = "La tour est à la position : ";
		sprintf (info, "%d", x);
		strcat (texte, info);
		writeString(10, 6.9,  texte);
    }
}


void Interface::drawMenuBas() {
	//drawSquare(900, 950, 10., 2., 1, 0, 0, 255);
	//float x = (-1 + 2. * 800. / 1800.)*15.;
	//float y = -(-1 + 2. * 900. / 1012.)*8.4;
	//printf("%f %f\n", x, y);
	drawTexture(this->texMenuBas, 800, 900, 800, 100);
}

