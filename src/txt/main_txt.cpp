#include "../core/Sauvegarde.h"
#include "TXT_Classique.h"
#include "TXT_PasAPas.h"
#include "TXT_1vs1.h"
#include <iostream>
#include <stdlib.h>
#include <math.h>
using namespace std;

void termClear();
int selectionSave(gestSauvegarde& gest);
int selectionMenu();
int selectionDim();

int main () {

	bool stop = false;

	while(!stop){
		
		int mode = selectionMenu();
		if (mode == 1) {
			int d = selectionDim();
			TXT_Classique partieTxt((unsigned char)d);
			partieTxt.boucle();
			mode = 0;

		}
		else if(mode == 2){
			int d = selectionDim();
			TXT_PasAPas partieTxt((unsigned char)d);
			partieTxt.boucle();
			mode = 0;
		}
		else if(mode == 3) {
			int d = selectionDim();
			TXT_1vs1 partieTxt((unsigned char)d);
			partieTxt.boucle();
			mode = 0;
		}
		else if (mode == 4) {
			termClear();
			gestSauvegarde gestionnaireSauvegarde("../data/saves/", "data/saves/");
			int saveId = selectionSave(gestionnaireSauvegarde);
			if (saveId != -1) {
				InfoSauvegarde infoSurLaPartie = gestionnaireSauvegarde.getInfoSauvegarde(saveId);
				Grille g_sol(infoSurLaPartie.tailleGrille);
				Grille g_orig(infoSurLaPartie.tailleGrille);
				Grille g_jeu(infoSurLaPartie.tailleGrille);
				gestionnaireSauvegarde.loadFromFile(saveId, g_sol, g_orig, g_jeu);
				if (infoSurLaPartie.modeJeu == 1) {
					TXT_Classique partieTxt((unsigned char)infoSurLaPartie.tailleGrille, infoSurLaPartie.id, infoSurLaPartie.chrono, g_sol, g_orig, g_jeu);
					partieTxt.boucle();
				}
				else if (infoSurLaPartie.modeJeu == 2) {
					TXT_PasAPas partieTxt((unsigned char)infoSurLaPartie.tailleGrille, infoSurLaPartie.id, infoSurLaPartie.chrono, g_sol, g_orig, g_jeu);
					partieTxt.boucle();
				}
				else {
					cout << "Le mode de jeu de cette grille est invalide ou ne pas etre repris a partir d'une sauvegarde" << endl;
				}
			}
			else mode = 4;
		}
		else {
			cout << "Option indisponible pour le moment" << endl;
		}
		if (mode == 0) {
			cout << endl << "Voulez-vous rejouer? | Oui: 1, Non: 0" << endl;
			cin >> mode;
			if (mode == 0) {
				stop = true;
			}
		}
	}

	return 0;
}

void termClear() {
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
}

int selectionDim() {
	int dim;
	termClear();

	do {
		cout << "||||||||||||||||||||||||||||||||||SUDOKU 3||||||||||||||||||||||||||||||||||" << endl;
		cout << "||                                                                        ||" << endl;
		cout << "||  Avec une grille de quelle dimension voulez-vous jouer? (4, 9 ou 16)   ||" << endl;
		cout << "||   Une grille de taille superieur sera tres (tres) longue a generer     ||" << endl;
		cout << "||                                                                        ||" << endl;
		cout << "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
		cout << "Votre choix: ";
		cin >> dim;
	} while (((float)((float)sqrt(dim) - (int)sqrt(dim)) != 0.0) || dim == 1);
	termClear();
	return dim;
	

}

int selectionMenu() {
	int mode;
	termClear();

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
		cout << "||    meme grille. Le vainqueur est celui qui l'a fini le plus rapidement.||" << endl;
		cout << "||                                                                        ||" << endl;
		cout << "|| 4: Recommencer a partir d'une sauvegarde.                              ||" << endl;
		cout << "||                                                                        ||" << endl;
		cout << "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
		cout << "Votre choix: ";
		cin >> mode;
	} while (mode < 0 || mode > 4);
	termClear();
	return mode;
}

int selectionSave(gestSauvegarde &gest) {
	int selectId = 0;
	int selectAction = 0;

	unsigned char convertIntToChar = 0;
	string ligne;
	do {
		do {
			termClear();
			cout << "||||||||||||||||||||||||||||||||||SUDOKU 3||||||||||||||||||||||||||||||||||" << endl;
			cout << "||                                                                        ||" << endl;
			cout << "||  Id | Nom | Taille de la grille                                        ||" << endl;
			cout << "||                                                                        ||" << endl;
			for (unsigned int i = 0; i < gest.nbSauvegarde; i++) {
				int id = gest.listeSauvegarde[i].id;
				int tailleGrille = gest.listeSauvegarde[i].tailleGrille;
				string name = gest.listeSauvegarde[i].name;
				ligne = to_string(id) + "  | " + name + " | " + to_string(tailleGrille) + "*" + to_string(tailleGrille);
				cout << "||  " << ligne;
				for (long unsigned int i = 0; i < 68 - ligne.length(); i++) { cout << " "; }
				cout << "  ||" << endl;
			}
			cout << "||                                                                        ||" << endl;
			cout << "|| -1: Retour                                                             ||" << endl;
			cout << "||                                                                        ||" << endl;
			cout << "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
			cout << "Entrer l'id de la sauvegarde: ";
			cin >> selectId;
			if (selectId != -1) convertIntToChar = selectId;
		} while (!gest.valideId(convertIntToChar) && selectId != -1);
		
		if (selectId != -1) {
			InfoSauvegarde& sauvegardeSelectionne = gest.getInfoSauvegarde(selectId);
			termClear();
			do {
				cout << "||||||||||||||||||||||||||||||||||SUDOKU 3||||||||||||||||||||||||||||||||||" << endl;
				cout << "||                                                                        ||" << endl;
				cout << "||                       Informations sur la partie                       ||" << endl;
				cout << "||                                                                        ||" << endl;

				ligne = "id: " + to_string(sauvegardeSelectionne.id); cout << "||  " << ligne; for (long unsigned int i = 0; i < 68 - ligne.length(); i++) { cout << " "; } cout << "  ||" << endl;
				ligne = "nom: " + sauvegardeSelectionne.name; cout << "||  " << ligne; for (long unsigned int i = 0; i < 68 - ligne.length(); i++) { cout << " "; } cout << "  ||" << endl;
				ligne = "Mode de Jeu: " + to_string(sauvegardeSelectionne.modeJeu);
				if (sauvegardeSelectionne.modeJeu == 1) {
					ligne += " (Classique)";
				}
				else if (sauvegardeSelectionne.modeJeu == 2) {
					ligne += " (Pas a Pas)";
				}
				else if (sauvegardeSelectionne.modeJeu == 3) {
					ligne += " (1 VS 1)";
				}
				else {
					ligne += " (erreur)";
				}
				cout << "||  " << ligne; for (long unsigned int i = 0; i < 68 - ligne.length(); i++) { cout << " "; } cout << "  ||" << endl;
					ligne = "Chrono: " + to_string((sauvegardeSelectionne.chrono / 1000 / 60 / 60)) + "h " + to_string((sauvegardeSelectionne.chrono / 1000 / 60) % 60) + "m " + to_string((sauvegardeSelectionne.chrono / 1000)) + "s " + to_string((sauvegardeSelectionne.chrono) % 1000) + "ms";
				cout << "||  " << ligne; for (long unsigned int i = 0; i < 68 - ligne.length(); i++) { cout << " "; } cout << "  ||" << endl;
				cout << "||                                                                        ||" << endl;
				cout << "|| 1: Charger cette sauvegarde                                            ||" << endl;
				cout << "|| 2: Supprimer cette sauvegarde                                          ||" << endl;
				cout << "|| 3: Revenir a la liste des sauvegardes                                  ||" << endl;
				cout << "||                                                                        ||" << endl;
				cout << "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
				cout << "Votre choix: ";
				cin >> selectAction;

			} while (selectAction < 1 || selectAction > 3);
			if (selectAction == 2) {
				gest.supprimerSauvegarde(selectId);
			}
		}
	} while (selectAction != 1 && selectId != -1);

	termClear();
	return (selectId);
}