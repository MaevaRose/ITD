#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>
#include <string>
#include <fstream>
#include "../include/carte.h"
#include "../include/foncOpenGL.h"

using namespace std;
static const char CARTE[] = "./images/niveau2.ppm";
static const string STRING_CARTE = "./images/niveau2.ppm";

Carte::Carte(){};

GLuint Carte::setCarte(){
	GLuint texture = setTexture(CARTE); 
	return texture;
}

void Carte::afficherCarte(GLuint texture, float x, float y){

	//drawTexture(texture, x, y);
	glColor3ub(255, 255, 255);
    glEnable(GL_TEXTURE_2D);

        glBindTexture(GL_TEXTURE_2D, texture);

        glBegin(GL_QUADS);

        glTexCoord2f(0,1);
        glVertex2f(-x, -y);

        glTexCoord2f(1,1);
        glVertex2f(x, -y);

        glTexCoord2f(1,0);
        glVertex2f(x, y);

        glTexCoord2f(0,0);
        glVertex2f(-x, y);

        glEnd();

        glBindTexture(GL_TEXTURE_2D, 0);
        glDisable(GL_TEXTURE_2D);

}

bool Carte::isConstructible(int x, int y, int width, int height){
	if (x<50 || y<50 || x+50>width || y+50>height){
		//printf("Hors carte !\n");
		return false;
	}
	else{
		int position = width*3*(y-1)+x*3;
		int coin1 = width*3*((y+50)-1)+(x-50)*3;
		int coin2 = width*3*((y-50)-1)+(x+50)*3;
		int coin3 = width*3*((y-50)-1)+(x-50)*3;
		int coin4 = width*3*((y+50)-1)+(x+50)*3;
		for(int i=0; i<3; i++){
			if(this->data[position+i+1]!=this->constructColor[i] || 
				this->data[coin1+i+1]!=this->constructColor[i] ||
				this->data[coin2+i+1]!=this->constructColor[i] ||
				this->data[coin3+i+1]!=this->constructColor[i] ||
				this->data[coin4+i+1]!=this->constructColor[i]){
					//cout<<"Cette zone n'est pas constructible"<<endl;
					return false;
			}
		}
		//cout<<"Cette zone est constructible"<<endl;
		return true;
	}
	
}

void Carte::setDataCarte(){
	int width;
	int height;
	string mot;
	int nb;

	//j'ouvre le fichier ppm
	string const nomCarteppm("./images/niveau2.ppm");
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


  	//enregistrement de la carte dans un tableau de int
  	for(int i = 0 ; i<(width*height*3) ; i++){
  		carteppm>>nb;
  		//this->data[i]=nb;
  		data.push_back(nb);
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
	string const nomCarte("./data/carte2.itd");
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
	bool bresenham = verifChemin(nomCarte);

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
		//vérification couleurs noeuds et 
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
    			//carte.seekg(1, ios::cur);
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


//--------------------------------------------------------------
// On vérifie la syntaxe des noeuds et les enregistre au passage
//-------------------------------------------------------------
bool Carte::verifNoeuds(string const nomCarte) {
	string ligne;
	string mot;
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
		//noeud->id = j;

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


		vector<int> relations;
		//cout<< "les noeuds sont à "<<x<<" "<<y<<endl;
		if(type == 1 || type == 2){
			carte.seekg(1, ios::cur);
			carte>>nombre;
			if(nombre>nbNoeuds){cout<<"Erreur dans les noeuds"<<endl; return false;}
			relations.push_back(nombre);

			carte.seekg(1, ios::cur);
			carte>>mot;
			if(mot!=";"){cout<<"Erreur dans la fin de la ligne"<< j <<endl; return false;}

		}

		if(type == 3){
			carte.seekg(1, ios::cur);
			carte>>nombre;
			if(nombre>nbNoeuds || nombre<0 ){printf("Erreur dans les noeudscligne %d\n", j); return false;}
			relations.push_back(nombre);

			carte.seekg(1, ios::cur);
			carte>>nombre;
			if(nombre>nbNoeuds || nombre<0 ){printf("Erreur dans les noeuds ligne %d\n", j); return false;}
			relations.push_back(nombre);

			carte.seekg(1, ios::cur);
			carte>>mot;
			if(mot!=";"){
				
				carte>>nombre;
				if(nombre>nbNoeuds || nombre<0 ){printf("Erreur dans les noeuds ligne %d\n", j); return false;}

				carte.seekg(1, ios::cur);
				carte>>mot;
				if(mot!=";"){cout<<"Erreur dans la fin de la ligne"<< j <<endl; return false;}
			}

		}

		if(type == 4){
			carte.seekg(1, ios::cur);
			carte>>nombre;
			if(nombre>nbNoeuds || nombre<0 ){printf("Erreur dans les noeuds ligne %d\n", j); return false;}
			relations.push_back(nombre);

			carte.seekg(1, ios::cur);
			carte>>nombre;
			if(nombre>nbNoeuds || nombre<0 ){printf("Erreur dans les noeuds ligne %d\n", j); return false;}
			relations.push_back(nombre);

			carte.seekg(1, ios::cur);
			carte>>nombre;
			if(nombre>nbNoeuds || nombre<0 ){printf("Erreur dans les noeuds ligne %d\n", j); return false;}
			relations.push_back(nombre);

			carte.seekg(1, ios::cur);
			carte>>mot;
			if(mot!=";"){
				
				carte.seekg(-1, ios::cur);
				carte>>nombre;
				if(nombre>nbNoeuds || nombre<0 ){printf("Erreur dans les noeuds ligne %d\n", j); return false;}

				carte.seekg(1, ios::cur);
				carte>>mot;
				if(mot!=";"){cout<<"Erreur dans la fin de la ligne"<< j <<endl; return false;}
			}
		}

		Noeud noeud(j, type, x, y, relations);
		this->noeuds.push_back(noeud);
		getline(carte, ligne);

	}

	carte.close();
	return true;
}




bool Carte::verifChemin(string const nomCarte){
	ifstream carte(nomCarte.c_str());

	int dx, dy, p, x, y;
	int position;
	int width = 1800;

	vector<Noeud>::iterator noeud = this->noeuds.begin();


	//----------------------------------------------------------------------------------------------------
	//    Ceci n'est pas Bresenham, mais étant donné qu'on n'a que des chemins en angle droit, 
	//	  il est plus simple pour nous de faire ainsi 
	//----------------------------------------------------------------------------------------------------
	for (int i = 0;  i < this->noeuds.size(); i++){
		vector<int> relations = this->noeuds[i].getRel();
		for(int j  = 0 ; j < relations.size() ; j++){

			int sens = 1;
			dx = this->noeuds[i].getPositionX()-this->noeuds[relations[j]].getPositionX();
			dy = this->noeuds[i].getPositionY()-this->noeuds[relations[j]].getPositionY();

			if(dx == 0){
				int y0 = this->noeuds[i].getPositionY();
				int y1 = this->noeuds[relations[j]].getPositionY();
				if (y0 < y1) {sens = -1;}
				//printf("Le noeud %d est lié au noeud %d et ils sont alignés en x\n", i, this->noeuds[relations[j]].getId());
				bool isContructible = isConstructible(this->noeuds[i].getPositionX(), y1, 1800, 0);
				while(y1 != y0 && !isContructible){
					y1 += 1*sens;
					printf("Je vérifie le pixel %d, %d \n", this->noeuds[i].getPositionX(), y1);
					isContructible = isConstructible(this->noeuds[i].getPositionX(), y1, 1800, 0);
				}
				if(y1 != y0){
					printf("Zone constructible entre deux noeuds liés !\n");
					return false;
				}
				//cout<<"Le noeud "<< i <<" est lié au noeud "<< this->noeuds[relations[j]] <<" et ils sont alignés en x"<<endl;
			}

			if(dy == 0){
				//for( ; )
				int x0 = this->noeuds[i].getPositionX();
				int x1 = this->noeuds[relations[j]].getPositionX();
				if (x0 < x1) {sens = -1;}
				printf("Le noeud %d est lié au noeud %d et ils sont alignés en y\n", i, this->noeuds[relations[j]].getId());
				//cout<<"Le noeud "<< i <<" est lié au noeud "<< this->noeuds[relations[j]] <<" et ils sont alignés en y"<<endl;
				bool isContructible = isConstructible(x1, this->noeuds[i].getPositionY(), 1800, 0);
				while(x1 != x0 && !isContructible){
					x1 += 1*sens;
					printf("Je vérifie le pixel %d, %d \n", x1, this->noeuds[i].getPositionY());
					isContructible = isConstructible(x1, this->noeuds[i].getPositionY(), 1800, 0);
				}
				if(x1 != x0){
					printf("Zone constructible entre deux noeuds liés !\n");
					return false;
				}
			}
		}
	}
	printf("Tous les noeuds sont bien liés sur la carte\n");
	return true;


	//première tentative de bresenham
	// 	for(int i = 0; i <this->noeuds.size()-1 ; i++){
	// 		dx=this->noeuds[i+1].getPositionX()-this->noeuds[i].getPositionX();
	// 		dy=this->noeuds[i+1].getPositionY()-this->noeuds[i].getPositionY();
	// 		x = this->noeuds[i].getPositionX();
	// 		y = this->noeuds[i].getPositionY();
	// 		p=2*dy-dx;

	// 		while(x!=this->noeuds[i+1].getPositionX())
	// 		{
	// 			cout<<"je rentre dans while"<<endl;
	// 			position = width*3*(y-1)+x*3;

	// 			if(p>=0)
	// 			{	
	// 				for(int j = 0 ; j<3 ; j++){
	// 					cout<<x<<" "<<y<<endl;
	// 					cout<<position<<endl;
	// 					if(this->data[position+j+1]!=this->cheminColor[j]){
	// 						cout<<"Le chemin n'est pas constant !"<<endl;
	// 						return false;
	// 					}
	// 				}
	// 				y=y+1;
	// 				p=p+2*dy-2*dx;
	// 				cout<<x<<" "<<y<<endl;
	// 			}
	// 			else
	// 			{
	// 				for(int j = 0 ; j<3 ; j++){
	// 					if(this->data[position+j+1]!=this->cheminColor[j]){
	// 						cout<<"Le chemin n'est pas constant !"<<endl;
	// 						return false;
	// 					}
	// 				}
	// 				p=p+2*dy;
	// 				//cout<<x<<" "<<y<<endl;
	// 			}
	// 			x=x+1;
	// 		}
	// 	} 

	// }
	// cout<<"en fait les chemins ça va"<<endl;

}



bool Carte::isChemin(int x, int y, int width){
	int position = width*3*(y-1)+x*3;
	for(int i=0; i<3; i++){
		if(this->data[position+i+1]!=this->cheminColor[i]){
			return false;
		}
	}
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