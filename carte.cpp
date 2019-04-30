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

GLuint setCarte(){
	GLuint texture = setTexture(CARTE);
	return texture;
}

void afficherCarte(GLuint texture, int size){

	drawTexture(texture, size);
}

int* setDataCarte(){
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

    cout<< "La largeur est "<<width<<" et la longueur est "<<height<<endl;


    //je veux enregistrer les données de l'image
	int* data = (int*) malloc(sizeof(int) * 3 * width * height);

	if(data == NULL){
    	cout<<"Carte : error bad memory allocation.\n"<<endl;
  	}


  	for(int i = 0 ; i<(width*height*3) ; i++){
  		//ici ça marche
  		carteppm>>nb;
  		//cout<<"J'ai récupéré "<<nb<<endl;
  		//ici ça marche pô
  		data[i]=nb;
  		//cout<<"J'ai mis dans data "<<data[i]<<endl;
  		carteppm.seekg(1, ios::cur);
  	}

  	carteppm.close();
  	return data;

}

void returnColor(int* data, int x, int y, int width, int height){

	int position = width*3*(y-1)+x*3;
	cout<<"R : "<<data[position+1]<<endl;
	cout<<"G : "<<data[position+2]<<endl;
	cout<<"B : "<<data[position+3]<<endl;

}


bool verifITD(){

	// on ouvre le fichier .itd

	string const nomCarte("./test.itd");
	ifstream carte(nomCarte.c_str());


	//pour chaque partie de la carte, on returne si c'est bon ou non
	bool header=verifHeader(nomCarte);
	bool carteOk=verifCarte(nomCarte);
	bool energie=verifEnergie(nomCarte);
	bool chemin=verifCouleurs(nomCarte, "chemin");
	bool noeud=verifCouleurs(nomCarte, "noeud");
	bool construct=verifCouleurs(nomCarte, "construct");
	bool out=verifCouleurs(nomCarte, "out");
	bool in = verifCouleurs(nomCarte, "in");
	bool allnoeuds = verifNoeuds(nomCarte);


	carte.close();
// vérifier au moins 1 zone entrée 1 zone sortie et 1 chiffre seul qui correspond au nb de lignes en dessous

	//on vérifie si absolument tout est ok
	if(header!=true || carteOk!=true || energie!=true || chemin!=true || construct!=true || noeud!=true || in!=true || out!=true){ exit(EXIT_FAILURE);}
	else {
		cout<< "Carte validée"<<endl; 
		return true;
	}

}

bool verifHeader(string const nomCarte){
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

bool verifCarte(string const nomCarte){
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

bool verifEnergie(string const nomCarte){
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
    			carte.close();
    			return true;
    		}
		}
	
	}
	carte.close();
	return false;
}


bool verifCouleurs(string const nomCarte, string verifMot){
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
    		}
        	carte.close();
    		return true;
    	}
	}
	carte.close();
	return false;
}

bool verifNoeuds(string const nomCarte) {
	string ligne;
	int nbNoeuds, type, nombre;

	ifstream carte(nomCarte.c_str());

	// On se place au début du fichier
	carte.seekg(0, ios::beg);

	//On se déplace à la 10e ligne où se trouve le chiffre désiré
	for(int i = 1 ; i <= 10; i++){
		getline(carte, ligne);
	}
/*
	//on récupère la valeur
	carte>>nbNoeuds;
	cout<< "le nombre est " << nbNoeuds <<endl;
	if(!nbNoeuds){cout<< "Erreur dans le nombre de noeuds" <<endl; return false;}

	carte.seekg(1, ios::cur);
	for(int j = 0 ; j < nbNoeuds ; j++){
		carte>>nombre;
		if(nombre!=j){cout<< "Erreur dans les noeuds" <<endl; return false;}

		carte.seekg(1, ios::cur);
		carte>>type;
		if(!type || type < 0 || type > 4){cout<< "Erreur dans le type du noeud "<< j <<endl; return false;}

		carte.seekg(1, ios::cur);
		carte>>nombre;
		if(!nombre){cout<< "Erreur dans la position du noeud "<< j <<endl; return false;}

		carte.seekg(1, ios::cur);
		carte>>nombre;
		if(!nombre){cout<< "Erreur dans la position du noeud "<< j <<endl; return false;}

		if(type == 1 || type == 2){
			carte.seekg(1, ios::cur);
			carte>>nombre;
			if(!nombre){printf("Erreur dans les noeuds\n"); return false;}
		}

		if(type == 3){
			carte.seekg(1, ios::cur);
			carte>>nombre;
			if(!nombre){printf("Erreur dans les noeuds\n"); return false;}

			carte.seekg(1, ios::cur);
			carte>>nombre;
			if(!nombre){printf("Erreur dans les noeuds\n"); return false;}
		}

		

		getline(carte, ligne);
	}
		*/

	carte.close();
	return true;
}
