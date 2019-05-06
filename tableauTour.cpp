#include <iostream>
#include <string>
#include <vector>
#include "tableauTour.h"

using namespace std;

void addToTabTower(vector<TourBleue*> tabTourBleue, TourBleue tour) {
	tabTourBleue.push_back(&tour);
	printf("C'est dans tabTourBleue !\n");
	tabTourBleue[0]->afficherEtat();
}

void printTab(vector<TourBleue*> tabTourBleue){

	vector<TourBleue*>::iterator ptr;
	vector<TourBleue*>::value_type t;


	//for (ptr = tabTourBleue.begin(); ptr < tabTourBleue.end(); ptr++){
		printf("sdvjbhoeqvb\n");
		//cout<<tabTourBleue[0]<<endl;
	//}
}

void drawAllTower(vector<TourBleue*> tabTourBleue, const unsigned int WINDOW_WIDTH, const unsigned int WINDOW_HEIGHT ) {
	//cout<<"hello"<<endl;
	//tabTourBleue[0]->draw(WINDOW_WIDTH, WINDOW_HEIGHT);
	if(tabTourBleue.size()>0){
		for (int i = 0; i < tabTourBleue.size(); i++){
		tabTourBleue[i]->draw(WINDOW_WIDTH, WINDOW_HEIGHT);
		printf("(ça draw ou pas)\n");
		}
	}
	else{
		cout<<"y'a aucune tour wesh"<<endl;
	}
	
}