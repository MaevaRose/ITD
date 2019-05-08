#include <iostream>
#include <string>
#include <vector>
#include "tableauTour.h"

using namespace std;

void addToTabTower(vector<TourBleue> &tabTourBleue, TourBleue tour) {
	vector<TourBleue>::iterator ptr;
	tabTourBleue.push_back(tour);
	printf("C'est dans tabTourBleue !\n");
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

void drawAllTower(vector<TourBleue> &tabTourBleue, const unsigned int WINDOW_WIDTH, const unsigned int WINDOW_HEIGHT ) {
	//cout<<"hello"<<endl;
	//tabTourBleue[0]->draw(WINDOW_WIDTH, WINDOW_HEIGHT);
	vector<TourBleue>::iterator ptr=tabTourBleue.begin();
	if(tabTourBleue.size()>0){
		int i=0;
		for (ptr = tabTourBleue.begin(); ptr < tabTourBleue.end(); ptr++){
			i++;
			//for (int i = 0; i < tabTourBleue.size(); i++){
			(*ptr).draw(WINDOW_WIDTH, WINDOW_HEIGHT);
			//printf("tour %d :\n", i);
			//(*ptr).afficherEtat();
			
		}
		//printf("Il y a %d tours\n", tabTourBleue.size());
	}
	else{
		//cout<<"y'a aucune tour wesh"<<endl;
	}
	
}