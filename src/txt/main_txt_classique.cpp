#include "TXT_Classique.h"
#include <iostream>
#include <stdlib.h>
#include <math.h>
using namespace std;

int main () {
	bool stop = false;
	while(!stop){
		int d, mode; 
		//faire verification que ce nombre à une racine
		do {
			cout << "Avec des grilles de quel dimension voulez vous jouer?(4, 9 ou 16 une grille de taille superieur serat tres (tres) longue a generer)" << endl;
			cin >> d;
		} while (((float)((float)sqrt(d) - (int)sqrt(d)) != 0.0) || d == 1);

		cout << "Quel mode de jeu voulez vous? | Mode de jeu classique: 1, Mode de Jeu pas a pas: 2, mode de jeu chrono 1vs 1: 3" << endl;
		cin >> mode;
		if (mode == 1) {
			TXT_Classique partieTxt((unsigned char)d);
			partieTxt.boucle();
		}
		else {
			cout << "Mode de jeu indisponible" << endl;
		}

		cout << endl << "Voulez vous rejouer? | Oui: 1, Non:0" << endl;
		cin >> mode;
		if (mode == 0) {
			stop = true;
		}
	}

	return 0;
}