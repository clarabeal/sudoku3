#include "TXT_Classique.h"
#include "TXT_PasAPas.h"

#include <iostream>
#include <stdlib.h>
#include <math.h>
using namespace std;

int main () {
	bool stop = false;
	while(!stop){
#ifdef _WIN32
		system("cls");
#else
		system("clear");
#endif
		int d, mode; 
		//verif que la dim de la grille a une racine
		do {
			cout << "||||||||||||||||||||||||||||||||||SUDOKU 3||||||||||||||||||||||||||||||||||" << endl;
			cout << "||                                                                        ||" << endl;
			cout << "||  Avec des grilles de quelle dimension voulez-vous jouer? (4, 9 ou 16)  ||" << endl;
			cout << "||   Une grille de taille superieur sera tres (tres) longue a generer)    ||" << endl;
			cout << "||                                                                        ||" << endl;
			cout << "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
			cout << "Votre choix: ";
			cin >> d;
		} while (((float)((float)sqrt(d) - (int)sqrt(d)) != 0.0) || d == 1);

		#ifdef _WIN32
			system("cls");
		#else
			system("clear");
		#endif
		do {
			cout << "||||||||||||||||||||||||||||||||||SUDOKU 3||||||||||||||||||||||||||||||||||" << endl;
			cout << "||                                                                        ||" << endl;
			cout << "||                       Selection d'un mode de Jeu                       ||" << endl;
			cout << "||                                                                        ||" << endl;
			cout << "|| 1: Mode de jeu classique, aucune aide et solution uniquement en fin de ||" << endl;
			cout << "||    partie.                                                             ||" << endl;
			cout << "||                                                                        ||" << endl;
			cout << "|| 2: Mode de jeu Pas a Pas, de nombreuses aides sont mises a disposition ||" << endl;
			cout << "||    pour vous aider a resoudre le sudoku.                               ||" << endl;
			cout << "||                                                                        ||" << endl;
			cout << "|| 3: Mode 1vs1, a tour de role, les deux joueurs doivent resoudre la     ||" << endl;
			cout << "||    meme grille. Le vainceur est celui qui l'a fini le plus rapidement. ||" << endl;
			cout << "||                                                                        ||" << endl;
			cout << "|| 4: Recommencer a partir d'une sauvegarde.                              ||" << endl;
			cout << "||                                                                        ||" << endl;
			cout << "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
			cout << "Votre choix: ";
			cin >> mode;
		} while (mode < 0 || mode > 4);

		if (mode == 1) {
			TXT_Classique partieTxt((unsigned char)d);
			partieTxt.boucle();
		}
		else if(mode == 2){
			TXT_PasAPas partieTxt((unsigned char)d);
			partieTxt.boucle();
		}
		else {
			cout << "Option indisponible pour le moment" << endl;
		}

		cout << endl << "Voulez-vous rejouer? | Oui: 1, Non: 0" << endl;
		cin >> mode;
		if (mode == 0) {
			stop = true;
		}
	}

	return 0;
}