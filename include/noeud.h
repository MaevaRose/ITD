#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Noeud {

	public:
	Noeud(int id, int type, int x, int y, vector<int> rel);

	//méthodes
	int getId ();

	int getPositionX();

	int getPositionY();

	int getType();

	void pushRel(vector<int> rel);

	vector<int> getRel();

	private:
	//attributs

	int id;
	int type;
	int x_position;
	int y_position;
	vector<int> relations;

};
	