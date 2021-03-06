#include <iostream>
#include <string>
#include <vector>


#include "monstre.h"

//#include "carte.h"
//#include "../include/foncOpenGL.h"
//#include "sprites.h"

using namespace std;


class Tour {

	public:
	Tour(int deg, int cad, float port, int prix, int lvl, int x_pos, int y_pos, int attaque);

	//méthodes

	virtual void direLeTypeDeLaTour() = 0;



	//void poser(int x, int y, Carte &carte, vector<TourBleue> tabTourBleue);				//OK

	void supprimer();						//OK

	void ameliorer(Carte &carte);				//OK

	void afficherEtat();					//OK

	//void afficherHallo(int portee);					//OPENGL

	

	void attaquer(vector<PetitMonstre> &tabPetitsMonstre, vector<MoyenMonstre> &tabMoyenMonstre, vector<GrosMonstre> &tabGrosMonstre);			//OK

	int getPortee();						//OK

	int getPositionX();						//OK

	int getPositionY();						//OK	

	int getNiveau();

	void augmenterPuissance(int pourcent);	//OK

	void augmenterVitesse(int pourcent);	//OK

	void augmenterPortee(float pourcent);		//OK

	bool aPortee(int x1, int y1);

	void buttonLevelUp();

	void buttonDelete();

	//void getAttributs() const;						//UTILITE A REVOIR

	//void consommerEnergie();							//BONUS


	protected:

	//attributs
	int degats;
	int cadence;
	float portee;
	int degatsPlus;
	int cadencePlus;
	float porteePlus;
	int cout;
	int level;
	int x_position;
	int y_position;
	int attaque;

	//en bonus
	int consommation;
};


class TourBleue:public Tour {
	
	void direLeTypeDeLaTour() {
		return;
	}

	public :
	TourBleue();

	void poser(int x, int y, Carte &carte, vector<TourBleue> &tabTourBleue, vector<vector<int>> &tabPoids, vector<vector<int>> &grapheNoeud, vector<vector<int>> &posNoeuds);
	void draw(const unsigned int WINDOW_WIDTH, const unsigned int WINDOW_HEIGHT);
	void supprimer(vector<TourBleue> &tabTourBleue, int indice_tour, Carte &carte, vector<vector<int>> &tabPoids, vector<vector<int>> &grapheNoeud, vector<vector<int>> &posNoeuds);

	//TourBleue(TourBleue &) = delete;
	//TourBleue& operator=(const TourBleue&) = delete;
};


class TourJaune:public Tour {
	
	void direLeTypeDeLaTour() {
		return;
	}

	public :
	TourJaune();

	void poser(int x, int y, Carte &carte, vector<TourJaune> &tabTourJaune, vector<vector<int>> &tabPoids, vector<vector<int>> &grapheNoeud, vector<vector<int>> &posNoeuds);
	void draw(const unsigned int WINDOW_WIDTH, const unsigned int WINDOW_HEIGHT, int frameIndex, Sprites tours, GLuint textTourJaune);
	void supprimer(vector<TourJaune> &tabTourJaune, int indice_tour, Carte &carte, vector<vector<int>> &tabPoids, vector<vector<int>> &grapheNoeud, vector<vector<int>> &posNoeuds);
};


class TourRouge:public Tour {
	
	void direLeTypeDeLaTour() {
		return;
	}

	public :
	TourRouge();
	void poser(int x, int y, Carte &carte, vector<TourRouge> &tabTourRouge, vector<vector<int>> &tabPoids, vector<vector<int>> &grapheNoeud, vector<vector<int>> &posNoeuds);
	void draw(const unsigned int WINDOW_WIDTH, const unsigned int WINDOW_HEIGHT, int frameIndex, Sprites tours, GLuint textTourRouge);
	void supprimer(vector<TourRouge> &tabTourRouge, int indice_tour, Carte &carte, vector<vector<int>> &tabPoids, vector<vector<int>> &grapheNoeud, vector<vector<int>> &posNoeuds);
};


class TourVerte:public Tour {
	
	void direLeTypeDeLaTour() {
		return;
	}

	public :
	TourVerte();
	void poser(int x, int y, Carte &carte, vector<TourVerte> &tabTourVerte, vector<vector<int>> &tabPoids, vector<vector<int>> &grapheNoeud, vector<vector<int>> &posNoeuds);
	void draw(const unsigned int WINDOW_WIDTH, const unsigned int WINDOW_HEIGHT, int frameIndex, Sprites tours, GLuint textTourVerte);
	void supprimer(vector<TourVerte> &tabTourVerte, int indice_tour, Carte &carte, vector<vector<int>> &tabPoids, vector<vector<int>> &grapheNoeud, vector<vector<int>> &posNoeuds);
};


//Tableaux de tours

void addToTabBlueTower(vector<TourBleue> &tabTourBleue, TourBleue tour);

void addToTabYellowTower(vector<TourJaune> &tabTourJaune, TourJaune tour);

void addToTabRedTower(vector<TourRouge> &tabTourRouge, TourRouge tour);

void addToTabGreenTower(vector<TourVerte> &tabTourVerte, TourVerte tour);

void printTab(vector<TourBleue> &tabTourBleue);

void attaqueAllTower(vector<TourBleue> &tabTourBleue, vector<TourJaune> &tabTourJaune, vector<TourRouge> &tabTourRouge, vector<TourVerte> &tabTourVerte, vector<PetitMonstre> &tabPetitMonstre, vector<MoyenMonstre> &tabMoyenMonstre, vector<GrosMonstre> &tabGrosMonstre);

void drawAllTower(vector<TourBleue> &tabTourBleue, vector<TourJaune> &tabTourJaune, vector<TourRouge> &tabTourRouge, vector<TourVerte> &tabTourVerte, const unsigned int WINDOW_WIDTH, const unsigned int WINDOW_HEIGHT, int frameIndex );


int clickOnTowers(int x, int y, Carte &carte);

int getTourBleue(int x, int y, vector<TourBleue> &tabTourBleue);

int getTourRouge(int x, int y, vector<TourRouge> &tabTourRouge);

int getTourJaune(int x, int y, vector<TourJaune> &tabTourJaune);

int getTourVerte(int x, int y, vector<TourVerte> &tabTourVerte);

void afficherTourSelect(int x, int y, int select, vector<TourBleue> &tabTourBleue, vector<TourJaune> &tabTourJaune, vector<TourRouge> &tabTourRouge, vector<TourVerte> &tabTourVerte);