#include "TXT_Classique.h"
#include "TXT_PasAPas.h"

#include <iostream>
#include <stdlib.h>
#include <math.h>
using namespace std;

int main () {
	bool stop = false;
	while(!stop){
		int d, mode; 
		//verif que la dim de la grille a une racine
		do {
			cout << "Avec des grilles de quelle dimension voulez-vous jouer?(4, 9 ou 16 une grille de taille superieur sera tres (tres) longue a generer)" << endl;
			cin >> d;
		} while (((float)((float)sqrt(d) - (int)sqrt(d)) != 0.0) || d == 1);

		cout << "Quel mode de jeu voulez-vous? | Mode de jeu classique: 1, Mode de Jeu pas a pas: 2, Mode de jeu chrono 1 vs 1: 3" << endl;
		cin >> mode;
		if (mode == 1) {
			TXT_Classique partieTxt((unsigned char)d);
			partieTxt.boucle();
		}
		else {
			//cout << "Mode de jeu en debug" << endl;

			TXT_PasAPas partieTxt((unsigned char)d);
			partieTxt.boucle();
			//partieTxt.boucleTest();
		}

		cout << endl << "Voulez-vous rejouer? | Oui: 1, Non: 0" << endl;
		cin >> mode;
		if (mode == 0) {
			stop = true;
		}
	}

	return 0;
}