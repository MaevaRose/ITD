#include <iostream>
#include <string>
#include <vector>
#include "tableauTour.h"

using namespace std;

void addToTabTower(vector<TourBleue> tabTourBleue, TourBleue tour) {
	tabTourBleue.push_back(tour);
	printf("C'est dans tabTourBleue !\n");
}

void printTab(vector<TourBleue> tabTourBleue){

	vector<TourBleue>::iterator ptr;
	vector<TourBleue>::value_type t;


	//for (ptr = tabTourBleue.begin(); ptr < tabTourBleue.end(); ptr++){
		printf("sdvjbhoeqvb\n");
		
		int test = (*ptr).getPositionY();
		cout<<test<<endl;
	//}
}

void drawAllTower(vector<TourBleue> tabTourBleue, const unsigned int WINDOW_WIDTH, const unsigned int WINDOW_HEIGHT ) {
	vector<TourBleue>::iterator ptr;
	for (ptr = tabTourBleue.begin(); ptr < tabTourBleue.end(); ptr++){
		(*ptr).draw(WINDOW_WIDTH, WINDOW_HEIGHT);
		cout<<(*ptr).getPositionX()<<endl;
		cout<<(*ptr).getPositionY()<<endl;
	}
}