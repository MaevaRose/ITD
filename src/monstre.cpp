#include <iostream>
#include <string>
#include <vector>
//#include "../include/tableauMonstre.h"

//#include "../include/grapheNoeuds.h"
#include "../include/monstre.h"

using namespace std;

Monstre::Monstre(int pv, float vit, int x_pos, int y_pos, int indice, Sprites spriteMonstre) : pts_vie(pv), vitesse(vit), x_position(x_pos), y_position(y_pos), indiceChemin(indice), spriteMonstre(spriteMonstre) {};

PetitMonstre::PetitMonstre() : Monstre(100, 2., -1, -1, 0, spriteMonstre) {};
MoyenMonstre::MoyenMonstre() : Monstre(250, 1., -1, -1, 0, spriteMonstre) {};
GrosMonstre::GrosMonstre() : Monstre(500, 0.5, -1, -1, 0, spriteMonstre) {};



void PetitMonstre::apparaitre(int x, int y, vector<PetitMonstre> &tabMonstre) {
	this->x_position = x;
	this->y_position = y;
	Sprites spriteMonstre(400, 400, 100, 100);
	this->spriteMonstre = spriteMonstre;
	this->textMonstre = setPNGTexture("./images/petitMonstre.png");
	addToTabPetitMonstre(tabMonstre, *this);
}


void MoyenMonstre::apparaitre(int x, int y, vector<MoyenMonstre> &tabMonstre) {
	this->x_position = x;
	this->y_position = y;
	Sprites spriteMonstre(400, 400, 100, 100);
	this->spriteMonstre = spriteMonstre;
	addToTabMoyenMonstre(tabMonstre, *this);
}


void GrosMonstre::apparaitre(int x, int y, vector<GrosMonstre> &tabMonstre) {
	this->x_position = x;
	this->y_position = y;
	Sprites spriteMonstre(400, 400, 100, 100);
	this->spriteMonstre = spriteMonstre;
	addToTabGrosMonstre(tabMonstre, *this);
}


void Monstre::afficherEtat() const {
     printf("Vie du monstre : %d\n", pts_vie);
}


void Monstre::ajouterChemin(vector<int> cheminCalcule) {
	this->chemin = cheminCalcule;
}


void Monstre::recevoirDegat(int nbDegats) {
	pts_vie-=nbDegats;

	if(pts_vie<0) {
		pts_vie = 0; 
		//tuerMonstre();
	}
}


bool Monstre::estVivant() const {
	//printf("il est mort lui\n");
    return pts_vie > 0;
}


int Monstre::getPositionX() {
	return this -> x_position;
}


int Monstre::getPositionY() {
	return this -> y_position;
}

int Monstre::getVie() {
	return this->pts_vie;
}


void Monstre::pushPosition(int x, int y) {
	this -> x_position = x;
	this -> y_position = y;
}


void PetitMonstre::drawPetitMonstre(int frameIndex) {
	float x = (-1 + 2 * this -> x_position / 1800.)*15;
	float y = -(-1 + 2 * this -> y_position/ 1012.)*8.4;

     glColor3ub(255,255,255);


    this->spriteMonstre.drawSprite(this->textMonstre, 0.7, x, y, frameIndex);
}


void MoyenMonstre::drawMoyenMonstre() {
	float x = (-1 + 2 * this -> x_position / 1800.)*15;
	float y = -(-1 + 2 * this -> y_position/ 1012.)*8.4;

	glPushMatrix();
		glTranslatef(x, y, 0);
            glColor3ub(210,84,28);
            drawCircle(0.1,1);
    glPopMatrix();
}


void GrosMonstre::drawGrosMonstre() {
	float x = (-1 + 2 * this -> x_position / 1800.)*15;
	float y = -(-1 + 2 * this -> y_position/ 1012.)*8.4;

	glPushMatrix();
		glTranslatef(x, y, 0);
            glColor3ub(190,33,6);
            drawCircle(0.1,1);
    glPopMatrix();
}


void Monstre::pushChemin(vector<vector<int>> &grapheNoeuds, vector<vector<int>> &tabPoids, int start, int end) {
	this -> chemin = calculCheminMonstre(grapheNoeuds, tabPoids, start, end);
}


vector<int> Monstre::getChemin() {
	return this -> chemin;
}

int Monstre::getIndice() {
	return this->indiceChemin;
}

void Monstre::updateIndice() {
	(this->indiceChemin)++;
}


void Monstre::updatePos(vector<int> chemin, vector<vector<int>> posNoeuds, int &finPartie) { 

	int sens;
	//printf("j'update la position\n");
	//printf("positions avant update : x=%d, y=%d\n", this->x_position, this->y_position);

	if (posNoeuds[chemin[this->indiceChemin]][0] == posNoeuds[chemin[this->indiceChemin+1]][0]) {
		//printf("je suis dans if 1 \n");
		if (posNoeuds[chemin[this->indiceChemin]][1] < posNoeuds[chemin[this->indiceChemin+1]][1]) {
			sens = 1;
		}
		else {
			sens = -1;
		}

		if (this -> y_position != posNoeuds[chemin[this->indiceChemin+1]][1]) {
			this -> y_position += sens*this->vitesse;
		}
		else {
			this->indiceChemin += 1;
			printf("update indice y\n");
		}
	}

	else if (posNoeuds[chemin[this->indiceChemin]][1] == posNoeuds[chemin[this->indiceChemin+1]][1]) {
		//printf("je suis dans else if 1\n");
		if (posNoeuds[chemin[this->indiceChemin]][0] < posNoeuds[chemin[this->indiceChemin+1]][0]) {
			sens = 1;
		}
		else {
			sens = -1;
		}
		if (this -> x_position != posNoeuds[chemin[this->indiceChemin+1]][0]) {
			this -> x_position += sens*this->vitesse;
		}
		else {
			this->indiceChemin += 1;
			printf("update indice x\n");
		}
	}
	if (this->indiceChemin == chemin.size()) {
		finPartie = 1;
	}
	//printf("positions apres update : x=%d, y=%d\n", this->x_position, this->y_position);
}




// FONCTIONS SUR LES TABLEAUX DE MONSTRES


void addToTabPetitMonstre(vector<PetitMonstre> &tabMonstre,  PetitMonstre monstre) {
	tabMonstre.push_back(monstre);
}
 

void popOfTabPetitMonstre(Carte &carte, vector<PetitMonstre> &tabMonstre, vector<PetitMonstre>::iterator ptr) {
	// printf("taille avant tuage %d\n", tabMonstre.size());
	// printf("JE SUIS DANS TUER LE PETIT MONSTRE !!!\n");
	tabMonstre.erase(ptr);
	carte.argent += 2;
	// printf("taille tab monstre : %d\n", tabMonstre.size());
}


void addToTabMoyenMonstre(vector<MoyenMonstre> &tabMonstre,  MoyenMonstre monstre) {
	tabMonstre.push_back(monstre);
}


void popOfTabMoyenMonstre(Carte &carte, vector<MoyenMonstre> &tabMonstre, vector<MoyenMonstre>::iterator ptr) {
	tabMonstre.erase(ptr);
	carte.argent += 5;
}


void addToTabGrosMonstre(vector<GrosMonstre> &tabMonstre,  GrosMonstre monstre) {
	tabMonstre.push_back(monstre);
}


void popOfTabGrosMonstre(Carte &carte, vector<GrosMonstre> &tabMonstre, vector<GrosMonstre>::iterator ptr) {
	tabMonstre.erase(ptr);
	carte.argent += 10;	
}


void tuerAllMonstre(Carte &carte, vector<PetitMonstre> &tabPetitMonstre, vector<MoyenMonstre> &tabMoyenMonstre, vector<GrosMonstre> &tabGrosMonstre) {
	int i = 0;
	vector<PetitMonstre>::iterator iterator1;
	//printf("taille petit monstres : %d\n", tabPetitMonstre.size());
	if (tabPetitMonstre.size() > 0) {
		for(iterator1=tabPetitMonstre.begin(); iterator1!=tabPetitMonstre.end(); iterator1++) {
			//printf("je suis dans tuer les monstres\n");

			Monstre &cible = tabPetitMonstre[i]; 
			if (!cible.estVivant()) {
				//printf("je suis dans le if pour voir si il est mort\n");
				popOfTabPetitMonstre(carte, tabPetitMonstre, iterator1);
				//printf("j'ai tué le petit monstre\n");
				iterator1--;
				i--;
			}
			i++;
		}
	}
	if (tabMoyenMonstre.size() > 0) {
		i=0;
		vector<MoyenMonstre>::iterator iterator2;
		for(iterator2=tabMoyenMonstre.begin(); iterator2!=tabMoyenMonstre.end(); iterator2++) {
			Monstre &cible = tabMoyenMonstre[i]; 
			if (!cible.estVivant()) {
				popOfTabMoyenMonstre(carte, tabMoyenMonstre, iterator2);
				iterator2--;
				i--;
			}
			i++;
		}
	}
	if (tabGrosMonstre.size() > 0) { 
		i=0;
		vector<GrosMonstre>::iterator iterator3;
		for(iterator3=tabGrosMonstre.begin(); iterator3!=tabGrosMonstre.end(); iterator3++) {
			Monstre &cible = tabGrosMonstre[i]; 
			if (!cible.estVivant()) {
				popOfTabGrosMonstre(carte, tabGrosMonstre, iterator3);
				iterator3--;
				i--;
			}
			i++;
		}
	}
}


void updateAllMonstre(vector<PetitMonstre> &tabPetitMonstre, vector<MoyenMonstre> &tabMoyenMonstre, vector<GrosMonstre> &tabGrosMonstre, vector<int> chemin, vector<vector<int>> posNoeuds, int &finPartie) {
	//printf("update monstre begin\n");
	for(int i=0; i<tabPetitMonstre.size(); i++) {
		Monstre &cible = tabPetitMonstre[i]; 
		cible.updatePos(chemin, posNoeuds, finPartie);
	}
	for(int i=0; i<tabMoyenMonstre.size(); i++) {
		Monstre &cible = tabMoyenMonstre[i]; 
		cible.updatePos(chemin, posNoeuds, finPartie);
	}
	for(int i=0; i<tabGrosMonstre.size(); i++) {
		Monstre &cible = tabGrosMonstre[i]; 
		cible.updatePos(chemin, posNoeuds, finPartie);
	}
}


void drawAllMonstres(int frameIndex, vector<PetitMonstre> &tabPetitMonstre, vector<MoyenMonstre> &tabMoyenMonstre, vector<GrosMonstre> &tabGrosMonstre) {
	int size = tabPetitMonstre.size();
	PetitMonstre monstre1;
	for (int i=0; i<size; i++) {
		monstre1 = tabPetitMonstre[i];
		monstre1.drawPetitMonstre(frameIndex);
	}

	size = tabMoyenMonstre.size();
	MoyenMonstre monstre2;
	for (int i=0; i<size; i++) {
		monstre2 = tabMoyenMonstre[i];
		monstre2.drawMoyenMonstre();
	}

	size = tabGrosMonstre.size();
	GrosMonstre monstre3;
	for (int i=0; i<size; i++) {
		monstre3 = tabGrosMonstre[i];
		monstre3.drawGrosMonstre();
	}

}


vector<vector<int>> creerTabVague() {
	
	vector<vector<int>> tabVagues;

	tabVagues.push_back(vector<int>(1, 10));
	tabVagues.push_back(vector<int>(1, 25));
	tabVagues.push_back(vector<int>(1, 40));
	tabVagues.push_back(vector<int>(1, 60));
	tabVagues.push_back(vector<int>(1, 80));
	tabVagues.push_back(vector<int>(1, 100));
	tabVagues.push_back(vector<int>(1, 120));
	tabVagues.push_back(vector<int>(1, 150));
	tabVagues.push_back(vector<int>(1, 180));
	tabVagues.push_back(vector<int>(1, 210));

	tabVagues[0].push_back(10);
	tabVagues[0].push_back(0);
	tabVagues[0].push_back(0);

	tabVagues[1].push_back(10);
	tabVagues[1].push_back(5);
	tabVagues[1].push_back(0);

	tabVagues[2].push_back(10);
	tabVagues[2].push_back(10);
	tabVagues[2].push_back(0);

	tabVagues[3].push_back(10);
	tabVagues[3].push_back(0);
	tabVagues[3].push_back(2);

	tabVagues[4].push_back(10);
	tabVagues[4].push_back(10);
	tabVagues[4].push_back(5);

	tabVagues[5].push_back(25);
	tabVagues[5].push_back(0);
	tabVagues[5].push_back(0);

	tabVagues[6].push_back(0);
	tabVagues[6].push_back(15);
	tabVagues[6].push_back(1);

	tabVagues[7].push_back(5);
	tabVagues[7].push_back(0);
	tabVagues[7].push_back(5);

	tabVagues[8].push_back(10);
	tabVagues[8].push_back(5);
	tabVagues[8].push_back(3);

	tabVagues[9].push_back(15);
	tabVagues[9].push_back(8);
	tabVagues[9].push_back(5);

	//printf("J'ai finis de créer les vagues\n");
	return tabVagues;
}


void creerVague(int &indice, vector<vector<int>> &tabVagues, int temps, int &nbLoop, int start, int end, vector<vector<int>> posNoeuds, vector<PetitMonstre> &tabPetitMonstre, vector<MoyenMonstre> &tabMoyenMonstre, vector<GrosMonstre> &tabGrosMonstre, vector<vector<int>> &grapheNoeuds, vector<vector<int>> &tabPoids) {
	if (temps > tabVagues[indice][0]) {
		if (nbLoop == 5) {
			if (tabVagues[indice][1] != 0) {
				PetitMonstre monstre;
				monstre.pushChemin(grapheNoeuds, tabPoids, start, end);
				monstre.apparaitre(posNoeuds[start][0], posNoeuds[start][1], tabPetitMonstre);
				tabVagues[indice][1]--;
			}
			else if (tabVagues[indice][2] != 0) {
				MoyenMonstre monstre;
				monstre.apparaitre(posNoeuds[start][0], posNoeuds[start][1], tabMoyenMonstre);
				tabVagues[indice][2]--;
			}
			else if (tabVagues[indice][3] != 0) {
				GrosMonstre monstre;
				monstre.apparaitre(posNoeuds[start][0], posNoeuds[start][1], tabGrosMonstre);
				tabVagues[indice][3]--;
			}			
			else {
				indice++;
			}

			nbLoop = 0;
		}
		else {
			nbLoop++;
		}
	}
}

