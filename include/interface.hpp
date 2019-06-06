#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <math.h>
#include <string>

#include "../include/tour.h"

using namespace std;

class Interface{
	public :
	Interface();

	int select;

	bool clicOnInterface(int x, int y,  Carte &carte, vector<TourBleue> &tabTourBleue, vector<TourJaune> &tabTourJaune, vector<TourRouge> &tabTourRouge, vector<TourVerte> &tabTourVerte, vector<vector<int>> &tabPoids, vector<vector<int>> &grapheNoeud, vector<vector<int>> &posNoeuds);

	void clicOnMenuBas();

	void clicOnMenuHaut( Carte &carte, vector<TourBleue> &tabTourBleue, vector<TourJaune> &tabTourJaune, vector<TourRouge> &tabTourRouge, vector<TourVerte> &tabTourVerte, vector<vector<int>> &tabPoids, vector<vector<int>> &grapheNoeud, vector<vector<int>> &posNoeuds);

	void setAllTexture();

	void drawInterface(Carte &carte, vector<TourBleue> &tabTourBleue, vector<TourJaune> &tabTourJaune, vector<TourRouge> &tabTourRouge, vector<TourVerte> &tabTourVerte);

	void drawMenuHaut(Carte &carte, vector<TourBleue> &tabTourBleue, vector<TourJaune> &tabTourJaune, vector<TourRouge> &tabTourRouge, vector<TourVerte> &tabTourVerte);

	void drawMenuBas();

	int x; 
	int y;
	int tour_select;
	int indice_tour;

	private :
	GLuint texMenuBas;


};





