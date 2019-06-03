#include <iostream>
#include <string>
#include <vector>
#include "monstre.h"
#include "carte.h"
#include "../include/foncOpenGL.h"
//#include "sprites.h"

using namespace std;


class Tour {

	public:
	Tour(int deg, int cad, float port, int prix, int lvl, int x_pos, int y_pos);

	//méthodes

	virtual void direLeTypeDeLaTour() = 0;



	//void poser(int x, int y, Carte &carte, vector<TourBleue> tabTourBleue);				//OK

	void supprimer();						//OK

	void ameliorer(int level);				//OK

	void afficherEtat();					//OK

	//void afficherHallo(int portee);					//OPENGL

	

	void attaquer(vector<PetitMonstre> &tabPetitsMonstre, vector<MoyenMonstre> &tabMoyenMonstre, vector<GrosMonstre> &tabGrosMonstre);			//OK

	int getPortee();						//OK

	int getPositionX();						//OK

	int getPositionY();						//OK	

	void augmenterPuissance(int pourcent);	//OK

	void augmenterVitesse(int pourcent);	//OK

	void augmenterPortee(int pourcent);		//OK

	bool aPortee(int x1, int y1);

	//void getAttributs() const;						//UTILITE A REVOIR

	//void consommerEnergie();							//BONUS


	protected:

	//attributs
	int degats;
	int cadence;
	float portee;
	int cout;
	int level;
	int x_position;
	int y_position;

	//en bonus
	int consommation;
};


class TourBleue:public Tour {
	
	void direLeTypeDeLaTour() {
		return;
	}

	public :
	TourBleue();

	void poser(int x, int y, Carte &carte, vector<TourBleue> &tabTourBleue);
	void draw(const unsigned int WINDOW_WIDTH, const unsigned int WINDOW_HEIGHT);

	//TourBleue(TourBleue &) = delete;
	//TourBleue& operator=(const TourBleue&) = delete;
};


class TourJaune:public Tour {
	
	void direLeTypeDeLaTour() {
		return;
	}

	public :
	TourJaune();

	void poser(int x, int y, Carte &carte, vector<TourJaune> &tabTourJaune);
	void draw(const unsigned int WINDOW_WIDTH, const unsigned int WINDOW_HEIGHT);
};


class TourRouge:public Tour {
	
	void direLeTypeDeLaTour() {
		return;
	}

	public :
	TourRouge();
	void poser(int x, int y, Carte &carte, vector<TourRouge> &tabTourRouge);
	void draw(const unsigned int WINDOW_WIDTH, const unsigned int WINDOW_HEIGHT, int frameIndex, Sprites tours, GLuint textTourRouge);
};


class TourVerte:public Tour {
	
	void direLeTypeDeLaTour() {
		return;
	}

	public :
	TourVerte();
	void poser(int x, int y, Carte &carte, vector<TourVerte> &tabTourVerte);
	void draw(const unsigned int WINDOW_WIDTH, const unsigned int WINDOW_HEIGHT);
};


//Tableaux de tours

void addToTabBlueTower(vector<TourBleue> &tabTourBleue, TourBleue tour);

void addToTabYellowTower(vector<TourJaune> &tabTourJaune, TourJaune tour);

void addToTabRedTower(vector<TourRouge> &tabTourRouge, TourRouge tour);

void addToTabGreenTower(vector<TourVerte> &tabTourVerte, TourVerte tour);

void printTab(vector<TourBleue> &tabTourBleue);

void attaqueAllTower(vector<TourBleue> &tabTourBleue, vector<TourJaune> &tabTourJaune, vector<TourRouge> &tabTourRouge, vector<TourVerte> &tabTourVerte, vector<PetitMonstre> &tabPetitMonstre, vector<MoyenMonstre> &tabMoyenMonstre, vector<GrosMonstre> &tabGrosMonstre);

void drawAllTower(vector<TourBleue> &tabTourBleue, vector<TourJaune> &tabTourJaune, vector<TourRouge> &tabTourRouge, vector<TourVerte> &tabTourVerte, const unsigned int WINDOW_WIDTH, const unsigned int WINDOW_HEIGHT, int frameIndex );
