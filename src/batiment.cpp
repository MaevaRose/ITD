#include <iostream>
#include <string>
#include "../include/batiment.h"



using namespace std;

Batiment::Batiment (int prct, int port, int prix, int lvl, int x_pos, int y_pos) : pourcent(prct), portee(port), cout(prix), level(lvl), x_position(x_pos), y_position(y_pos) {};
Radar::Radar () : Batiment(25, 100, 70, 1, -1, -1) {};
UsineArmement::UsineArmement () : Batiment(25, 100, 70, 1, -1, -1) {};
StockMunition::StockMunition () : Batiment(25, 100, 70, 1, -1, -1) {};




void Batiment::poser(int x, int y, Carte &carte) {
	bool isConstructible = carte.isConstructible(x, y, 1800, 1012);
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


void Radar::drawRadar() {
	float x = (-1 + 2 * this -> x_position / 1800.)*15;
	float y = -(-1 + 2 * this -> y_position/ 1012.)*8.4;

	glPushMatrix();
		glTranslatef(x, y, 0);
            glColor3ub(28,49,127);
            drawCircle(30, 1);
    glPopMatrix();
}


void UsineArmement::drawUsineArmement() {
	float x = (-1 + 2 * this -> x_position / 1800.)*15;
	float y = -(-1 + 2 * this -> y_position/ 1012.)*8.4;

	glPushMatrix();
		glTranslatef(x, y, 0);
            glColor3ub(35,67,127);
            drawCircle(30, 1);
    glPopMatrix();
}


void StockMunition::drawStockMunition() {
	float x = (-1 + 2 * this -> x_position / 1800.)*15;
	float y = -(-1 + 2 * this -> y_position/ 1012.)*8.4;

	glPushMatrix();
		glTranslatef(x, y, 0);
            glColor3ub(28,49,54);
            drawCircle(30, 1);
    glPopMatrix();
}





// Tableaux de batiments 

void addToTabRadar(vector<Radar> &tabRadar, Radar radar) {
	tabRadar.push_back(radar);
}


void addToTabUsine(vector<UsineArmement> &tabUsineArmement, UsineArmement usine) {
	tabUsineArmement.push_back(usine);
}


void addToTabStock(vector<StockMunition> &tabStockMunition, StockMunition stock) {
	tabStockMunition.push_back(stock);
}


void drawAllBatiments(vector<Radar> &tabRadar, vector<UsineArmement> &tabUsineArmement, vector<StockMunition> &tabStockMunition) {
	int size1 = tabRadar.size();
	Radar radar1;
	for (int i=0; i<size1; i++) {
		radar1 = tabRadar[i];
		radar1.drawRadar();
	}

	int size2 = tabUsineArmement.size();
	UsineArmement usineArmement1;
	for (int i=0; i<size2; i++) {
		usineArmement1 = tabUsineArmement[i];
		usineArmement1.drawUsineArmement();
	}

	int size3 = tabStockMunition.size();
	StockMunition stockMunition1;
	for (int i=0; i<size3; i++) {
		stockMunition1 = tabStockMunition[i];
		stockMunition1.drawStockMunition();
	}
}
