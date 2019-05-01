#include <iostream>
#include <string>
#include "monstre.h"
#include "carte.h"

class Tour {

	public:
	Tour(int deg, int cad, int port, int prix, int lvl, int x_pos, int y_pos);

	//méthodes

	virtual void direLeTypeDeLaTour() = 0;



	void poser(int x, int y, Carte &carte);				//OK

	void supprimer();						//OK

	void ameliorer(int level);				//OK

	void afficherEtat();					//OK

	//void afficherHallo(int portee);					//OPENGL

	void attaquer(Monstre &cible);			//OK

	int getPortee();						//OK

	int getPositionX();						//OK

	int getPositionY();						//OK	

	void augmenterPuissance(int pourcent);	//OK

	void augmenterVitesse(int pourcent);	//OK

	void augmenterPortee(int pourcent);		//OK

	//void getAttributs() const;						//UTILITE A REVOIR

	//void consommerEnergie();							//BONUS


	protected:

	//attributs
	int degats;
	int cadence;
	int portee;
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
};


class TourJaune:public Tour {
	
	void direLeTypeDeLaTour() {
		return;
	}

	public :
	TourJaune();
};


class TourRouge:public Tour {
	
	void direLeTypeDeLaTour() {
		return;
	}

	public :
	TourRouge();
};


class TourVerte:public Tour {
	
	void direLeTypeDeLaTour() {
		return;
	}

	public :
	TourVerte();
};
