#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

//#include "../include/initialisation.hpp"
#include "../include/tour.h"
#include "../include/interface.hpp"

Interface interface;

Carte carte;

int finPartie = 0;

TourBleue tourbleue;
TourBleue select_blue;
vector<TourBleue> tabTourBleue;
    
TourRouge tourrouge;
TourRouge select_rouge;
vector<TourRouge> tabTourRouge;
    
TourJaune tourjaune;
TourJaune select_jaune;
vector<TourJaune> tabTourJaune;

TourVerte tourverte;
TourVerte select_verte;
vector<TourVerte> tabTourVerte;


PetitMonstre monstre1;
MoyenMonstre monstre2;
GrosMonstre monstre3;

vector<PetitMonstre> tabPetitMonstre;
vector<MoyenMonstre> tabMoyenMonstre;
vector<GrosMonstre> tabGrosMonstre;

vector<Noeud> noeuds = carte.noeuds;
vector<vector<int>> grapheNoeuds;
vector<vector<int>> tabPoids;
vector<vector<int>> posNoeuds;