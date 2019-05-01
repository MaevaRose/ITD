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

	void ajouterPortee(int pourcent, Tour &tour);

	public :
	Radar();

};

class UsineArmement:public Batiment {

	void typeBatiment() {  return;  }

	void ajouterPuissance(int pourcent, Tour &tour);

	public :
	UsineArmement();
	
};

class StockMunition:public Batiment {

	void typeBatiment() {  return;  }

	void ajouterCadence(int pourcent, Tour &tour);

	public :
	StockMunition();
	
};


//en bonus
/*class Centrale:public Batiment {

	void typeBatiment() {  return;  }

	void somme energie();

	public :
	Centrale();
	
}*/