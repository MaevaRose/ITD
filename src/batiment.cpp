#include <iostream>
#include <string>
#include <vector>
#include "../include/batiment.h"



using namespace std;

Batiment::Batiment (int prct, int port, int prix, int lvl, int x_pos, int y_pos) : pourcent(prct), portee(port), cout(prix), level(lvl), x_position(x_pos), y_position(y_pos) {};
Radar::Radar () : Batiment(25, 130, 10, 1, -1, -1) {};
UsineArmement::UsineArmement () : Batiment(25, 130, 10, 1, -1, -1) {};
StockMunition::StockMunition () : Batiment(25, 130, 10, 1, -1, -1) {};








void Batiment::ameliorer(Carte &carte) {
	if(this->level<5 && this->cout/2<=carte.argent){
		this->level += 1;
		this->pourcent += 10;
		carte.argent -= this->cout/2;
	}

}


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
				carte.data[position+2]=220;
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
				carte.data[position+2]=240;
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
				tabTourJaune[i].augmenterPortee(10.);
			}		
		}
	}
	if (tabTourRouge.size()>0) {
		for (int i=0; i<tabTourRouge.size(); i++) {
			if(aPortee(tabTourRouge[i].getPositionX(), tabTourRouge[i].getPositionY())){
				tabTourRouge[i].augmenterPortee(10.);
			}
		}
	}
	if (tabTourVerte.size()>0) {
		for (int i=0; i<tabTourVerte.size(); i++) {
			if(aPortee(tabTourVerte[i].getPositionX(), tabTourVerte[i].getPositionY())){
				tabTourVerte[i].augmenterPortee(10.);
			}
		}
	}
}

void UsineArmement::augmenterTour(vector<TourBleue> &tabTourBleue, vector<TourJaune> &tabTourJaune, vector<TourRouge> &tabTourRouge, vector<TourVerte> &tabTourVerte){
	if (tabTourBleue.size()>0) {
		for (int i=0; i<tabTourBleue.size(); i++) {
			if(aPortee(tabTourBleue[i].getPositionX(), tabTourBleue[i].getPositionY())){
				//printf("Tour bleue %d est à portée\n", i);
				tabTourBleue[i].augmenterPuissance(10);
			}
		}
	}
	if (tabTourJaune.size()>0) {
		for (int i=0; i<tabTourJaune.size(); i++) {
			if(aPortee(tabTourJaune[i].getPositionX(), tabTourJaune[i].getPositionY())){
				tabTourJaune[i].augmenterPuissance(10);
			}		
		}
	}
	if (tabTourRouge.size()>0) {
		for (int i=0; i<tabTourRouge.size(); i++) {
			if(aPortee(tabTourRouge[i].getPositionX(), tabTourRouge[i].getPositionY())){
				tabTourRouge[i].augmenterPuissance(10);
			}
		}
	}
	if (tabTourVerte.size()>0) {
		for (int i=0; i<tabTourVerte.size(); i++) {
			if(aPortee(tabTourVerte[i].getPositionX(), tabTourVerte[i].getPositionY())){
				tabTourVerte[i].augmenterPuissance(10);
			}
		}
	}
}


void StockMunition::augmenterTour(vector<TourBleue> &tabTourBleue, vector<TourJaune> &tabTourJaune, vector<TourRouge> &tabTourRouge, vector<TourVerte> &tabTourVerte){
	if (tabTourBleue.size()>0) {
		for (int i=0; i<tabTourBleue.size(); i++) {
			if(aPortee(tabTourBleue[i].getPositionX(), tabTourBleue[i].getPositionY())){
				//printf("Tour bleue %d est à portée\n", i);
				tabTourBleue[i].augmenterVitesse(10);
			}
		}
	}
	if (tabTourJaune.size()>0) {
		for (int i=0; i<tabTourJaune.size(); i++) {
			if(aPortee(tabTourJaune[i].getPositionX(), tabTourJaune[i].getPositionY())){
				tabTourJaune[i].augmenterVitesse(10);
			}		
		}
	}
	if (tabTourRouge.size()>0) {
		for (int i=0; i<tabTourRouge.size(); i++) {
			if(aPortee(tabTourRouge[i].getPositionX(), tabTourRouge[i].getPositionY())){
				tabTourRouge[i].augmenterVitesse(10);
			}
		}
	}
	if (tabTourVerte.size()>0) {
		for (int i=0; i<tabTourVerte.size(); i++) {
			if(aPortee(tabTourVerte[i].getPositionX(), tabTourVerte[i].getPositionY())){
				tabTourVerte[i].augmenterVitesse(10);
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
			tabUsineArmement[i].augmenterTour(tabTourBleue, tabTourJaune, tabTourRouge, tabTourVerte);
		}
	}
	if (tabStockMunition.size()>0) {
		for (int i=0; i<tabStockMunition.size(); i++) {
			tabStockMunition[i].augmenterTour(tabTourBleue, tabTourJaune, tabTourRouge, tabTourVerte);
		}
	}
}

int getRadar(int x, int y, vector<Radar> &tabRadar){
	if (tabRadar.size()>0) {
		for (int i=0; i<tabRadar.size(); i++) {
			int radar_x = tabRadar[i].getPositionX();
			int radar_y = tabRadar[i].getPositionY();
			if(radar_y > y-30 && radar_y < y+30 && radar_x > x-30 && radar_x < x+30) {
				return i;
			}
		}
	}
}

int getUsineArmement(int x, int y, vector<UsineArmement> &tabUsineArmement){
	if (tabUsineArmement.size()>0) {
		for (int i=0; i<tabUsineArmement.size(); i++) {
			int uarmement_x = tabUsineArmement[i].getPositionX();
			int uarmement_y = tabUsineArmement[i].getPositionY();
			if(uarmement_y > y-30 && uarmement_y < y+30 && uarmement_x > x-30 && uarmement_x < x+30) {
				return i;
			}
		}
	}
}

int getStockMunition(int x, int y, vector<StockMunition> &tabStockMunition){
	if (tabStockMunition.size()>0) {
		for (int i=0; i<tabStockMunition.size(); i++) {
			int stomuni_x = tabStockMunition[i].getPositionX();
			int stomuni_y = tabStockMunition[i].getPositionY();
			if(stomuni_y > y-30 && stomuni_y < y+30 && stomuni_x > x-30 && stomuni_x < x+30) {
				return i;
			}
		}
	}
}

void Radar::supprimer(vector<Radar> &tabRadar, int indice_tour,  Carte &carte){

	int x = this->x_position;
	int y = this->y_position;

	carte.argent+=8;

	for(int i = y-30; i < y+30; i++){
		for(int j = x-30 ; j < x+30; j++){
			int position = 1800*3*(i-1)+j*3;
			carte.data[position+1]=255;
			carte.data[position+2]=255;
		}
	}


	vector<Radar>::iterator ptr = tabRadar.begin();
	for(int i = 0; i<indice_tour ; i++){
		ptr++;
	}

	tabRadar.erase(ptr);

}
void UsineArmement::supprimer(vector<UsineArmement> &tabUsineArmement, int indice_tour,  Carte &carte){

	int x = this->x_position;
	int y = this->y_position;

	carte.argent+=8;

	for(int i = y-30; i < y+30; i++){
		for(int j = x-30 ; j < x+30; j++){
			int position = 1800*3*(i-1)+j*3;
			carte.data[position+1]=255;
			carte.data[position+2]=255;
		}
	}


	vector<UsineArmement>::iterator ptr = tabUsineArmement.begin();
	for(int i = 0; i<indice_tour ; i++){
		ptr++;
	}

	tabUsineArmement.erase(ptr);

}
void StockMunition::supprimer(vector<StockMunition> &tabStockMunition, int indice_tour,  Carte &carte){

	int x = this->x_position;
	int y = this->y_position;

	carte.argent+=8;

	for(int i = y-30; i < y+30; i++){
		for(int j = x-30 ; j < x+30; j++){
			int position = 1800*3*(i-1)+j*3;
			carte.data[position+1]=255;
			carte.data[position+2]=255;
		}
	}


	vector<StockMunition>::iterator ptr = tabStockMunition.begin();
	for(int i = 0; i<indice_tour ; i++){
		ptr++;
	}

	tabStockMunition.erase(ptr);

}