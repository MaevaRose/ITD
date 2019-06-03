#include <iostream>
#include <string>
#include "../include/batiment.h"



using namespace std;

Batiment::Batiment (int prct, int port, int prix, int lvl, int x_pos, int y_pos) : pourcent(prct), portee(port), cout(prix), level(lvl), x_position(x_pos), y_position(y_pos) {};
Radar::Radar () : Batiment(25, 100, 70, 1, -1, -1) {};
UsineArmement::UsineArmement () : Batiment(25, 100, 70, 1, -1, -1) {};
StockMunition::StockMunition () : Batiment(25, 100, 70, 1, -1, -1) {};




void Batiment::poser(int x, int y, Carte &carte) {
	bool isConstructible = carte.isConstructible(x, y, 1800);
	if(isConstructible){
		this->x_position = x;
		this->y_position = y;
		this->cout = cout/2;
		//void addToListBatiment
	}
	else{
		//void fonction qui prévient que ce n'est pas contructible
	}
	
}


void Batiment::suprimer() {
	//void popOfListBatiment
}


void Batiment::ameliorer(int level) {
	level += 1;
	this->pourcent += 10;
}


void Batiment::afficherEtat() {
	//afficherHallo(this->portee);
	printf("Niveau : %d.\n", this->level);
}


int Batiment::getPortee() {
	return(this->portee);
}


int Batiment::getPositionX() {
	return this -> x_position;
}


int Batiment::getPositionY() {
	return this -> y_position;
}


void Radar::ajouterPortee(int pourcent, Tour &tour) {
	tour.augmenterPortee(pourcent);
}


void UsineArmement::ajouterPuissance(int pourcent, Tour &tour) {
	tour.augmenterPuissance(pourcent);
}


void StockMunition::ajouterCadence(int pourcent, Tour &tour) {
	tour.augmenterVitesse(pourcent);
}