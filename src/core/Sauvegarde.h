#ifndef _SAUVEGARDE_H 
#define _SAUVEGARDE_H
#include <stdlib.h>
#include <iostream>
#include <string>
#include "Grille.h"
#include "Jeu.h"


using namespace std;

struct sauvegardeId {
	unsigned int id;
	string name;
	unsigned int modeJeu;
	unsigned int tailleGrille;
	unsigned long int chrono;
};

class gestSauvegarde
{
public:
	gestSauvegarde(string emplacement, string emplacement2 = "");
	~gestSauvegarde();
	sauvegardeId* listeSauvegarde;
	unsigned int nbSauvegarde,maxId;
 	string cheminDossier; //chemin vers le dossier qui contient les sauvegardes
	bool updateListe();
	sauvegardeId& getSauvegardeId(unsigned char id) const;

	bool valideId(unsigned char id) const;

	void loadFromFile(int id, Grille& g_sol, Grille& g_orig, Grille g_jeu);

	int sauvegarder(Jeu& jeu, string name, int mode, int id);

	void supprimerSauvegarde(unsigned char id);

private:

};

#endif

