#include <iostream>
#include <string>
#include "monstre.h"

using namespace std;

Monstre::Monstre(int pv, int vit, int x_pos, int y_pos) : pts_vie(pv), vitesse(vit), x_position(x_pos), y_position(y_pos) {};
PetitMonstre::PetitMonstre() : Monstre(100, 100, -1, -1) {};
MoyenMonstre::MoyenMonstre() : Monstre(150, 500, -1, -1) {};
GrosMonstre::GrosMonstre() : Monstre(250, 1000, -1, -1) {};




void Monstre::apparaitre(int x, int y) {
	this->x_position = x;
	this->y_position = y;
	//void addToListMonstre
}


void Monstre::tuerMonstre() {
	//void popOfListMonstre
}


void Monstre::afficherEtat() const {
     printf("Vie du monstre : %d\n", pts_vie);
}


void Monstre::recevoirDegat(int nbDegats) {
	pts_vie-=nbDegats;

	if(pts_vie<0) {
		pts_vie = 0; 
		tuerMonstre();
	}
}


bool Monstre::estVivant() const {
    return pts_vie > 0;
}


int Monstre::getPositionX() {
	return this -> x_position;
}


int Monstre::getPositionY() {
	return this -> y_position;
}


void Monstre::updatePosition(int x, int y) {
	this -> x_position = x;
	this -> y_position = y;
}