#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class Carte{
	public :
	Carte();

	GLuint setCarte();

	void afficherCarte(GLuint texture, float x, float y);

	void setDataCarte();

	void returnColor(int x, int y, int width);

	bool verifITD();

	bool verifHeader(string const nomCarte);

	bool verifCarte(string const nomCarte);

	bool verifEnergie(string const nomCarte);

	bool verifCouleurs(string const nomCarte, string verifMot, int value[3]);

	bool verifNoeuds(string const nomCarte);

	bool isConstructible(int x, int y, int width);
	bool isChemin(int x, int y, int width);
	bool isIn(int x, int y, int width);
	bool isOut(int x, int y, int width);
	bool isNoeud(int x, int y, int width);

	protected:
	int* data; 
	int energie;
	int cheminColor[3];
	int noeudColor[3];
	int constructColor[3];
	int outColor[3];
	int inColor[3];

};

