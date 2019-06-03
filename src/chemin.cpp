#include <iostream>
#include <string>
#include <vector>
#include "../include/chemin.h"

using namespace std;

Chemin::Chemin(int poid, int idNoeud1, int idNoeud2) : poid(poid), idNoeud1(idNoeud1), idNoeud2(idNoeud2) {};


int Chemin::getPoid() {
	return this->poid;
}


int Chemin::getNoeud1() {
	return this->idNoeud1;
}


int Chemin::getNoeud2() {
	return this->idNoeud2;
}