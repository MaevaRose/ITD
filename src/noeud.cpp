#include <iostream>
#include <string>
#include <vector>
#include "../include/noeud.h"

using namespace std;


Noeud::Noeud(int id, int type, int x, int y, vector<int> relations) : id(id), type(type), x_position(x), y_position(y), relations(relations) {};


int Noeud::getId() {
	return this -> id;
}


int Noeud::getType() {
	return this -> type;
}


int Noeud::getPositionX() {
	return this -> x_position;
}


int Noeud::getPositionY() {
	return this -> y_position;
}

// void Noeud::pushRel(vector<int> relations){
// 	this->relations = relations;
// }

vector<int> Noeud::getRel(){
	return this->relations;
}

