#include <iostream>
#include <string>
#include "tableauMonstre.h"
#include <vector>

using namespace std;

vector<PetitMonstre>::iterator ptr;

void addToTabMonstre(vector<PetitMonstre> tabMonstre,  PetitMonstre monstre) {
		tabMonstre.push_back(monstre);
}