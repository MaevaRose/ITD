#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Chemin {

	public :
	Chemin(int poid, int idNoeud1, int idNoeud2);

	//méthodes
	int getPoid();

	int getNoeud1();

	int getNoeud2();


	private:
	//attributs

	int poid;
	int idNoeud1;
	int idNoeud2;
};