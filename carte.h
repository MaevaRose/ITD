#include <iostream>
#include <string>
#include <fstream>

using namespace std;

GLuint setCarte();

void afficherCarte(GLuint texture, int size);

int* setDataCarte();

void returnColor(int* data, int x, int y, int width, int height);

bool verifITD();

bool verifHeader(string const nomCarte);

bool verifCarte(string const nomCarte);

bool verifEnergie(string const nomCarte);

bool verifChemin(string const nomCarte);

bool verifNoeud(string const nomCarte);

bool verifIn(string const nomCarte);

bool verifOut(string const nomCarte);

bool verifCouleurs(string const nomCarte, string verifMot);

bool verifNoeuds(string const nomCarte);