#include <iostream>
#include <string>
#include <vector>
#include "noeud.h"

using namespace std;


void addConnexion (vector<vector<int>> &grapheNoeuds, int idNoeud1, int idNoeud2);

void constructGraphes (vector<Noeud> noeuds, vector<vector<int>> &grapheNoeuds, vector<vector<int>> &tabPoids, vector<vector<int>> &posNoeuds);

void visit(vector<vector<int>> &grapheNoeuds, int idNoeud, vector<bool> &seen, vector<int> &distances, vector<vector<int>> &tabPoids);

int findMin(vector<bool> &seen, vector<int> &distances);

int findMin(vector<bool> &seen, vector<int> &distances);

vector<int> dijkstra(vector<vector<int>> &grapheNoeuds, vector<vector<int>> &tabPoids, int &idNoeudStart);

int findMinInDist (vector<int> distances);

vector<vector<int>> creerGrapheTest();

vector<vector<int>> creerTabTest();

vector<vector<int>> creerGrapheTest2();

vector<vector<int>> creerTabTest2();

vector<vector<int>> creerPosNoeud();

int meilleurChemin(vector<vector<int>> &grapheNoeuds, vector<vector<int>> tabPoids, vector<int> &utilise, int idNoeud, int end);

vector<int> calculCheminMonstre(vector<vector<int>> &grapheNoeuds, vector<vector<int>> &tabPoids, int start, int end);

void afficheChemin(vector<int> chemin);