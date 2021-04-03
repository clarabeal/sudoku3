#include "sauvegarde.h"
#include "../txt/TXT_Classique.h"
#include "../txt/TXT_PasAPas.h"
#include "../txt/TXT_1vs1.h"
#include <fstream>
#include <string>

gestSauvegarde::gestSauvegarde(string emplacement)
{
	cheminDossier = emplacement;
	ifstream fichier;
	fichier.open(cheminDossier + "indexParties.txt", ios::in);
	if (fichier.is_open()) {
		//cout << "index des sauvegarde ouvert a avec succes" << endl;
		fichier >> nbSauvegarde;
		fichier >> maxId;
		//cout << nbSauvegarde << " sauvegardes ont ete trouves" << endl;
		listeSauvegarde = new sauvegardeId[nbSauvegarde];
		for (int i = 0; i < nbSauvegarde; i++) {
			fichier >> listeSauvegarde[i].id >> listeSauvegarde[i].name >> listeSauvegarde[i].modeJeu >> listeSauvegarde[i].tailleGrille >> listeSauvegarde[i].chrono;
		}
		for (int i = 0; i < nbSauvegarde; i++) {
			//cout << "sauvegarde: " << i + 1 << " id: " << listeSauvegarde[i].id << " nom: " << listeSauvegarde[i].name << " mode: " << listeSauvegarde[i].modeJeu << " Taille: " << listeSauvegarde[i].tailleGrille << " chrono: " << listeSauvegarde[i].chrono << endl;
		}
	}
	else {
		listeSauvegarde = nullptr;
		//cout << "Impossible d'ouvrire l'index des sauvegardes! " << endl;
	}

	fichier.close();
}

gestSauvegarde::~gestSauvegarde()
{
	delete[] listeSauvegarde;
}

sauvegardeId& gestSauvegarde::getSauvegardeId(unsigned char id) const {
	for (int i = 0; i < nbSauvegarde; i++) {
		if (listeSauvegarde[i].id == id) {
			return listeSauvegarde[i];
		}
	}
}

bool gestSauvegarde::valideId(unsigned char id) const {
	for (int i = 0; i < nbSauvegarde; i++) {
		if (listeSauvegarde[i].id == id) {
			return true;
		}
	}
	return false;
}

void gestSauvegarde::loadFromFile(int id)
{
	ifstream fichier;
	sauvegardeId& infoSurLaSauvegarde = getSauvegardeId(id);
	fichier.open(cheminDossier + to_string(id) + ".sudokujeu", ios::in);
	if (fichier.is_open()) {
		unsigned char dimGrille = infoSurLaSauvegarde.tailleGrille;
		Grille g_sol(dimGrille);
		Grille g_orig(dimGrille);
		Grille g_jeu(dimGrille);
		int val;
		unsigned char conv;
		cout << "debut du chargement des grilles" << endl;
		cout << (int)g_sol.dim << endl;
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
		cout << "Grilles chargees" << endl;
		g_jeu.grille.print();
		if (infoSurLaSauvegarde.modeJeu == 1) {
			TXT_Classique partieTxt((unsigned char)infoSurLaSauvegarde.tailleGrille, g_sol, g_orig, g_jeu);
			partieTxt.boucle();
		}
		else if (infoSurLaSauvegarde.modeJeu == 2) {
			TXT_PasAPas partieTxt((unsigned char)infoSurLaSauvegarde.tailleGrille, g_sol, g_orig, g_jeu);
			partieTxt.boucle();
		}
		else {
			cout << "Le mode de jeu de cette grille est invalide ou ne pas être repris a partir d'une sauvegarde" << endl;
		}

	}
	else {
		cout << "Impossible d'ouvrire la partie demande!" << endl;
	}
}

void gestSauvegarde::sauvegarder(Jeu &jeu ,string name, int mode) {

	maxId++;
	nbSauvegarde++;
	int idSauvegarde = maxId;

	sauvegardeId infoSurLaSauvegarde;
	infoSurLaSauvegarde.id = idSauvegarde;
	infoSurLaSauvegarde.name = name;
	infoSurLaSauvegarde.modeJeu = mode;
	infoSurLaSauvegarde.tailleGrille = jeu.grilleJeu.dim;

	ofstream fichierIndex;
	fichierIndex.open(cheminDossier + "indexParties.txt",  std::fstream::out);
	if (fichierIndex.is_open()) {
		fichierIndex << nbSauvegarde << " " << maxId << endl;
		for (int i = 0; i < nbSauvegarde - 1; i++) {
			fichierIndex << listeSauvegarde[i].id << " " << listeSauvegarde[i].name << " " << listeSauvegarde[i].modeJeu << " " << listeSauvegarde[i].tailleGrille << " " << 0 << endl;
		}
		fichierIndex << infoSurLaSauvegarde.id << " " << infoSurLaSauvegarde.name << " " << infoSurLaSauvegarde.modeJeu << " " << infoSurLaSauvegarde.tailleGrille << " " << 0 << endl;
		string line = to_string(nbSauvegarde) + " " + to_string(maxId);

		ofstream fichier;
		fichier.open(cheminDossier + to_string(infoSurLaSauvegarde.id) + ".sudokujeu", ios::out);
		if (fichier.is_open()) {
			unsigned char dimGrille = jeu.grilleJeu.dim;
			fichier << (int)jeu.grilleSolution.grille.getCase(0, 0).getVal()<< " ";
			for (int l = 0; l < dimGrille; l++) {
				for (int c = 0; c < dimGrille; c++) {
					if(!(l== 0 && c == 0))fichier << (int)jeu.grilleSolution.grille.getCase(l, c).getVal() << " ";
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

			fichier << (int)jeu.grilleOriginale.grille.getCase(0, 0).getVal() << " ";
			for (int l = 0; l < dimGrille; l++) {
				for (int c = 0; c < dimGrille; c++) {
					if (!(l == 0 && c == 0))fichier << (int)jeu.grilleJeu.grille.getCase(l, c).getVal() << " ";
				}
				fichier << endl;

			}
			fichier.close();
		}
		else {
			cout << "Une erreur c'est produite!" << endl;
		}
	}else {
		cout << "Une erreur c'est produite lors de l'ouverture de l'index!" << endl;
	}
}