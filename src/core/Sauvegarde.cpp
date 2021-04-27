#include "Sauvegarde.h"

#include <fstream>
#include <string>
#include <stdio.h>
#include <cassert>

gestSauvegarde::gestSauvegarde(string emplacement, string emplacement2)
{
	listeSauvegarde = nullptr;
	cheminDossier = emplacement;
	if (!updateListe()) {
		cheminDossier = emplacement2;
	}
	assert(updateListe());

}

bool gestSauvegarde::updateListe()
{
	ifstream fichier;
	fichier.open(cheminDossier + "indexParties.txt", ios::in);
	if (fichier.is_open()) {
		//cout << "index des sauvegarde ouvert a avec succes" << endl;
		fichier >> nbSauvegarde;
		fichier >> maxId;
		maxId = 0;
		cout << nbSauvegarde << " sauvegardes ont ete trouves" << endl;
		listeSauvegarde = new InfoSauvegarde[nbSauvegarde];
		for (unsigned int i = 0; i < nbSauvegarde; i++) {
			fichier >> listeSauvegarde[i].id >> listeSauvegarde[i].name >> listeSauvegarde[i].modeJeu >> listeSauvegarde[i].tailleGrille >> listeSauvegarde[i].chrono;
			if (listeSauvegarde[i].id > maxId) maxId = listeSauvegarde[i].id;
		}
		fichier.close();
		return true;
	}
	else {
		listeSauvegarde = nullptr;
		fichier.close();

		return false;
		
	}
	return false;

}

gestSauvegarde::~gestSauvegarde()
{
	delete[] listeSauvegarde;
}

InfoSauvegarde& gestSauvegarde::getInfoSauvegarde(unsigned char id) const {
	for (unsigned int i = 0; i < nbSauvegarde; i++) {
		if (listeSauvegarde[i].id == id) {
			return listeSauvegarde[i];
		}
	}
	assert(false);
}

bool gestSauvegarde::valideId(unsigned char id) const {
	for (unsigned int i = 0; i < nbSauvegarde; i++) {
		if (listeSauvegarde[i].id == id) {
			return true;
		}
	}
	return false;
}

void gestSauvegarde::loadFromFile(unsigned int id, Grille& g_sol, Grille& g_orig, Grille& g_jeu, Grille* grilleJ1, Grille* grilleJ2, unsigned long int* chronoJ1, unsigned long int* chronoJ2, int *nbErrJ1, int *nbErrj2, bool *stopJ1, bool *stopJ2)
{
	ifstream fichier;
	InfoSauvegarde& infoSurLaSauvegarde = getInfoSauvegarde(id);
	cout << "Id: " << id << endl;
	assert(infoSurLaSauvegarde.tailleGrille == g_sol.dim && infoSurLaSauvegarde.tailleGrille == g_jeu.dim && infoSurLaSauvegarde.tailleGrille == g_orig.dim);// on verifie que les grilles fournit soit de la bonne taille
	fichier.open(cheminDossier + to_string(id) + ".sudokujeu", ios::in);
	if (fichier.is_open()) {
		unsigned char dimGrille = infoSurLaSauvegarde.tailleGrille;
		int val;
		unsigned char conv;
		cout << "debut du chargement des grilles" << endl;
		cout << (int)g_sol.dim << endl;
		//chargement des valeurs
		for (int l = 0; l < dimGrille; l++) {
			for (int c = 0; c < dimGrille; c++) {
				fichier >> val;
				conv = (unsigned char)val;
				g_sol.grille.getCase(l, c).setVal(conv);
			}
		}
		for (int l = 0; l < dimGrille; l++) {
			for (int c = 0; c < dimGrille; c++) {
				fichier >> val;
				conv = (unsigned char)val;
				g_orig.grille.getCase(l, c).setVal(conv);
			}
		}
		for (int l = 0; l < dimGrille; l++) {
			for (int c = 0; c < dimGrille; c++) {
				fichier >> val;
				conv = (unsigned char)val;
				g_jeu.grille.getCase(l, c).setVal(conv);
			}
		}
		//chargement des modifiables
		bool valMod;
		for (int l = 0; l < dimGrille; l++) {
			for (int c = 0; c < dimGrille; c++) {
				fichier >> valMod;
				g_sol.grille.getCase(l, c).modifiable = valMod;
			}
		}
		for (int l = 0; l < dimGrille; l++) {
			for (int c = 0; c < dimGrille; c++) {
				fichier >> valMod;
				g_orig.grille.getCase(l, c).modifiable = valMod;
			}
		}
		for (int l = 0; l < dimGrille; l++) {
			for (int c = 0; c < dimGrille; c++) {
				fichier >> valMod;
				g_jeu.grille.getCase(l, c).modifiable = valMod;
			}
		}
		//chargement des etat
		for (int l = 0; l < dimGrille; l++) {
			for (int c = 0; c < dimGrille; c++) {
				fichier >> val;
				conv = (unsigned char)val;
				g_sol.grille.getCase(l, c).etat = conv;
			}
		}
		for (int l = 0; l < dimGrille; l++) {
			for (int c = 0; c < dimGrille; c++) {
				fichier >> val;
				conv = (unsigned char)val;
				g_orig.grille.getCase(l, c).etat = conv;
			}
		}
		for (int l = 0; l < dimGrille; l++) {
			for (int c = 0; c < dimGrille; c++) {
				fichier >> val;
				conv = (unsigned char)val;
				g_jeu.grille.getCase(l, c).etat = conv;
			}
		}
		
		if (infoSurLaSauvegarde.modeJeu == 3) {//info pour les mode pas a pas
			//chargement valeur grille j1
			for (int l = 0; l < dimGrille; l++) {
				for (int c = 0; c < dimGrille; c++) {
					fichier >> val;
					conv = (unsigned char)val;
					grilleJ1->grille.getCase(l, c).setVal(conv);
				}
			}
			//chargement valeur grille j2
			for (int l = 0; l < dimGrille; l++) {
				for (int c = 0; c < dimGrille; c++) {
					fichier >> val;
					conv = (unsigned char)val;
					grilleJ2->grille.getCase(l, c).setVal(conv);
				}
			}
			//chargement modifiable grille j1
			bool valMod;
			for (int l = 0; l < dimGrille; l++) {
				for (int c = 0; c < dimGrille; c++) {
					fichier >> valMod;
					grilleJ1->grille.getCase(l, c).modifiable = valMod;
				}
			}
			//chargement modifiable grille j2
			for (int l = 0; l < dimGrille; l++) {
				for (int c = 0; c < dimGrille; c++) {
					fichier >> valMod;
					grilleJ2->grille.getCase(l, c).modifiable = valMod;
				}
			}

			//chargement des etat grille j1
			for (int l = 0; l < dimGrille; l++) {
				for (int c = 0; c < dimGrille; c++) {
					fichier >> val;
					conv = (unsigned char)val;
					grilleJ1->grille.getCase(l, c).etat = conv;
				}
			}
			//chargement des etat grille j1
			for (int l = 0; l < dimGrille; l++) {
				for (int c = 0; c < dimGrille; c++) {
					fichier >> val;
					conv = (unsigned char)val;
					grilleJ2->grille.getCase(l, c).etat = conv;
				}
			}
			//chargements des chronos
			fichier >> *chronoJ1;
			fichier >> *chronoJ2;

			//chargements des val nb erreur
			fichier >> *nbErrJ1;
			fichier >> *nbErrj2;
			//chargements des val stop
			bool valStop;
			fichier >> valStop;
			cout << "valstop " <<valStop;
			*stopJ1 = valStop;
			cout << " stop j1 " << *stopJ1;

			fichier >> valStop;
			cout << "valstop " << valStop;

			*stopJ2 = valStop;
			cout << " stopj2 " << *stopJ2;


		}
		

	}
	else {
		cout << "Impossible d'ouvrire la partie demande!" << endl;
	}
}

int gestSauvegarde::sauvegarder(Jeu &jeu ,string name, int mode, unsigned  int id, Grille* grilleJ1, Grille* grilleJ2, chronometre* chronoJ1, chronometre* chronoJ2, int nbErrJ1, int nbErrj2, bool stopJ1, bool stopJ2) {
	if (id != 0 && !valideId(id)) return -1;
	ofstream fichierIndex;
	fichierIndex.open(cheminDossier + "indexParties.txt", std::fstream::out);
	
	if (!fichierIndex.is_open()) {
		cout << "Une erreur c'est produite lors de l'ouverture de l'index!" << endl;
		return -1;
	}
	if (id == 0) {//si la partie n'a jamais �t� sauvegard� on linscrit dans l'index
		nbSauvegarde++;
		for (unsigned int i = 1; i <= maxId; i++) {
			if (!valideId(i)) {
				id = i;
			}
		}
		if (id == 0) {
			maxId++;
			id = maxId;
		}

		InfoSauvegarde infoSurLaSauvegarde;
		infoSurLaSauvegarde.id = id;
		infoSurLaSauvegarde.name = name;
		infoSurLaSauvegarde.modeJeu = mode;
		infoSurLaSauvegarde.tailleGrille = jeu.grilleJeu.dim;
		infoSurLaSauvegarde.chrono = jeu.chrono.getTimeInMSec();
		fichierIndex << nbSauvegarde << " " << maxId << endl;
		fichierIndex << infoSurLaSauvegarde.id << " " << infoSurLaSauvegarde.name << " " << infoSurLaSauvegarde.modeJeu << " " << infoSurLaSauvegarde.tailleGrille << " " << infoSurLaSauvegarde.chrono << endl;//on ajoute a ligne de la partie dans l'index des aprties sauvegard�es
		for (unsigned int i = 0; i < nbSauvegarde - 1; i++) {//on reecrit toutes les autres parties en mettant la partie qui vient d'�tre suavegard� en haut
			if (listeSauvegarde[i].id != id) {
				fichierIndex << listeSauvegarde[i].id << " " << listeSauvegarde[i].name << " " << listeSauvegarde[i].modeJeu << " " << listeSauvegarde[i].tailleGrille << " " << listeSauvegarde[i].chrono << endl;
			}
		}
	}
	else {
		InfoSauvegarde infoSurLaSauvegarde = getInfoSauvegarde(id);
		infoSurLaSauvegarde.chrono = jeu.chrono.getTimeInMSec();
		fichierIndex << nbSauvegarde << " " << maxId << endl;
		fichierIndex << infoSurLaSauvegarde.id << " " << infoSurLaSauvegarde.name << " " << infoSurLaSauvegarde.modeJeu << " " << infoSurLaSauvegarde.tailleGrille << " " << infoSurLaSauvegarde.chrono << endl;//on ajoute a ligne de la partie dans l'index des aprties sauvegard�es
		for (unsigned int i = 0; i < nbSauvegarde; i++) {//on reecrit toutes les autres parties en mettant la partie qui vient d'�tre suavegard� en haut
			if (listeSauvegarde[i].id != id) {
				fichierIndex << listeSauvegarde[i].id << " " << listeSauvegarde[i].name << " " << listeSauvegarde[i].modeJeu << " " << listeSauvegarde[i].tailleGrille << " " << listeSauvegarde[i].chrono << endl;
			}
		}
	}
	
	
	ofstream fichier;
	fichier.open(cheminDossier + to_string(id) + ".sudokujeu", ios::out);
	if (fichier.is_open()) {
		unsigned char dimGrille = jeu.grilleJeu.dim;
		//////////////sauvegarde des chiffres
		fichier << (int)jeu.grilleSolution.grille.getCase(0, 0).getVal() << " ";
		for (int l = 0; l < dimGrille; l++) {
			for (int c = 0; c < dimGrille; c++) {
				if (!(l == 0 && c == 0))fichier << (int)jeu.grilleSolution.grille.getCase(l, c).getVal() << " ";
			}
			fichier << endl;
		}
		fichier << endl;

		fichier << (int)jeu.grilleOriginale.grille.getCase(0, 0).getVal() << " ";
		for (int l = 0; l < dimGrille; l++) {
			for (int c = 0; c < dimGrille; c++) {
				if (!(l == 0 && c == 0))fichier << (int)jeu.grilleOriginale.grille.getCase(l, c).getVal() << " ";
			}
			fichier << endl;

		}
		fichier << endl;

		fichier << (int)jeu.grilleJeu.grille.getCase(0, 0).getVal() << " ";
		for (int l = 0; l < dimGrille; l++) {
			for (int c = 0; c < dimGrille; c++) {
				if (!(l == 0 && c == 0))fichier << (int)jeu.grilleJeu.grille.getCase(l, c).getVal() << " ";
			}
			fichier << endl;

		}
		fichier << endl;
		fichier << endl;

		//////////////sauvegarde de modifiable
		fichier << (int)jeu.grilleSolution.grille.getCase(0, 0).modifiable << " ";

		for (int l = 0; l < dimGrille; l++) {
			for (int c = 0; c < dimGrille; c++) {
				if (!(l == 0 && c == 0))fichier << jeu.grilleSolution.grille.getCase(l, c).modifiable << " ";
			}
			fichier << endl;
		}
		fichier << endl;

		fichier << (int)jeu.grilleOriginale.grille.getCase(0, 0).modifiable << " ";
		for (int l = 0; l < dimGrille; l++) {
			for (int c = 0; c < dimGrille; c++) {
				if (!(l == 0 && c == 0))fichier << jeu.grilleOriginale.grille.getCase(l, c).modifiable << " ";
			}
			fichier << endl;

		}
		fichier << endl;

		fichier << (int)jeu.grilleJeu.grille.getCase(0, 0).modifiable << " ";
		for (int l = 0; l < dimGrille; l++) {
			for (int c = 0; c < dimGrille; c++) {
				if (!(l == 0 && c == 0)) {
					fichier << jeu.grilleJeu.grille.getCase(l, c).modifiable << " ";
				}
			}
			fichier << endl;

		}
		fichier << endl;
		fichier << endl;

		//////////////sauvegarde de etat
		fichier << (int)jeu.grilleSolution.grille.getCase(0, 0).etat << " ";

		for (int l = 0; l < dimGrille; l++) {
			for (int c = 0; c < dimGrille; c++) {
				if (!(l == 0 && c == 0))fichier << (int)jeu.grilleSolution.grille.getCase(l, c).etat << " ";
			}
			fichier << endl;
		}
		fichier << endl;

		fichier << (int)jeu.grilleOriginale.grille.getCase(0, 0).etat << " ";
		for (int l = 0; l < dimGrille; l++) {
			for (int c = 0; c < dimGrille; c++) {
				if (!(l == 0 && c == 0))fichier << (int)jeu.grilleOriginale.grille.getCase(l, c).etat << " ";
			}
			fichier << endl;

		}
		fichier << endl;

		fichier << (int)jeu.grilleJeu.grille.getCase(0, 0).etat << " ";
		for (int l = 0; l < dimGrille; l++) {
			for (int c = 0; c < dimGrille; c++) {
				if (!(l == 0 && c == 0))fichier << (int)jeu.grilleJeu.grille.getCase(l, c).etat << " ";
			}
			fichier << endl;

		}
		if (mode == 3) {
			assert(grilleJ1 != NULL&& grilleJ2 != NULL && chronoJ1 != NULL && chronoJ2 != NULL);
			//Partie sauvegarde 1vs1
			//sauveagrde  valeur grille J1
			fichier << (int)grilleJ1->grille.getCase(0, 0).getVal() << " ";
			for (int l = 0; l < dimGrille; l++) {
				for (int c = 0; c < dimGrille; c++) {
					if (!(l == 0 && c == 0))fichier << (int)grilleJ1->grille.getCase(l, c).getVal() << " ";
				}
				fichier << endl;
			}
			fichier << endl;
			//sauveagrde  valeur grille J2
			fichier << (int)grilleJ2->grille.getCase(0, 0).getVal() << " ";
			for (int l = 0; l < dimGrille; l++) {
				for (int c = 0; c < dimGrille; c++) {
					if (!(l == 0 && c == 0))fichier << (int)grilleJ2->grille.getCase(l, c).getVal() << " ";
				}
				fichier << endl;
			}
			fichier << endl;


			//sauvegarde modifiable grilleJ1
			fichier << (int)grilleJ1->grille.getCase(0, 0).modifiable << " ";

			for (int l = 0; l < dimGrille; l++) {
				for (int c = 0; c < dimGrille; c++) {
					if (!(l == 0 && c == 0))fichier << grilleJ1->grille.getCase(l, c).modifiable << " ";
				}
				fichier << endl;
			}
			fichier << endl;
			//sauvegarde modifiable grilleJ2
			fichier << (int)grilleJ2->grille.getCase(0, 0).modifiable << " ";

			for (int l = 0; l < dimGrille; l++) {
				for (int c = 0; c < dimGrille; c++) {
					if (!(l == 0 && c == 0))fichier << grilleJ2->grille.getCase(l, c).modifiable << " ";
				}
				fichier << endl;
			}
			fichier << endl;


			//sauveagrde etat grille J1
			fichier << (int)grilleJ1->grille.getCase(0, 0).etat << " ";

			for (int l = 0; l < dimGrille; l++) {
				for (int c = 0; c < dimGrille; c++) {
					if (!(l == 0 && c == 0))fichier << (int)grilleJ1->grille.getCase(l, c).etat << " ";
				}
				fichier << endl;
			}
			fichier << endl;
			//sauveagrde etat grille J2
			fichier << (int)grilleJ2->grille.getCase(0, 0).etat << " ";

			for (int l = 0; l < dimGrille; l++) {
				for (int c = 0; c < dimGrille; c++) {
					if (!(l == 0 && c == 0))fichier << (int)grilleJ2->grille.getCase(l, c).etat << " ";
				}
				fichier << endl;
			}
			fichier << endl;

			//sauvegarde chrnono j1
			fichier << chronoJ1->getTimeInMSec() << endl;
			//sauvegarde chrnono j2
			fichier << chronoJ2->getTimeInMSec() << endl;

			//sauvegarde nberrj1
			fichier << nbErrJ1 << endl;

			//sauvegarde nberrj2
			fichier << nbErrj2 << endl;

			//sauvegarde etat boucle j1
			fichier << stopJ1 << endl;

			//sauvegarde etat boucle j2
			fichier << stopJ2 << endl;

		}
		fichier.close();
	}
	else {
		cout << "Une erreur c'est produite!" << endl;
		return -1;
	}
	updateListe();
	return id;
}

void gestSauvegarde::supprimerSauvegarde(unsigned char id)
{
	if (!valideId(id)) return;
	nbSauvegarde--;
	ofstream fichierIndex;
	fichierIndex.open(cheminDossier + "indexParties.txt", std::fstream::out);
	if (fichierIndex.is_open()) {
		if (id == maxId) maxId--;
		fichierIndex << nbSauvegarde << " " << maxId << endl;
		for (unsigned int i = 0; i < nbSauvegarde +1; i++) {
			if (listeSauvegarde[i].id != id) {
				fichierIndex << listeSauvegarde[i].id << " " << listeSauvegarde[i].name << " " << listeSauvegarde[i].modeJeu << " " << listeSauvegarde[i].tailleGrille << " " << 0 << endl;
			}
		}
		
		if (remove((cheminDossier + to_string(id) + ".sudokujeu").c_str()) != 0) {
			cout << "Erreur lors de la supression" << endl;
		}
		else {
			cout << "Fichier supprim�" << endl;
		}
	}
	else {
		cout << "Une erreur c'est produite lors de l'ouverture de l'index!" << endl;
	}
	updateListe();
}

void gestSauvegarde::renommerSauvegarde(unsigned int id, string name)
{
	if (!valideId(id)) return;
	if (name == "") return;
	ofstream fichierIndex;
	fichierIndex.open(cheminDossier + "indexParties.txt", std::fstream::out);
	if (fichierIndex.is_open()) {
		fichierIndex << nbSauvegarde << " " << maxId << endl;
		for (unsigned int i = 0; i < nbSauvegarde; i++) {
			if (listeSauvegarde[i].id != id) {
				fichierIndex << listeSauvegarde[i].id << " " << listeSauvegarde[i].name << " " << listeSauvegarde[i].modeJeu << " " << listeSauvegarde[i].tailleGrille << " " << 0 << endl;
			}
			else {
				fichierIndex << listeSauvegarde[i].id << " " << name << " " << listeSauvegarde[i].modeJeu << " " << listeSauvegarde[i].tailleGrille << " " << 0 << endl;
			}
		}

	}
	else {
		cout << "Une erreur c'est produite lors de l'ouverture de l'index!" << endl;
	}
	updateListe();
}
