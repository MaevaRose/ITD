#include <iostream>
#include <string>
#include "tour.h"


using namespace std;

Tour::Tour (int deg, int cad, int port, int prix, int lvl, int x_pos, int y_pos) : degats(deg), cadence(cad), portee(port), cout(prix), level(lvl), x_position(x_pos), y_position(y_pos) {};
TourBleue::TourBleue () : Tour(100, 100, 50, 10, 1, -1, -1) {};
TourRouge::TourRouge () : Tour(150, 500, 50, 20, 1, -1, -1) {};
TourJaune::TourJaune () : Tour(20, 1000, 20, 5, 1, -1, -1) {};
TourVerte::TourVerte () : Tour(50, 100, 25, 10, 1, -1, -1) {};




void Tour::poser(int x, int y, Carte &carte) {
	bool isConstructible = carte.isConstructible(x, y, 1800);
	if(isConstructible){
		this->x_position = x;
		this->y_position = y;
		this->cout = this->cout/2;
		//void addToListTour
	}
	else{
		//fonction qui prévient que pas constructible
	}
	
}


void Tour::supprimer() {
	//void popOfListTour
}


void Tour::ameliorer(int level) {
	level += 1;
	this->portee += 10;
	this->degats += 10;
	this->cadence -= 100;
}


void Tour::afficherEtat() {
	//afficherHallo(this->portee);
    printf("Niveau : %d.\nDégats : %d.\nCadence : %d.\n", level, degats, cadence);
}


void Tour::attaquer(Monstre &cible){
	cible.recevoirDegat(degats);
}


int Tour::getPortee() {
	return (this->portee);
}


int Tour::getPositionX() {
	return this -> x_position;
}


int Tour::getPositionY() {
	return this -> y_position;
}


void Tour::augmenterPuissance(int pourcent) {
	this->degats += this->degats*(pourcent/100);
}


void Tour::augmenterVitesse(int pourcent) {
	this->cadence += this->cadence*(pourcent/100);
}


void Tour::augmenterPortee(int pourcent) {
	this->portee += this->portee*(pourcent/100);
}


