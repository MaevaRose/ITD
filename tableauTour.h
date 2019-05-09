#include <iostream>
#include <string>
#include <vector>
#include "tour.h"

using namespace std;

void addToTabBlueTower(vector<TourBleue> &tabTourBleue, TourBleue tour);

void addToTabYellowTower(vector<TourJaune> &tabTourJaune, TourJaune tour);

void addToTabRedTower(vector<TourRouge> &tabTourRouge, TourRouge tour);

void addToTabGreenTower(vector<TourVerte> &tabTourVerte, TourVerte tour);

void printTab(vector<TourBleue> &tabTourBleue);

void drawAllTower(vector<TourBleue> &tabTourBleue, vector<TourJaune> &tabTourJaune, vector<TourRouge> &tabTourRouge, vector<TourVerte> &tabTourVerte, const unsigned int WINDOW_WIDTH, const unsigned int WINDOW_HEIGHT );