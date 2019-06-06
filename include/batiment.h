#include <iostream>
#include <string>
#include "tour.h"

class Batiment   {

	public:
	Batiment(int prct, int port, int prix, int lvl, int x_pos, int y_pos);

	//méthodes

	virtual void typeBatiment() = 0;



	//void poser(int x, int y, Carte &carte);				//OK

	void suprimer();						//OK

	void ameliorer(Carte &carte);				//OK

	void afficherEtat();					//OK

	bool aPortee(int x1, int y1);

	//void afficherHallo(int portee);					//OPENGL

	int getPortee();						//OK

	int getPositionX();						//OK

	int getPositionY();						//OK	

	//void getAttributs() const;						//UTILITE A REVOIR


	protected:
	//attributs
	int pourcent;
	int portee;
	int cout;
	int level;
	int x_position;
	int y_position;
};




class Radar:public Batiment {

	void typeBatiment() {  return;  }
	

	public :
	Radar();

	void ajouterPortee(int pourcent, Tour &tour);
	void poser(int x, int y, Carte &carte, vector<Radar> &tabRadar);

	void augmenterTour(vector<TourBleue> &tabTourBleue, vector<TourJaune> &tabTourJaune, vector<TourRouge> &tabTourRouge, vector<TourVerte> &tabTourVerte);

	void drawRadar();

	void supprimer(vector<Radar> &tabRadar, int indice_tour,  Carte &carte);

};

class UsineArmement:public Batiment {

	void typeBatiment() {  return;  }

	public :
	UsineArmement();

	void ajouterPuissance(int pourcent, Tour &tour);

	void poser(int x, int y, Carte &carte, vector<UsineArmement> &tabUsineArmement);

	void augmenterTour(vector<TourBleue> &tabTourBleue, vector<TourJaune> &tabTourJaune, vector<TourRouge> &tabTourRouge, vector<TourVerte> &tabTourVerte);

	void drawUsineArmement();

	void supprimer(vector<UsineArmement> &tabUsineArmement, int indice_tour,  Carte &carte);
	
};

class StockMunition:public Batiment {

	void typeBatiment() {  return;  }

	public :
	StockMunition();

	void ajouterCadence(int pourcent, Tour &tour);

	void poser(int x, int y, Carte &carte, vector<StockMunition> &tabStockMunition);

	void augmenterTour(vector<TourBleue> &tabTourBleue, vector<TourJaune> &tabTourJaune, vector<TourRouge> &tabTourRouge, vector<TourVerte> &tabTourVerte);

	void drawStockMunition();

	void supprimer(vector<StockMunition> &tabStockMunition, int indice_tour,  Carte &carte);
	
};


//en bonus
/*class Centrale:public Batiment {

	void typeBatiment() {  return;  }

	void somme energie();

	public :
	Centrale();
	
}*/



void addToTabRadar(vector<Radar> &tabRadar, Radar radar);

void addToTabUsine(vector<UsineArmement> &tabUsineArmement, UsineArmement usine);

void addToTabStock(vector<StockMunition> &tabStockMunition, StockMunition stock);

void printTab(vector<TourBleue> &tabTourBleue);

void drawAllBatiments(vector<Radar> &tabRadar, vector<UsineArmement> &tabUsineArmement, vector<StockMunition> &tabStockMunition, int frameIndex );

void augmenteAllTours(vector<Radar> &tabRadar, vector<UsineArmement> &tabUsineArmement, vector<StockMunition> &tabStockMunition, vector<TourBleue> &tabTourBleue, vector<TourJaune> &tabTourJaune, vector<TourRouge> &tabTourRouge, vector<TourVerte> &tabTourVerte);

int getRadar(int x, int y, vector<Radar> &tabRadar);

int getUsineArmement(int x, int y, vector<UsineArmement> &tabUsineArmement);

int getStockMunition(int x, int y, vector<StockMunition> &tabStockMunition);