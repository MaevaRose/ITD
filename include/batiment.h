#include <iostream>
#include <string>
#include "tour.h"

class Batiment   {

	public:
	Batiment(int prct, int port, int prix, int lvl, int x_pos, int y_pos);

	//méthodes

	virtual void typeBatiment() = 0;



	void poser(int x, int y, Carte &carte);				//OK

	void suprimer();						//OK

	void ameliorer(int level);				//OK

	void afficherEtat();					//OK

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

	void drawRadar();

};

class UsineArmement:public Batiment {

	void typeBatiment() {  return;  }

	public :
	UsineArmement();

	void ajouterPuissance(int pourcent, Tour &tour);

	void drawUsineArmement();
	
};

class StockMunition:public Batiment {

	void typeBatiment() {  return;  }

	public :
	StockMunition();

	void ajouterCadence(int pourcent, Tour &tour);

	void drawStockMunition();
	
};


//en bonus
/*class Centrale:public Batiment {

	void typeBatiment() {  return;  }

	void somme energie();

	public :
	Centrale();
	
}*/



void addToTabRadar(vector<TourBleue> &tabTourBleue, TourBleue tour);

void addToTabUsine(vector<TourJaune> &tabTourJaune, TourJaune tour);

void addToTabStock(vector<TourRouge> &tabTourRouge, TourRouge tour);

void printTab(vector<TourBleue> &tabTourBleue);

void drawAllBatiments(vector<TourBleue> &tabTourBleue, vector<TourJaune> &tabTourJaune, vector<TourRouge> &tabTourRouge, vector<TourVerte> &tabTourVerte, const unsigned int WINDOW_WIDTH, const unsigned int WINDOW_HEIGHT, int frameIndex );
