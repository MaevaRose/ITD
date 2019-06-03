#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Monstre {

	public:
	Monstre(int pv, int vit, int x_pos, int y_pos);
	
	//méthodes

	virtual void direLeTypeDuMonstre() = 0;
	
	void afficherEtat() const;					//OK

	void ajouterChemin(vector<int> cheminCalcule);

	void recevoirDegat(int nbDegats);			//OK

	bool estVivant() const;						//OK
	
	int getPositionX();							//OK

	int getPositionY();							//OK	

	int getVie();						

	void pushPosition(int x, int y);			//OK

	//void getAttributs() const;							//UTILITE A REVOIR

	void pushChemin(vector<vector<int>> &grapheNoeuds, vector<vector<int>> &tabPoids, int start, int end);

	void updatePos(vector<int> chemin, vector<vector<int>> posNoeuds, int &finPartie);

	vector<int> getChemin();

	int getIndice();

	void updateIndice();




	protected:
	//attributs
	int pts_vie;
	int vitesse;
	int x_position;
	int y_position;
	vector<int> chemin;
	int indiceChemin;
	//rajouter quelque chose pour dire résistance à une tour particuliere
};


class PetitMonstre:public Monstre {

	void direLeTypeDuMonstre() {
		return ;
	}

	public :
	PetitMonstre();

	void apparaitre(int x, int y, vector<PetitMonstre> &tabMonstre);

	void drawPetitMonstre();

	//void tuerMonstre(vector<PetitMonstre> &tabMonstre);
};


class GrosMonstre:public Monstre {

	void direLeTypeDuMonstre() {
		return ;
	}

	public :
	GrosMonstre();

	void apparaitre(int x, int y, vector<GrosMonstre> &tabMonstre);

	void drawGrosMonstre();
};


class MoyenMonstre:public Monstre {

	void direLeTypeDuMonstre() {
		return ;
	}

	public :
	MoyenMonstre();

	void apparaitre(int x, int y, vector<MoyenMonstre> &tabMonstre);

	void drawMoyenMonstre();
};


void tuerAllMonstre(vector<PetitMonstre> &tabPetitMonstre, vector<MoyenMonstre> &tabMoyenMonstre, vector<GrosMonstre> &tabGrosMonstre);

void updateAllMonstre(vector<PetitMonstre> &tabPetitMonstre, vector<MoyenMonstre> &tabMoyenMonstre, vector<GrosMonstre> &tabGrosMonstre, vector<int> chemin, vector<vector<int>> posNoeuds, int &finPartie);

void drawAllMonstres(vector<PetitMonstre> &tabPetitMonstre, vector<MoyenMonstre> &tabMoyenMonstre, vector<GrosMonstre> &tabGrosMonstre);

void addToTabPetitMonstre(vector<PetitMonstre> &tabMonstre,  PetitMonstre monstre);

void popOfTabPetitMonstre(vector<PetitMonstre> &tabMonstre, vector<PetitMonstre>::iterator ptr);

void addToTabMoyenMonstre(vector<MoyenMonstre> &tabMonstre,  MoyenMonstre monstre);

void popOfTabMoyenMonstre(vector<MoyenMonstre> &tabMonstre, vector<MoyenMonstre>::iterator ptr);

void addToTabGrosMonstre(vector<GrosMonstre> &tabMonstre,  GrosMonstre monstre);

void popOfTabGrosMonstre(vector<GrosMonstre> &tabMonstre, vector<GrosMonstre>::iterator ptr);

void drawAllMonstres(vector<PetitMonstre> &tabPetitMonstre, vector<MoyenMonstre> &tabMoyenMonstre, vector<GrosMonstre> &tabGrosMonstre);