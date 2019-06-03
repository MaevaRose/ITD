#include <iostream>
#include <string>
#include <vector>
#include "../include/grapheNoeuds.h"
//#include "noeud.h"


using namespace std;

void addConnexion (vector<vector<int>> &grapheNoeuds, int idNoeud1, int idNoeud2) {
	grapheNoeuds[idNoeud1].push_back(idNoeud2);
}


void constructGraphes (vector<Noeud> noeuds, vector<vector<int>> &grapheNoeuds, vector<vector<int>> &tabPoids, vector<vector<int>> &posNoeuds) {
	for (int i=0; i<noeuds.size(); i++) {
		grapheNoeuds.push_back(vector<int>(1,noeuds[i].getRel()[0]));
		//printf("je remplis la premiere couche de poids\n");
		tabPoids.push_back(vector<int>(1,0));
		posNoeuds.push_back(vector<int>(1,noeuds[i].getPositionX()));
		posNoeuds[i].push_back(noeuds[i].getPositionY());
		//printf("posNoeuds : %d, %d\n", posNoeuds[i][0], posNoeuds[i][0]);

		for (int j=1; j<noeuds[i].getRel().size(); j++) {
			grapheNoeuds[i].push_back(noeuds[i].getRel()[j]);

			//printf("je vais remplir poids\n");
			tabPoids[i].push_back(0);
		}
	}
}


// void visit(vector<vector<int>> &grapheNoeuds, int idNoeud, vector<bool> &seen, vector<int> &distances, vector<vector<int>> &tabPoids) {
// 	printf("Je visite\n");
// 	seen[idNoeud]=true;
// 	int size = grapheNoeuds[idNoeud].size();
// 	for (int i=0; i<size; i++) {
// 		int idNoeud2 = grapheNoeuds[idNoeud][i];
// 		int newDist = tabPoids[idNoeud][i] + distances[idNoeud];
// 		printf("newdist = %d\n", newDist);
// 		if (newDist <= distances[idNoeud2]) {
// 			distances[idNoeud2] = newDist;
// 		}
// 	} 
// }


// int findMin  (vector<bool> &seen, vector<int> &distances) {
// 	int size = seen.size();
// 	int bestId = -1;
// 	int bestDist = 10000000;
// 	for (int i=0; i<size; i++) {
// 		if (!seen[i] && distances[i]<bestDist) {
// 			bestId = i;
// 			bestDist = distances[i];
// 		}
// 	}
// 	return bestId;
// }



// vector<int> dijkstra(vector<vector<int>> &grapheNoeuds, vector<vector<int>> &tabPoids, int &idNoeudStart) {
// 	printf("DIJKSTRA\n");
// 	int size = grapheNoeuds.size();
// 	vector<int> distances;
// 	for (int i=0; i<size; i++) {
// 		distances.push_back(1000000);
// 	}
// 	vector<bool> seen;
// 	for (int i=0; i<size; i++) {
// 		seen.push_back(false);
// 	}
// 	int idNoeud = idNoeudStart;
// 	printf("%d\n",idNoeud);
// 	while (idNoeud!=-1) {
// 		visit(grapheNoeuds, idNoeud, seen, distances, tabPoids);
// 		idNoeud = findMin(seen, distances);
// 		//printf("%d\n",idNoeud);
// 	}
// 	return distances;
// }


// int findMinInDist (vector<int> distances) {
// 	int min = 1000000;
// 	int size = distances.size();
// 	for (int i=0; i<size; i++) {
// 		if (distances[i]<min) {
// 			min = distances[i];
// 		}
// 	}
// 	return min;
// }

// vector<vector<int>> creerGrapheTest() {
	
// 	vector<vector<int>> grapheNoeuds;

// 	grapheNoeuds.push_back(vector<int>(1,1));
// 	grapheNoeuds.push_back(vector<int>(1,0));
// 	grapheNoeuds.push_back(vector<int>(1,0));
// 	grapheNoeuds.push_back(vector<int>(1,0));
// 	grapheNoeuds.push_back(vector<int>(1,2));
// 	grapheNoeuds.push_back(vector<int>(1,2));
// 	grapheNoeuds.push_back(vector<int>(1,3));

// 	printf("J'ai mis la premiere couche\n");

// 	grapheNoeuds[0].push_back(2);
// 	grapheNoeuds[0].push_back(3);
// 	grapheNoeuds[2].push_back(4);
// 	grapheNoeuds[2].push_back(5);
// 	grapheNoeuds[3].push_back(6);
// 	grapheNoeuds[4].push_back(6);
// 	grapheNoeuds[5].push_back(6);
// 	grapheNoeuds[6].push_back(4);
// 	grapheNoeuds[6].push_back(5);

// 	printf("J'ai finis de créer ton tableau\n");
// 	return grapheNoeuds;
// }


// vector<vector<int>> creerTabTest() {
// 	vector<vector<int>> tabPoids;

// 	tabPoids.push_back(vector<int>(1,10));
// 	tabPoids.push_back(vector<int>(1,10));   
// 	tabPoids.push_back(vector<int>(1,2));   
// 	tabPoids.push_back(vector<int>(1,4));   
// 	tabPoids.push_back(vector<int>(1,6));   
// 	tabPoids.push_back(vector<int>(1,1));   
// 	tabPoids.push_back(vector<int>(1,10));  

// 	tabPoids[0].push_back(2);
// 	tabPoids[0].push_back(4);
// 	tabPoids[2].push_back(6);
// 	tabPoids[2].push_back(1);
// 	tabPoids[3].push_back(10);
// 	tabPoids[4].push_back(2);
// 	tabPoids[5].push_back(4);
// 	tabPoids[6].push_back(2);
// 	tabPoids[6].push_back(4);


// 	return tabPoids;
// }


// vector<vector<int>> creerGrapheTest2() {
	
// 	vector<vector<int>> grapheNoeuds;

// 	grapheNoeuds.push_back(vector<int>(1,1));
// 	grapheNoeuds.push_back(vector<int>(1,0));
// 	grapheNoeuds.push_back(vector<int>(1,1));
// 	grapheNoeuds.push_back(vector<int>(1,2));


// 	printf("J'ai mis la premiere couche\n");

// 	grapheNoeuds[1].push_back(2);
// 	grapheNoeuds[2].push_back(3);

// 	printf("J'ai finis de créer ton tableau\n");
// 	return grapheNoeuds;
// }


// vector<vector<int>> creerTabTest2() {
// 	vector<vector<int>> tabPoids;

// 	tabPoids.push_back(vector<int>(1,0));
// 	tabPoids.push_back(vector<int>(2,0));   
// 	tabPoids.push_back(vector<int>(2,0));   
// 	tabPoids.push_back(vector<int>(1,0));   
 

// 	return tabPoids;
// }


// vector<vector<int>> creerPosNoeud() {
// 	vector<vector<int>> posNoeuds;

// 	posNoeuds.push_back(vector<int>(1,1625));
// 	posNoeuds.push_back(vector<int>(1,825));   
// 	posNoeuds.push_back(vector<int>(1,825));   
// 	posNoeuds.push_back(vector<int>(1,225)); 

// 	posNoeuds[0].push_back(725);
// 	posNoeuds[1].push_back(725);
// 	posNoeuds[2].push_back(275);
// 	posNoeuds[3].push_back(275);  
 

// 	return posNoeuds;
// }


// void afficheTabPoids(vector<vector<int>> tabPoids) {
// 	for (int i=0; i<tabPoids.size(); i++) {
// 		printf("Le noeud %d est : %d\n", i+1, tabPoids[i]);
// 	}
// }


int meilleurChemin(vector<vector<int>> &grapheNoeuds, vector<vector<int>> tabPoids, vector<int> &utilise, int idNoeud, int end) {
	/*for (int i=0; i<utilise.size(); i++) {
		printf("la vlaeur %d de Utilise est %d\n", i, utilise[i]);
	}*/

	int min = 1000000;
	int indice = -1;

	for (int i=1; i<grapheNoeuds[idNoeud].size(); i++) {
		if (grapheNoeuds[idNoeud][i] == end) {
			indice = i;
			return grapheNoeuds[idNoeud][indice];
		}

		else if ((tabPoids[idNoeud][i] < min) && (utilise[grapheNoeuds[idNoeud][i]] == 0)) {
			//printf("je suis dans le if\n");
			min = tabPoids[idNoeud][i];
			indice = i;
		}
	}

	if (indice == -1) {
		printf("il y a pas de possibilité\n");
		return indice;
	}
	else {
		//printf("Le meilleur choix est %d\n", grapheNoeuds[idNoeud][indice]);
		return grapheNoeuds[idNoeud][indice];
	}
}


vector<int> calculCheminMonstre (vector<vector<int>> &grapheNoeuds, vector<vector<int>> &tabPoids, int start, int end) {
	
	printf("je commence le calcul.\n");
	vector<int> utilise (grapheNoeuds.size(), 0);
	utilise[start] = 1;
	vector<int> chemin (1, start);
	int i=start;
	vector<int> histoVisite;

	while (i != end) {
		histoVisite.push_back(i);
		if(grapheNoeuds[i].size() == 1) {
			if (utilise[grapheNoeuds[i][0]] == 1) {
				
				histoVisite.pop_back();
				i = histoVisite[histoVisite.size()-1];
				histoVisite.pop_back();
				
				printf("LE NOEUD SOLO EST UTILISE \n");
			} 
			else {
				chemin.push_back(grapheNoeuds[i][0]);
				utilise[grapheNoeuds[i][0]] = 1;
				i=grapheNoeuds[i][0];
				printf("il n'y avait ici qu'une possibilité\n");
			}
		}
		else {
			int meilleurChoix = meilleurChemin(grapheNoeuds, tabPoids, utilise, i, end);
			if (meilleurChoix == -1) {
				//printf("boucle entre %d \n", histoVisite[histoVisite.size()-1]);
				histoVisite.pop_back();
				i = histoVisite[histoVisite.size()-1];
				histoVisite.pop_back();
			}

			else {
				i = meilleurChoix;
				utilise[meilleurChoix] = 1;
				chemin.push_back(meilleurChoix);
				//printf("j'ai lancé meilleurChemin et j'ai sortis la valeur %d\n", meilleurChoix);
			}
		}
	}
	return chemin;
}


void afficheChemin(vector<int> chemin) {
	for (int i=0; i<chemin.size(); i++) {
		printf("Le noeud %d est : %d\n", i+1, chemin[i]);
	}
}