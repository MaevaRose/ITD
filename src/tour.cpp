#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include "../include/tour.h"


using namespace std;

Tour::Tour (int deg, int cad, float port, int prix, int lvl, int x_pos, int y_pos, int attaque) : degats(deg), cadence(cad), portee(port), cout(prix), level(lvl), x_position(x_pos), y_position(y_pos), attaque(attaque) {};
TourBleue::TourBleue () : Tour(100, 100, 130, 10, 1, -1, -1, 0) {};
TourRouge::TourRouge () : Tour(150, 500, 150., 20, 1, -1, -1, 0) {};
TourJaune::TourJaune () : Tour(20, 1000, 120, 5, 1, -1, -1, 0) {};
TourVerte::TourVerte () : Tour(50, 100, 130, 10, 1, -1, -1, 0) {};

	int width = 1800;




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

bool Tour::aPortee(int x1, int y1){
	//positionTour = width*3*(this->y_position-1)+this->x_position*3;
	//positionMonstre =  width*3*(y-1)+x*3;
	printf("Est il à ma portée ?\n");
	int x0 = this->x_position;
	int y0 = this->y_position;
	printf("Il est à une distance de %f\n", sqrt((x1-x0)*(x1-x0)+(y1-y0)*(y1-y0)));
	printf("La portée est de %f\n", this->portee);

	if(sqrt((x1-x0)*(x1-x0)+(y1-y0)*(y1-y0)) < this->portee){
		printf("Il est à ma portééée\n");
		return true;
	}

	return false;
}


void Tour::attaquer(vector<PetitMonstre> &tabPetitMonstre, vector<MoyenMonstre> &tabMoyenMonstre, vector<GrosMonstre> &tabGrosMonstre) {
	if (this->attaque == this->cadence) {

		for(int i=0; i<tabPetitMonstre.size(); i++) {
			Monstre &cible = tabPetitMonstre[i]; 
			if (sqrt((((cible.getPositionX())-(this->x_position))*((cible.getPositionX())-(this->x_position)))+(((cible.getPositionY())-(this->y_position))*((cible.getPositionY())-(this->y_position))))) {
				cible.recevoirDegat(this->degats);
			}
			printf("monstre 1 : %d pv \n", cible.getVie());
		}
		for(int i=0; i<tabMoyenMonstre.size(); i++) {
			Monstre &cible = tabMoyenMonstre[i]; 
			if (sqrt((((cible.getPositionX())-(this->x_position))*((cible.getPositionX())-(this->x_position)))+(((cible.getPositionY())-(this->y_position))*((cible.getPositionY())-(this->y_position))))) {
				cible.recevoirDegat(this->degats);
			}
			printf("monstre 2 : %d pv \n", cible.getVie());
		}
		for(int i=0; i<tabGrosMonstre.size(); i++) {
			Monstre &cible = tabGrosMonstre[i]; 
			if (sqrt((((cible.getPositionX())-(this->x_position))*((cible.getPositionX())-(this->x_position)))+(((cible.getPositionY())-(this->y_position))*((cible.getPositionY())-(this->y_position))))) {
				cible.recevoirDegat(this->degats);
			}
			printf("monstre 3 : %d pv \n", cible.getVie());

		}

	(this->attaque) = 0;
	}
	else {
		(this->attaque)++;
	}
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


void TourBleue::poser(int x, int y, Carte &carte, vector<TourBleue> &tabTourBleue) {
	bool isConstructible = carte.isConstructible(x, y, 1800, 1012);
	//printf("!!!!!!!! Je pose ça là\n");

	if(isConstructible) {
		this->x_position = x;
		this->y_position = y;
		this->cout = this->cout/2;

		//changer le ppm pour rendre la zone plus constructible
		for(int i = y-60 ; i < y+60 ; i++) {
			for(int j = x-60; j < x+60 ; j++){
				int position = width*3*(i-1)+j*3;
				carte.data[position+1]=0;
			}
		}

		addToTabBlueTower(tabTourBleue, *this);
	}
	
	
}


void TourBleue::draw(const unsigned int WINDOW_WIDTH, const unsigned int WINDOW_HEIGHT ) {

	float x = (-1 + 2. * this->x_position / 1800.)*15.;
	float y = -(-1 + 2. * this->y_position / 1012.)*8.4;

	glPushMatrix();
	
	glTranslatef(x, y, 0);
    glBegin(GL_QUADS);
    glColor3ub(0, 0, 255);
    glVertex2f(-0.9, -0.9);
    glVertex2f(-0.9, 0.9);
    glVertex2f(0.9, 0.9);
    glVertex2f(0.9, -0.9);

    glEnd();
   	glPopMatrix();
}


void TourJaune::poser(int x, int y, Carte &carte, vector<TourJaune> &tabTourJaune) {
	bool isConstructible = carte.isConstructible(x, y, 1800, 1012);
	//printf("!!!!!!!! Je pose ça là\n");
	if(isConstructible){
		this->x_position = x;
		this->y_position = y;
		this->cout = this->cout/2;

		for(int i = y-60 ; i < y+60 ; i++){
			for(int j = x-60; j < x+60 ; j++){
				int position = width*3*(i-1)+j*3;
				carte.data[position+1]=0;
			}
		}

		addToTabYellowTower(tabTourJaune, *this);
	}	
}


void TourJaune::draw(const unsigned int WINDOW_WIDTH, const unsigned int WINDOW_HEIGHT ) {

	float x = (-1 + 2. * this->x_position / 1800.)*15.;
	float y = -(-1 + 2. * this->y_position / 1012.)*8.4;

	glPushMatrix();
	
	glTranslatef(x, y, 0);
    glBegin(GL_QUADS);
    glColor3ub(255, 204, 0);
    glVertex2f(-0.9, -0.9);
    glVertex2f(-0.9, 0.9);
    glVertex2f(0.9, 0.9);
    glVertex2f(0.9, -0.9);

    glEnd();
   	glPopMatrix();
}


void TourRouge::poser(int x, int y, Carte &carte, vector<TourRouge> &tabTourRouge) {
	bool isConstructible = carte.isConstructible(x, y, 1800, 1012);
	//printf("!!!!!!!! Je pose ça là\n");
	if(isConstructible){
		this->x_position = x;
		this->y_position = y;
		this->cout = this->cout/2;

		for(int i = y-60 ; i < y+60 ; i++){
			for(int j = x-60; j < x+60 ; j++){
				int position = width*3*(i-1)+j*3;
				carte.data[position+1]=0;
			}
		}

		addToTabRedTower(tabTourRouge, *this);
	}
	
	
}


void TourRouge::draw(const unsigned int WINDOW_WIDTH, const unsigned int WINDOW_HEIGHT, int frameIndex, Sprites tours, GLuint textTourRouge ) {

	float x = (-1 + 2. * this->x_position / WINDOW_WIDTH)*15.;
	float y = -(-1 + 2. * this->y_position / WINDOW_HEIGHT)*8.4;

	glColor3ub(255, 255, 255);
	
	tours.drawSprite(textTourRouge, 0.9, x, y, frameIndex);

}


void TourVerte::poser(int x, int y, Carte &carte, vector<TourVerte> &tabTourVerte) {
	bool isConstructible = carte.isConstructible(x, y, 1800, 1012);
	//printf("!!!!!!!! Je pose ça là\n");
	if(isConstructible){
		this->x_position = x;
		this->y_position = y;
		this->cout = this->cout/2;

		for(int i = y-60 ; i < y+60 ; i++){
			for(int j = x-60; j < x+60 ; j++){
				int position = width*3*(i-1)+j*3;
				carte.data[position+1]=0;
			}
		}

		addToTabGreenTower(tabTourVerte, *this);
	}	
}


void TourVerte::draw(const unsigned int WINDOW_WIDTH, const unsigned int WINDOW_HEIGHT ) {

	float x = (-1 + 2. * this->x_position / 1800.)*15.;
	float y = -(-1 + 2. * this->y_position / 1012.)*8.4;

	glPushMatrix();
	
	glTranslatef(x, y, 0);
    glBegin(GL_QUADS);
    glColor3ub(0, 255, 0);
    glVertex2f(-0.9, -0.9);
    glVertex2f(-0.9, 0.9);
    glVertex2f(0.9, 0.9);
    glVertex2f(0.9, -0.9);

    glEnd();
   	glPopMatrix();
}


//Tableaux de tours

void addToTabBlueTower(vector<TourBleue> &tabTourBleue, TourBleue tour) {
	tabTourBleue.push_back(tour);
	printf("C'est dans tabTourBleue !\n");
}


void addToTabYellowTower(vector<TourJaune> &tabTourJaune, TourJaune tour) {
	tabTourJaune.push_back(tour);
	printf("C'est dans tabTourJaune !\n");
}


void addToTabRedTower(vector<TourRouge> &tabTourRouge, TourRouge tour) {
	tabTourRouge.push_back(tour);
	printf("C'est dans tabTourRouge !\n");
}


void addToTabGreenTower(vector<TourVerte> &tabTourVerte, TourVerte tour) {
	tabTourVerte.push_back(tour);
	printf("C'est dans tabTourVerte !\n");
}


void printTab(vector<TourBleue> &tabTourBleue){

	vector<TourBleue>::iterator ptr;
	vector<TourBleue>::value_type t;


	//for (ptr = tabTourBleue.begin(); ptr < tabTourBleue.end(); ptr++){
		printf("sdvjbhoeqvb\n");
		//cout<<tabTourBleue[0]<<endl;
	//}
}


void attaqueAllTower(vector<TourBleue> &tabTourBleue, vector<TourJaune> &tabTourJaune, vector<TourRouge> &tabTourRouge, vector<TourVerte> &tabTourVerte, vector<PetitMonstre> &tabPetitMonstre, vector<MoyenMonstre> &tabMoyenMonstre, vector<GrosMonstre> &tabGrosMonstre) {
	if (tabTourBleue.size()>0) {
		//printf("dans le if tour bleue\n");
		for (int i=0; i<tabTourBleue.size(); i++) {
			tabTourBleue[i].attaquer(tabPetitMonstre, tabMoyenMonstre, tabGrosMonstre);
		}
	}
	//printf("hors du if tour bleue\n");
	if (tabTourJaune.size()>0) {
		for (int i=0; i<tabTourJaune.size(); i++) {
			tabTourJaune[i].attaquer(tabPetitMonstre, tabMoyenMonstre, tabGrosMonstre);
		}
	}
	if (tabTourRouge.size()>0) {
		for (int i=0; i<tabTourRouge.size(); i++) {
			tabTourRouge[i].attaquer(tabPetitMonstre, tabMoyenMonstre, tabGrosMonstre);
		}
	}
	if (tabTourVerte.size()>0) {
		for (int i=0; i<tabTourVerte.size(); i++) {
			tabTourVerte[i].attaquer(tabPetitMonstre, tabMoyenMonstre, tabGrosMonstre);
		}
	}
}


void drawAllTower(vector<TourBleue> &tabTourBleue, vector<TourJaune> &tabTourJaune, vector<TourRouge> &tabTourRouge, vector<TourVerte> &tabTourVerte, const unsigned int WINDOW_WIDTH, const unsigned int WINDOW_HEIGHT, int frameIndex ) {
	//cout<<"hello"<<endl;
	//tabTourBleue[0]->draw(WINDOW_WIDTH, WINDOW_HEIGHT);
	Sprites tours(300, 300, 100, 100);
	//GLuint textTourRouge = setTexture("./images/test_sprite.jpg");
	GLuint textTourRouge = setPNGTexture("./images/tourRouge.png");
	vector<TourBleue>::iterator bleu=tabTourBleue.begin();
	vector<TourJaune>::iterator jaune=tabTourJaune.begin();
	vector<TourRouge>::iterator rouge=tabTourRouge.begin();
	vector<TourVerte>::iterator vert=tabTourVerte.begin();
	if(tabTourBleue.size()>0){
		int i=0;
		for (bleu = tabTourBleue.begin(); bleu < tabTourBleue.end(); bleu++){
			// i++;
			//for (int i = 0; i < tabTourBleue.size(); i++){
			(*bleu).draw(WINDOW_WIDTH, WINDOW_HEIGHT);
			//printf("tour %d :\n", i);
			//(*ptr).afficherEtat();
			
		}
	}
	if(tabTourRouge.size()>0){
		for (rouge = tabTourRouge.begin(); rouge < tabTourRouge.end(); rouge++){
			// i++;
			//for (int i = 0; i < tabTourBleue.size(); i++){
			(*rouge).draw(WINDOW_WIDTH, WINDOW_HEIGHT, frameIndex, tours, textTourRouge);
			//printf("tour %d :\n", i);
			//(*ptr).afficherEtat();
			
		}
	}
	if(tabTourJaune.size()>0){
		for (jaune = tabTourJaune.begin(); jaune < tabTourJaune.end(); jaune++){
			// i++;
			//for (int i = 0; i < tabTourJaune.size(); i++){
			(*jaune).draw(WINDOW_WIDTH, WINDOW_HEIGHT);
			//printf("tour %d :\n", i);
			//(*ptr).afficherEtat();
			
		}
	}
	if(tabTourVerte.size()>0){
		for (vert = tabTourVerte.begin(); vert < tabTourVerte.end(); vert++){
			// i++;
			//for (int i = 0; i < tabTourVerte.size(); i++){
			(*vert).draw(WINDOW_WIDTH, WINDOW_HEIGHT);
			//printf("tour %d :\n", i);
			//(*ptr).afficherEtat();
			
		}
		//printf("Il y a %d tours\n", tabTourBleue.size());
	}
	else{
		//cout<<"y'a aucune tour wesh"<<endl;
	}
	
}