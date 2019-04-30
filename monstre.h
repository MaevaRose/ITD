#include <iostream>
#include <string>

class Monstre {

	public:
	Monstre(int pv, int vit, int x_pos, int y_pos);
	
	//méthodes

	virtual void direLeTypeDuMonstre() = 0;



	void apparaitre(int x, int y);				//OK

	void tuerMonstre();							//OK

	void afficherEtat() const;					//OK

	//void calculChemin();									//DIJKSTRA

	void recevoirDegat(int nbDegats);			//OK

	bool estVivant() const;						//OK
	
	int getPositionX();							//OK

	int getPositionY();							//OK	

	void updatePosition(int x, int y);			//OK

	//void getAttributs() const;							//UTILITE A REVOIR


	private:
	//attributs
	int pts_vie;
	int vitesse;
	int x_position;
	int y_position;
	//rajouter quelque chose pour dire résistance à une tour particuliere

};

class PetitMonstre:public Monstre {

	void direLeTypeDuMonstre() {
		return;
	}

	public :
	PetitMonstre();
};


class GrosMonstre:public Monstre {

	void direLeTypeDuMonstre() {
		return;
	}

	public :
	GrosMonstre();
};

class MoyenMonstre:public Monstre {

	void direLeTypeDuMonstre() {
		return;
	}

	public :
	MoyenMonstre();
};