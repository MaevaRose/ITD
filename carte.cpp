#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>
#include <string>
#include <fstream>
#include "carte.h"
#include "image.h"

using namespace std;
static const char CARTE[] = "./niveau1.ppm";
static const string STRING_CARTE = "./niveau1.ppm";

Carte::Carte(){};

GLuint Carte::setCarte(){
	GLuint texture = setTexture(CARTE); 
	return texture;
}

void Carte::afficherCarte(GLuint texture, int size){

	drawTexture(texture, size);
}

void Carte::setDataCarte(){
	int width;
	int height;
	string mot;
	int nb;

	//j'ouvre le fichier ppm
	string const nomCarteppm("./niveau1.ppm");
	ifstream carteppm(nomCarteppm.c_str(), ios::in);

	if(!carteppm){cout<<"Non la carte ppm s'ouvre pas loul"<<endl;}

	//je vérifie qu'elle est bien en P3
	carteppm.seekg(0, ios::beg);
    carteppm>>mot;
    cout<<mot<<endl;
    if(mot!="P3") { cout<<"La carte n'est pas en ppm p3 !"<<endl;}

    //je récupère la largeur et la hauteur de l'image
    carteppm.seekg(1, ios::cur);
    carteppm>>width;

    carteppm.seekg(1, ios::cur);
    carteppm>>height;

    cout<< "La largeur de la carte est "<<width<<" et sa longueur est "<<height<<endl;


    //allocation mémoire pour la carte
	this->data = (int*) malloc(sizeof(int) * 3 * width * height);

	if(this->data == NULL){
    	cout<<"Carte : erreur lors de l'allocation mémoire.\n"<<endl;
  	}

  	//enregistrement de la carte dans un tableau de int
  	for(int i = 0 ; i<(width*height*3) ; i++){
  		carteppm>>nb;
  		this->data[i]=nb;
  		carteppm.seekg(1, ios::cur);
  	}

  	carteppm.close();

}

void Carte::returnColor(int x, int y, int width){

	int position = width*3*(y-1)+x*3;
	cout<<"R : "<<this->data[position+1]<<endl;
	cout<<"G : "<<this->data[position+2]<<endl;
	cout<<"B : "<<this->data[position+3]<<endl;

}


bool Carte::verifITD(){

	// on ouvre le fichier .itd
	string const nomCarte("./test.itd");
	ifstream carte(nomCarte.c_str());


	//pour chaque partie de la carte, on returne si c'est bon ou non
	bool header=verifHeader(nomCarte);
	bool carteOk=verifCarte(nomCarte);
	bool energie=verifEnergie(nomCarte);
	bool chemin=verifCouleurs(nomCarte, "chemin", this->cheminColor);
	bool noeud=verifCouleurs(nomCarte, "noeud", this->noeudColor);
	bool construct=verifCouleurs(nomCarte, "construct", this->constructColor);
	bool out=verifCouleurs(nomCarte, "out", this->outColor);
	bool in = verifCouleurs(nomCarte, "in",this->inColor);
	bool allnoeuds = verifNoeuds(nomCarte);

	cout<<"L'énergie est de "<<this->energie<<endl;
	carte.close();
// vérifier au moins 1 zone entrée 1 zone sortie et 1 chiffre seul qui correspond au nb de lignes en dessous

	//on vérifie si absolument tout est ok
	if(header!=true || carteOk!=true || energie!=true || chemin!=true || construct!=true || noeud!=true || in!=true || out!=true || allnoeuds!=true )
		{ 
			cout<<"La carte n'est pas valide"<<endl;
			exit(EXIT_FAILURE);
		}
	else {
		cout<< "Carte validée"<<endl; 
		return true;
	}

}

bool Carte::verifHeader(string const nomCarte){
	string ligne;
    string mot;
    int nombre;

    ifstream carte(nomCarte.c_str());

	carte.seekg(0, ios::beg);
        carte>>mot;
        if(mot!="@ITD") { return false;}

        carte.seekg(1, ios::cur);
        carte>>nombre;
        if(!nombre) { return false;}

        carte.seekg(1, ios::cur);
        carte>>mot;
        if(mot!="#"){ return false;}

    carte.close();
    return true;

}

bool Carte::verifCarte(string const nomCarte){
	string ligne;
	string mot;

	ifstream carte(nomCarte.c_str());

	while(getline(carte, ligne)){
		carte>>mot;
    	if(mot=="carte") { carte.close();return true;}
	}
	carte.close();
	return false;

}

bool Carte::verifEnergie(string const nomCarte){
	string ligne;
	string mot;

	ifstream carte(nomCarte.c_str());

	while(getline(carte, ligne)){
		carte>>mot;
    	if(mot=="energie") { 
    		int nombre;
    		carte.seekg(1, ios::cur);
    		carte>>nombre;
    		if(!nombre) {
    			printf("Erreur energie\n"); 
    			return false;
    		}
    		else {
    			this->energie=nombre;
    			carte.close();
    			return true;
    		}
		}
	
	}
	carte.close();
	return false;
}


bool Carte::verifCouleurs(string const nomCarte, string verifMot, int value[3]){
	string ligne;
	string mot;
 
	ifstream carte(nomCarte.c_str());

	while(getline(carte, ligne)){
		carte>>mot;
    	if(mot==verifMot) { 
    		int nombre;
    		for(int i=0;i<3;i++){
    			carte.seekg(1, ios::cur);
    			carte>>nombre;
    			if(!nombre){printf("Erreur couleurs\n"); return false;}
    			value[i]=nombre;
    		}
        	carte.close();
    		return true;
    	}
	}
	carte.close();
	return false;
}

bool Carte::verifNoeuds(string const nomCarte) {
	string ligne;
	int nbNoeuds, type, nombre;
	int x, y;
	int width = 1800;

	ifstream carte(nomCarte.c_str());

	// On se place au début du fichier
	carte.seekg(0, ios::beg);

	//On se déplace à la 10e ligne où se trouve le chiffre désiré
	for(int i = 1 ; i < 10; i++){
		getline(carte, ligne);
	}

	//on récupère la valeur
	carte>>nbNoeuds;
	cout<< "le nombre de noeuds est de " << nbNoeuds <<endl;
	if(!nbNoeuds){cout<< "Erreur dans le nombre de noeuds" <<endl; return false;}

	carte.seekg(1, ios::cur);
	for(int j = 0 ; j < nbNoeuds ; j++)
	{
		carte>>nombre;
		if(nombre!=j){cout<< "Erreur dans les noeuds" <<endl; return false;}

		carte.seekg(1, ios::cur);
		carte>>type;
		if(!type || type < 0 || type > 4){cout<< "Erreur dans le type du noeud "<< j <<endl; return false;}

		carte.seekg(1, ios::cur);
		carte>>nombre;
		if(!nombre || nombre<0 ){cout<< "Erreur dans la position du noeud "<< j <<endl; return false;}
		x=nombre;

		carte.seekg(1, ios::cur);
		carte>>nombre;
		if(!nombre || nombre<0 ){cout<< "Erreur dans la position du noeud "<< j <<endl; return false;}
		y=nombre;

		//cout<< "les noeuds sont à "<<x<<" "<<y<<endl;
		if(type == 1 || type == 2){
			carte.seekg(1, ios::cur);
			carte>>nombre;
			if(!nombre){cout<<"Erreur dans les noeuds"<<endl; return false;}

			/*bool entree=isIn(700, 725, width);
			bool sortie = isOut(x, y, width);
			if(!entree && !sortie){
				cout<<"Erreur : l'entrée ou la sortie indiqué.e ne correspond pas à la carte"<<endl; return false;
			}*/
		}

		if(type == 3){
			carte.seekg(1, ios::cur);
			carte>>nombre;
			if(!nombre){printf("Erreur dans les noeuds\n"); return false;}

			carte.seekg(1, ios::cur);
			carte>>nombre;
			if(!nombre){printf("Erreur dans les noeuds\n"); return false;}

			/*bool noeud = isNoeud(x, y, width);
			if(!noeud){
				cout<<"Erreur : le noeud indiqué ne correspond pas à la carte"<<endl; return false;
			}*/

		}

		getline(carte, ligne);
	}
		

	carte.close();
	return true;
}

bool Carte::isConstructible(int x, int y, int width){
	int position = width*3*(y-1)+x*3;
	for(int i=0; i<3; i++){
		if(this->data[position+i+1]!=this->constructColor[i]){
			cout<<"Cette zone n'est pas constructible"<<endl;
			return false;
		}
	}
	cout<<"Cette zone est constructible"<<endl;
	return true;
}

bool Carte::isChemin(int x, int y, int width){
	int position = width*3*(y-1)+x*3;
	for(int i=0; i<3; i++){
		if(this->data[position+i+1]!=this->cheminColor[i]){
			cout<<"Cette zone n'est pas un chemin"<<endl;
			return false;
		}
	}
	cout<<"Cette zone est un chemin"<<endl;
	return true;
}

bool Carte::isIn(int x, int y, int width){
	int position = width*3*(y-1)+x*3;
	for(int i=0; i<3; i++){
		if(this->data[position+i+1]!=this->inColor[i]){
			cout<<"Cette zone n'est pas une zone d'entrée"<<endl;
			return false;
		}
	}
	cout<<"Cette zone est une zone d'entrée"<<endl;
	return true;
}

bool Carte::isOut(int x, int y, int width){
	int position = width*3*(y-1)+x*3;
	for(int i=0; i<3; i++){
		if(this->data[position+i+1]!=this->outColor[i]){
			cout<<"Cette zone n'est pas une zone de sortie"<<endl;
			return false;
		}
	}
	cout<<"Cette zone est une zone de sortie"<<endl;
	return true;
}

bool Carte::isNoeud(int x, int y, int width){
	int position = width*3*(y-1)+x*3;
	for(int i=0; i<3; i++){
		if(this->data[position+i+1]!=this->cheminColor[i]){
			cout<<"Cette zone n'est pas un noeud"<<endl;
			return false;
		}
	}
	cout<<"Cette zone est un noeud"<<endl;
	return true;
}