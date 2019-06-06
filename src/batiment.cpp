#include <iostream>
#include <string>
#include "../include/batiment.h"



using namespace std;

Batiment::Batiment (int prct, int port, int prix, int lvl, int x_pos, int y_pos) : pourcent(prct), portee(port), cout(prix), level(lvl), x_position(x_pos), y_position(y_pos) {};
Radar::Radar () : Batiment(25, 130, 10, 1, -1, -1) {};
UsineArmement::UsineArmement () : Batiment(25, 130, 10, 1, -1, -1) {};
StockMunition::StockMunition () : Batiment(25, 130, 10, 1, -1, -1) {};






// void Batiment::poser(int x, int y, Carte &carte) {
// 	bool isConstructible = carte.isConstructible(x, y, 1800, 1012);
// 	if(isConstructible){
// 		this->x_position = x;
// 		this->y_position = y;
// 		this->cout = cout/2;
// 		//void addToListBatiment
// 	}
// 	else{
// 		//void fonction qui prévient que ce n'est pas contructible
// 	}
	
// }


void Batiment::suprimer() {
	//void popOfListBatiment
}


// void Batiment::ameliorer(int level) {
// 	level += 1;
// 	this->pourcent += 10;
// }


void Batiment::afficherEtat() {
	//afficherHallo(this->portee);
	printf("Niveau : %d.\n", this->level);
}

bool Batiment::aPortee(int x1, int y1){
	int x0 = this->x_position;
	int y0 = this->y_position;
	

	if(sqrt((x1-x0)*(x1-x0)+(y1-y0)*(y1-y0)) < this->portee){
		//printf("Il est à une distance de %f\n", sqrt((x1-x0)*(x1-x0)+(y1-y0)*(y1-y0)));
		//printf("La portée est de %f donc je peux faire effet\n", this->portee);
		return true;
	}

	return false;
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


// void Radar::ajouterPortee(int pourcent, Tour &tour) {
// 	tour.augmenterPortee(pourcent);
// }


// void UsineArmement::ajouterPuissance(int pourcent, Tour &tour) {
// 	tour.augmenterPuissance(pourcent);
// }


// void StockMunition::ajouterCadence(int pourcent, Tour &tour) {
// 	tour.augmenterVitesse(pourcent);
// }

void Radar::poser(int x, int y, Carte &carte, vector<Radar> &tabRadar){
	int width = 1800;
	bool isConstructible = carte.isConstructibleBatiment(x, y, 1800, 1012);
	if(isConstructible  && carte.argent>=this->cout){
		this->x_position = x;
		this->y_position = y;
		carte.argent -= this->cout;

		for(int i = y-30 ; i < y+30 ; i++){
			for(int j = x-30; j < x+30 ; j++){
				int position = width*3*(i-1)+j*3;
				carte.data[position+1]=0;
				carte.data[position+2]=200;
			}
		}

		addToTabRadar(tabRadar, *this);
	}	
}

void UsineArmement::poser(int x, int y, Carte &carte, vector<UsineArmement> &tabUsineArmement){
	int width = 1800;
	bool isConstructible = carte.isConstructibleBatiment(x, y, 1800, 1012);
	if(isConstructible  && carte.argent>=this->cout){
		this->x_position = x;
		this->y_position = y;
		carte.argent -= this->cout;

		for(int i = y-30 ; i < y+30 ; i++){
			for(int j = x-30; j < x+30 ; j++){
				int position = width*3*(i-1)+j*3;
				carte.data[position+1]=0;
				carte.data[position+2]=200;
			}
		}

		addToTabUsine(tabUsineArmement, *this);
	}
}

void StockMunition::poser(int x, int y, Carte &carte, vector<StockMunition> &tabStockMunition){
	int width = 1800;
	bool isConstructible = carte.isConstructibleBatiment(x, y, 1800, 1012);
	if(isConstructible  && carte.argent>=this->cout){
		this->x_position = x;
		this->y_position = y;
		carte.argent -= this->cout;

		for(int i = y-30 ; i < y+30 ; i++){
			for(int j = x-30; j < x+30 ; j++){
				int position = width*3*(i-1)+j*3;
				carte.data[position+1]=0;
				carte.data[position+2]=200;
			}
		}

		addToTabStock(tabStockMunition, *this);
	}
}

void Radar::drawRadar() {
	float x = (-1 + 2 * this -> x_position / 1800.)*15;
	float y = -(-1 + 2 * this -> y_position/ 1012.)*8.4;

	float portee = (this->portee * 16.8) / 1012.;

	float size = (30 * 16.8) / 1012.;

	glPushMatrix();
		glTranslatef(x, y, 0);
            glColor3ub(150,49,127);
            drawCircle(size, 1);
            drawCircle(portee, 0);
    glPopMatrix();
}


void UsineArmement::drawUsineArmement() {
	float x = (-1 + 2 * this -> x_position / 1800.)*15;
	float y = -(-1 + 2 * this -> y_position/ 1012.)*8.4;

	float portee = (this->portee * 16.8) / 1012.;

	float size = (30 * 16.8) / 1012.;

	glPushMatrix();
		glTranslatef(x, y, 0);
            glColor3ub(35,67,127);
            drawCircle(size, 1);
            drawCircle(portee, 0);
    glPopMatrix();
}


void StockMunition::drawStockMunition() {
	float x = (-1 + 2 * this -> x_position / 1800.)*15;
	float y = -(-1 + 2 * this -> y_position/ 1012.)*8.4;

	float portee = (this->portee * 16.8) / 1012.;

	float size = (30 * 16.8) / 1012.;

	glPushMatrix();
		glTranslatef(x, y, 0);
            glColor3ub(28,49,54);
            drawCircle(size, 1);
            drawCircle(portee, 0);
    glPopMatrix();
}

void Radar::augmenterTour(vector<TourBleue> &tabTourBleue, vector<TourJaune> &tabTourJaune, vector<TourRouge> &tabTourRouge, vector<TourVerte> &tabTourVerte){
	if (tabTourBleue.size()>0) {
		for (int i=0; i<tabTourBleue.size(); i++) {
			if(aPortee(tabTourBleue[i].getPositionX(), tabTourBleue[i].getPositionY())){
				//printf("Tour bleue %d est à portée\n", i);
				tabTourBleue[i].augmenterPortee(10.);
			}
		}
	}
	if (tabTourJaune.size()>0) {
		for (int i=0; i<tabTourJaune.size(); i++) {
			if(aPortee(tabTourJaune[i].getPositionX(), tabTourJaune[i].getPositionY())){
				tabTourJaune[i].augmenterPortee(10);
			}		
		}
	}
	if (tabTourRouge.size()>0) {
		for (int i=0; i<tabTourRouge.size(); i++) {
			if(aPortee(tabTourRouge[i].getPositionX(), tabTourRouge[i].getPositionY())){
				tabTourRouge[i].augmenterPortee(10);
			}
		}
	}
	if (tabTourVerte.size()>0) {
		for (int i=0; i<tabTourVerte.size(); i++) {
			if(aPortee(tabTourVerte[i].getPositionX(), tabTourVerte[i].getPositionY())){
				tabTourVerte[i].augmenterPortee(10);
			}
		}
	}
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


void drawAllBatiments(vector<Radar> &tabRadar, vector<UsineArmement> &tabUsineArmement, vector<StockMunition> &tabStockMunition, int frameIndex) {
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


void augmenteAllTours(vector<Radar> &tabRadar, vector<UsineArmement> &tabUsineArmement, vector<StockMunition> &tabStockMunition, vector<TourBleue> &tabTourBleue, vector<TourJaune> &tabTourJaune, vector<TourRouge> &tabTourRouge, vector<TourVerte> &tabTourVerte) {
	if (tabRadar.size()>0) {
		for (int i=0; i<tabRadar.size(); i++) {
			tabRadar[i].augmenterTour(tabTourBleue, tabTourJaune, tabTourRouge, tabTourVerte);
		}
	}
	if (tabUsineArmement.size()>0) {
		for (int i=0; i<tabUsineArmement.size(); i++) {
			//tabTourJaune[i].attaquer(tabPetitMonstre, tabMoyenMonstre, tabGrosMonstre);
		}
	}
	if (tabStockMunition.size()>0) {
		for (int i=0; i<tabStockMunition.size(); i++) {
			//tabTourRouge[i].attaquer(tabPetitMonstre, tabMoyenMonstre, tabGrosMonstre);
		}
	}
}