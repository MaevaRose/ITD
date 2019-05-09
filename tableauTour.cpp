#include <iostream>
#include <string>
#include <vector>
#include "tableauTour.h"

using namespace std;

void addToTabBlueTower(vector<TourBleue> &tabTourBleue, TourBleue tour) {
	//vector<TourBleue>::iterator ptr;
	tabTourBleue.push_back(tour);
	printf("C'est dans tabTourBleue !\n");
	//(*ptr).afficherEtat();
}

void addToTabYellowTower(vector<TourJaune> &tabTourJaune, TourJaune tour) {
	//vector<TourBleue>::iterator ptr;
	tabTourJaune.push_back(tour);
	printf("C'est dans tabTourJaune !\n");
	//(*ptr).afficherEtat();
}

void addToTabRedTower(vector<TourRouge> &tabTourRouge, TourRouge tour) {
	//vector<TourBleue>::iterator ptr;
	tabTourRouge.push_back(tour);
	printf("C'est dans tabTourRouge !\n");
	//(*ptr).afficherEtat();
}

void addToTabGreenTower(vector<TourVerte> &tabTourVerte, TourVerte tour) {
	//vector<TourBleue>::iterator ptr;
	tabTourVerte.push_back(tour);
	printf("C'est dans tabTourVerte !\n");
	//(*ptr).afficherEtat();
}

void printTab(vector<TourBleue> &tabTourBleue){

	vector<TourBleue>::iterator ptr;
	vector<TourBleue>::value_type t;


	//for (ptr = tabTourBleue.begin(); ptr < tabTourBleue.end(); ptr++){
		printf("sdvjbhoeqvb\n");
		//cout<<tabTourBleue[0]<<endl;
	//}
}

void drawAllTower(vector<TourBleue> &tabTourBleue, vector<TourJaune> &tabTourJaune, vector<TourRouge> &tabTourRouge, vector<TourVerte> &tabTourVerte, const unsigned int WINDOW_WIDTH, const unsigned int WINDOW_HEIGHT ) {
	//cout<<"hello"<<endl;
	//tabTourBleue[0]->draw(WINDOW_WIDTH, WINDOW_HEIGHT);
	vector<TourBleue>::iterator bleu=tabTourBleue.begin();
	vector<TourJaune>::iterator jaune=tabTourJaune.begin();
	vector<TourRouge>::iterator rouge=tabTourRouge.begin();
	vector<TourVerte>::iterator vert=tabTourVerte.begin();
	if(tabTourBleue.size()>0){
		int i=0;
		for (bleu = tabTourBleue.begin(); bleu < tabTourBleue.end(); bleu++){
			// i++;
			//for (int i = 0; i < tabTourBleue.size(); i++){
			(*bleu).draw(WINDOW_WIDTH, WINDOW_HEIGHT);
			//printf("tour %d :\n", i);
			//(*ptr).afficherEtat();
			
		}
	}
	if(tabTourRouge.size()>0){
		for (rouge = tabTourRouge.begin(); rouge < tabTourRouge.end(); rouge++){
			// i++;
			//for (int i = 0; i < tabTourBleue.size(); i++){
			(*rouge).draw(WINDOW_WIDTH, WINDOW_HEIGHT);
			//printf("tour %d :\n", i);
			//(*ptr).afficherEtat();
			
		}
	}
	if(tabTourJaune.size()>0){
		for (jaune = tabTourJaune.begin(); jaune < tabTourJaune.end(); jaune++){
			// i++;
			//for (int i = 0; i < tabTourJaune.size(); i++){
			(*jaune).draw(WINDOW_WIDTH, WINDOW_HEIGHT);
			//printf("tour %d :\n", i);
			//(*ptr).afficherEtat();
			
		}
	}
	if(tabTourVerte.size()>0){
		for (vert = tabTourVerte.begin(); vert < tabTourVerte.end(); vert++){
			// i++;
			//for (int i = 0; i < tabTourVerte.size(); i++){
			(*vert).draw(WINDOW_WIDTH, WINDOW_HEIGHT);
			//printf("tour %d :\n", i);
			//(*ptr).afficherEtat();
			
		}
		//printf("Il y a %d tours\n", tabTourBleue.size());
	}
	else{
		//cout<<"y'a aucune tour wesh"<<endl;
	}
	
}