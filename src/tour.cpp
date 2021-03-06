#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include "../include/tour.h"


using namespace std;

Tour::Tour (int deg, int cad, float port, int prix, int lvl, int x_pos, int y_pos, int attaque) : degats(deg), cadence(cad), portee(port), cout(prix), level(lvl), x_position(x_pos), y_position(y_pos), attaque(attaque) {};
TourBleue::TourBleue () : Tour(30, 75, 150., 10, 1, -1, -1, 0) {};
TourRouge::TourRouge () : Tour(150, 500, 170., 20, 1, -1, -1, 0) {};
TourJaune::TourJaune () : Tour(20, 150, 110., 5, 1, -1, -1, 0) {};
TourVerte::TourVerte () : Tour(50, 100, 130., 15, 1, -1, -1, 0) {};

int width = 1800;




// void Tour::supprimer() {
// 	printf("Je supprime cette tour\n");
// 	//void popOfListTour
// }


void Tour::ameliorer(Carte &carte) {
	if(this->level<5 && this->cout/2<=carte.argent){
		this->level += 1;
		this->portee += 10;
		this->degats += 10;
		carte.argent -= this->cout/2;
	}
	//this->cadence -= 10;
}


void Tour::afficherEtat() {
	//afficherHallo(this->portee);
    printf("Niveau : %d.\nDégats : %d.\nCadence : %d.\n", level, degats, cadence);
}


bool Tour::aPortee(int x1, int y1){
	int x0 = this->x_position;
	int y0 = this->y_position;
	
	if(this->porteePlus > this->portee){
		if(sqrt((x1-x0)*(x1-x0)+(y1-y0)*(y1-y0)) < this->porteePlus){
			printf("Il est à une distance de %f\n", sqrt((x1-x0)*(x1-x0)+(y1-y0)*(y1-y0)));
			printf("La portée est de %f\n donc je peux lui tirer dessus", this->porteePlus);
			return true;
		}
	}
	else{
		if(sqrt((x1-x0)*(x1-x0)+(y1-y0)*(y1-y0)) < this->portee){
			printf("Il est à une distance de %f\n", sqrt((x1-x0)*(x1-x0)+(y1-y0)*(y1-y0)));
			printf("La portée est de %f\n donc je peux lui tirer dessus", this->portee);
			return true;
		}
	}

	

	return false;
}


void Tour::attaquer(vector<PetitMonstre> &tabPetitMonstre, vector<MoyenMonstre> &tabMoyenMonstre, vector<GrosMonstre> &tabGrosMonstre) {
	if (this->attaque == this->cadencePlus) {

		for(int i=0; i<tabPetitMonstre.size(); i++) {
			Monstre &cible = tabPetitMonstre[i]; 
			//if (sqrt((((cible.getPositionX())-(this->x_position))*((cible.getPositionX())-(this->x_position)))+(((cible.getPositionY())-(this->y_position))*((cible.getPositionY())-(this->y_position))))) 
			if (aPortee(cible.getPositionX(), cible.getPositionY())) {
				cible.recevoirDegat(this->degatsPlus);
				printf("petit monstre %d a : %d pv \n les dégâts étaient de %d et sont maintenant de %d", i, cible.getVie(), this->degats, this->degatsPlus);
			}
			
		}
		for(int i=0; i<tabMoyenMonstre.size(); i++) {
			Monstre &cible = tabMoyenMonstre[i]; 
			if (aPortee(cible.getPositionX(), cible.getPositionY())) {
				cible.recevoirDegat(this->degatsPlus);
				printf("moyen monstre %d a: %d pv \n", i, cible.getVie());
			}
			
		}
		for(int i=0; i<tabGrosMonstre.size(); i++) {
			Monstre &cible = tabGrosMonstre[i]; 
			if (aPortee(cible.getPositionX(), cible.getPositionY())) {
				cible.recevoirDegat(this->degatsPlus);
				printf("gros monstre %d a : %d pv \n", i, cible.getVie());
			}
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

int Tour::getNiveau(){
	return this->level;
}


void Tour::augmenterPuissance(int pourcent) {
	this->degatsPlus = this->degats + pourcent;
}


void Tour::augmenterVitesse(int pourcent) {
	this->cadencePlus = this->cadence - pourcent;
}


void Tour::augmenterPortee(float pourcent) {
	this->porteePlus = this->portee + pourcent;
}


void TourBleue::poser(int x, int y, Carte &carte, vector<TourBleue> &tabTourBleue, vector<vector<int>> &tabPoids, vector<vector<int>> &grapheNoeud, vector<vector<int>> &posNoeuds) {
	bool isConstructible = carte.isConstructible(x, y, 1800, 1012);

	if(isConstructible && carte.argent>=this->cout) {
		this->x_position = x;
		this->y_position = y;
		carte.argent -= this->cout;
		this->level = 1;

		this->degatsPlus = this->degats;
		this->cadencePlus = this->cadence;
		this->porteePlus = this->portee;


		//changer le ppm pour rendre la zone plus constructible
		for(int i = y-60 ; i < y+60 ; i++) {
			for(int j = x-60; j < x+60 ; j++){
				int position = width*3*(i-1)+j*3;
				carte.data[position+1]=0;
				carte.data[position+2]=10;
			}
		}

		ajoutePoidsChemin(this->portee, this->x_position, this->y_position, 30, tabPoids, grapheNoeud, posNoeuds);

		addToTabBlueTower(tabTourBleue, *this);
	}
}


void TourBleue::draw(const unsigned int WINDOW_WIDTH, const unsigned int WINDOW_HEIGHT ) {

	float x = (-1 + 2. * this->x_position / 1800.)*15.;
	float y = -(-1 + 2. * this->y_position / 1012.)*8.4;

		float portee = (this->porteePlus * 16.8) / 1012.;


	glPushMatrix();
	
	glTranslatef(x, y, 0);
    glBegin(GL_QUADS);
    glColor3ub(0, 0, 255);
    glVertex2f(-0.9, -0.9);
    glVertex2f(-0.9, 0.9);
    glVertex2f(0.9, 0.9);
    glVertex2f(0.9, -0.9);

    drawCircle(portee, 0);

    glEnd();
   	glPopMatrix();
}


void TourJaune::poser(int x, int y, Carte &carte, vector<TourJaune> &tabTourJaune, vector<vector<int>> &tabPoids, vector<vector<int>> &grapheNoeud, vector<vector<int>> &posNoeuds) {
	bool isConstructible = carte.isConstructible(x, y, 1800, 1012);
	if(isConstructible  && carte.argent>=this->cout){
		this->x_position = x;
		this->y_position = y;
		carte.argent -= this->cout;

		this->degatsPlus = this->degats;
		this->cadencePlus = this->cadence;
		this->porteePlus = this->portee;

		for(int i = y-60 ; i < y+60 ; i++){
			for(int j = x-60; j < x+60 ; j++){
				int position = width*3*(i-1)+j*3;
				carte.data[position+1]=0;
				carte.data[position+2]=100;
			}
		}

		ajoutePoidsChemin(this->portee, this->x_position, this->y_position, 20, tabPoids, grapheNoeud, posNoeuds);

		addToTabYellowTower(tabTourJaune, *this);
	}	
}


void TourJaune::draw(const unsigned int WINDOW_WIDTH, const unsigned int WINDOW_HEIGHT, int frameIndex, Sprites tours, GLuint textTourJaune) {

	float x = (-1 + 2. * this->x_position / 1800.)*15.;
	float y = -(-1 + 2. * this->y_position / 1012.)*8.4;
	float portee = (this->porteePlus * 16.8) / 1012.;


	glPushMatrix();
	
	glTranslatef(x, y, 0);
    //glBegin(GL_QUADS);
    glColor3ub(255, 204, 0);
    // glVertex2f(-0.9, -0.9);
    // glVertex2f(-0.9, 0.9);
    // glVertex2f(0.9, 0.9);
    // glVertex2f(0.9, -0.9);

    drawCircle(portee, 0);

    //glEnd();
   	glPopMatrix();

   	glColor3ub(255, 255, 255);
	
	tours.drawSprite(textTourJaune, 0.9, x, y, frameIndex);
}


void TourRouge::poser(int x, int y, Carte &carte, vector<TourRouge> &tabTourRouge, vector<vector<int>> &tabPoids, vector<vector<int>> &grapheNoeud, vector<vector<int>> &posNoeuds) {
	bool isConstructible = carte.isConstructible(x, y, 1800, 1012);
	if(isConstructible  && carte.argent>=this->cout){
		this->x_position = x;
		this->y_position = y;
		carte.argent -= this->cout;

		this->degatsPlus = this->degats;
		this->cadencePlus = this->cadence;
		this->porteePlus = this->portee;

		for(int i = y-60 ; i < y+60 ; i++){
			for(int j = x-60; j < x+60 ; j++){
				int position = width*3*(i-1)+j*3;
				carte.data[position+1]=0;
				carte.data[position+2]=150;
			}
		}

		ajoutePoidsChemin(this->portee, this->x_position, this->y_position, 50, tabPoids, grapheNoeud, posNoeuds);

		addToTabRedTower(tabTourRouge, *this);
	}
}


void TourRouge::draw(const unsigned int WINDOW_WIDTH, const unsigned int WINDOW_HEIGHT, int frameIndex, Sprites tours, GLuint textTourRouge ) {

	float x = (-1 + 2. * this->x_position / WINDOW_WIDTH)*15.;
	float y = -(-1 + 2. * this->y_position / WINDOW_HEIGHT)*8.4;
	float portee = (this->porteePlus * 16.8) / 1012.;

	glColor3ub(255, 0, 0);
	glPushMatrix();
		glTranslatef(x, y, 0);
		drawCircle(portee, 0);
	glPopMatrix();

	glColor3ub(255, 255, 255);
	
	tours.drawSprite(textTourRouge, 0.9, x, y, frameIndex);
}


void TourVerte::poser(int x, int y, Carte &carte, vector<TourVerte> &tabTourVerte, vector<vector<int>> &tabPoids, vector<vector<int>> &grapheNoeud, vector<vector<int>> &posNoeuds) {
	bool isConstructible = carte.isConstructible(x, y, 1800, 1012);
	if(isConstructible  && carte.argent>=this->cout){
		this->x_position = x;
		this->y_position = y;
		carte.argent -= this->cout;

		this->degatsPlus = this->degats;
		this->cadencePlus = this->cadence;
		this->porteePlus = this->portee;

		for(int i = y-60 ; i < y+60 ; i++){
			for(int j = x-60; j < x+60 ; j++){
				int position = width*3*(i-1)+j*3;
				carte.data[position+1]=0;
				carte.data[position+2]=50;
			}
		}

		ajoutePoidsChemin(this->portee, this->x_position, this->y_position, 40, tabPoids, grapheNoeud, posNoeuds);

		addToTabGreenTower(tabTourVerte, *this);
	}	
}


void TourVerte::draw(const unsigned int WINDOW_WIDTH, const unsigned int WINDOW_HEIGHT, int frameIndex, Sprites tours, GLuint textTourVerte ) {

	float x = (-1 + 2. * this->x_position / 1800.)*15.;
	float y = -(-1 + 2. * this->y_position / 1012.)*8.4;
	float portee = (this->porteePlus * 16.8) / 1012.;

	glPushMatrix();
	
	glTranslatef(x, y, 0);
    //glBegin(GL_QUADS);
    glColor3ub(0, 255, 0);
    // glVertex2f(-0.9, -0.9);
    // glVertex2f(-0.9, 0.9);
    // glVertex2f(0.9, 0.9);
    // glVertex2f(0.9, -0.9);

    drawCircle(portee, 0);

    //glEnd();
   	glPopMatrix();

   	glColor3ub(255, 255, 255);
	
	tours.drawSprite(textTourVerte, 0.9, x, y, frameIndex);
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
		//printf("sdvjbhoeqvb\n");
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

	Sprites tours(300, 300, 100, 100);

	GLuint textTourRouge = setPNGTexture("./images/tourRouge.png");
	GLuint textTourVerte = setPNGTexture("./images/tourVerte.png");
	GLuint textTourJaune = setPNGTexture("./images/tourJaune.png");
	vector<TourBleue>::iterator bleu=tabTourBleue.begin();
	vector<TourJaune>::iterator jaune=tabTourJaune.begin();
	vector<TourRouge>::iterator rouge=tabTourRouge.begin();
	vector<TourVerte>::iterator vert=tabTourVerte.begin();
	if(tabTourBleue.size()>0){
		int i=0;
		for (bleu = tabTourBleue.begin(); bleu < tabTourBleue.end(); bleu++){

			(*bleu).draw(WINDOW_WIDTH, WINDOW_HEIGHT);
		}
	}
	if(tabTourRouge.size()>0){
		for (rouge = tabTourRouge.begin(); rouge < tabTourRouge.end(); rouge++){

			(*rouge).draw(WINDOW_WIDTH, WINDOW_HEIGHT, frameIndex, tours, textTourRouge);	
		}
	}
	if(tabTourJaune.size()>0){
		for (jaune = tabTourJaune.begin(); jaune < tabTourJaune.end(); jaune++){

			(*jaune).draw(WINDOW_WIDTH, WINDOW_HEIGHT, frameIndex, tours, textTourJaune);
		}
	}
	if(tabTourVerte.size()>0){
		for (vert = tabTourVerte.begin(); vert < tabTourVerte.end(); vert++){

			(*vert).draw(WINDOW_WIDTH, WINDOW_HEIGHT, frameIndex, tours, textTourVerte);	
		}
	}	
}


int clickOnTowers(int x, int y, Carte &carte){
	int position = width*3*(y-1)+x*3;
	if(carte.data[position+1] == 0){
		if(carte.data[position+2] == 10){
			return 1;
		}
		if(carte.data[position+2] == 50){
			return 2;
		}
		if(carte.data[position+2] == 100){
			return 3;
		}
		if(carte.data[position+2] == 150){
			return 4;
		}
		if(carte.data[position+2] == 200){
			return 5;
		}
		if(carte.data[position+2] == 220){
			return 6;
		}
		if(carte.data[position+2] == 240){
			return 7;
		}
	}
	return -1;
}


int getTourBleue(int x, int y, vector<TourBleue> &tabTourBleue){
	if (tabTourBleue.size()>0) {
		for (int i=0; i<tabTourBleue.size(); i++) {
			int tour_x = tabTourBleue[i].getPositionX();
			int tour_y = tabTourBleue[i].getPositionY();
			if(tour_y > y-60 && tour_y < y+60 && tour_x > x-60 && tour_x < x+60) {
				return i;
			}
		}
	}
}


int getTourRouge(int x, int y, vector<TourRouge> &tabTourRouge){
	if (tabTourRouge.size()>0) {
		for (int i=0; i<tabTourRouge.size(); i++) {
			int tour_x = tabTourRouge[i].getPositionX();
			int tour_y = tabTourRouge[i].getPositionY();
			if(tour_y > y-60 && tour_y < y+60 && tour_x > x-60 && tour_x < x+60) {
				return i;
			}
		}
	}
}


int getTourJaune(int x, int y, vector<TourJaune> &tabTourJaune){
	if (tabTourJaune.size()>0) {
		for (int i=0; i<tabTourJaune.size(); i++) {
			int tour_x = tabTourJaune[i].getPositionX();
			int tour_y = tabTourJaune[i].getPositionY();
			if(tour_y > y-60 && tour_y < y+60 && tour_x > x-60 && tour_x < x+60) {
				return i;
			}
		}
	}
}


int getTourVerte(int x, int y, vector<TourVerte> &tabTourVerte){
	if (tabTourVerte.size()>0) {
		for (int i=0; i<tabTourVerte.size(); i++) {
			int tour_x = tabTourVerte[i].getPositionX();
			int tour_y = tabTourVerte[i].getPositionY();
			if(tour_y > y-60 && tour_y < y+60 && tour_x > x-60 && tour_x < x+60) {
				return i;
			}
		}
	}
}


// void afficherTourSelect(int x, int y, int select, vector<TourBleue> &tabTourBleue, vector<TourJaune> &tabTourJaune, vector<TourRouge> &tabTourRouge, vector<TourVerte> &tabTourVerte){
// 	if(select == 1){
// 		TourBleue tourbleue = getTourBleue(x, y, tabTourBleue);
// 		tourbleue.afficherEtat();
// 	}
// 	if(select == 2){
// 		TourVerte tourverte = getTourVerte(x, y, tabTourVerte);
// 		tourverte.afficherEtat();
// 	}
// 	if(select == 3){
// 		TourJaune tourjaune = getTourJaune(x, y, tabTourJaune);
// 		tourjaune.afficherEtat();
// 	}
// 	if(select == 4){
// 		TourRouge tourrouge = getTourRouge(x, y, tabTourRouge);
// 		tourrouge.afficherEtat();
// 	} 
// }


void TourBleue::supprimer(vector<TourBleue> &tabTourBleue, int indice_tour,  Carte &carte, vector<vector<int>> &tabPoids, vector<vector<int>> &grapheNoeud, vector<vector<int>> &posNoeuds) {
	printf("Je supprime cette tour bleue\n");

	int x = this->x_position;
	int y = this->y_position;

	carte.argent+=8;

	for(int i = y-60 ; i < y+60 ; i++){
		for(int j = x-60; j < x+60 ; j++){
			int position = width*3*(i-1)+j*3;
			carte.data[position+1]=255;
			carte.data[position+2]=255;
		}
	}



	vector<TourBleue>::iterator ptr = tabTourBleue.begin();
	for(int i = 0; i<indice_tour ; i++){
		ptr++;
	}

	ajoutePoidsChemin(this->portee, this->x_position, this->y_position, -30, tabPoids, grapheNoeud, posNoeuds);

	tabTourBleue.erase(ptr);
	//void popOfListTour
}

void TourJaune::supprimer(vector<TourJaune> &tabTourJaune, int indice_tour,  Carte &carte, vector<vector<int>> &tabPoids, vector<vector<int>> &grapheNoeud, vector<vector<int>> &posNoeuds) {
	printf("Je supprime cette tour jaune\n");

	int x = this->x_position;
	int y = this->y_position;

	carte.argent+=4;

	for(int i = y-60 ; i < y+60 ; i++){
		for(int j = x-60; j < x+60 ; j++){
			int position = width*3*(i-1)+j*3;
			carte.data[position+1]=255;
			carte.data[position+2]=255;
		}
	}

	vector<TourJaune>::iterator ptr = tabTourJaune.begin();
	for(int i = 0; i<indice_tour ; i++){
		ptr++;
	}

	ajoutePoidsChemin(this->portee, this->x_position, this->y_position, -20, tabPoids, grapheNoeud, posNoeuds);

	tabTourJaune.erase(ptr);
	//void popOfListTour
}

void TourRouge::supprimer(vector<TourRouge> &tabTourRouge, int indice_tour,  Carte &carte, vector<vector<int>> &tabPoids, vector<vector<int>> &grapheNoeud, vector<vector<int>> &posNoeuds) {
	printf("Je supprime cette tour rouge\n");

	int x = this->x_position;
	int y = this->y_position;

	carte.argent+=16;

	for(int i = y-60 ; i < y+60 ; i++){
		for(int j = x-60; j < x+60 ; j++){
			int position = width*3*(i-1)+j*3;
			carte.data[position+1]=255;
			carte.data[position+2]=255;
		}
	}

	vector<TourRouge>::iterator ptr = tabTourRouge.begin();
	for(int i = 0; i<indice_tour ; i++){
		ptr++;
	}

	ajoutePoidsChemin(this->portee, this->x_position, this->y_position, -50, tabPoids, grapheNoeud, posNoeuds);

	tabTourRouge.erase(ptr);
	//void popOfListTour
}

void TourVerte::supprimer(vector<TourVerte> &tabTourVerte, int indice_tour,  Carte &carte, vector<vector<int>> &tabPoids, vector<vector<int>> &grapheNoeud, vector<vector<int>> &posNoeuds) {
	printf("Je supprime cette tour jaune\n");

	int x = this->x_position;
	int y = this->y_position;

	carte.argent+=12;

	for(int i = y-60 ; i < y+60 ; i++){
		for(int j = x-60; j < x+60 ; j++){
			int position = width*3*(i-1)+j*3;
			carte.data[position+1]=255;
			carte.data[position+2]=255;
		}
	}

	vector<TourVerte>::iterator ptr = tabTourVerte.begin();
	for(int i = 0; i<indice_tour ; i++){
		ptr++;
	}

	ajoutePoidsChemin(this->portee, this->x_position, this->y_position, -40, tabPoids, grapheNoeud, posNoeuds);

	tabTourVerte.erase(ptr);
	//void popOfListTour
}