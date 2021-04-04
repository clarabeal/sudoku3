#ifndef _SAUVEGARDE_H 
#define _SAUVEGARDE_H
#include "Grille.h"
#include <stdlib.h>
#include <iostream>
#include <string>
#include "Jeu.h"

using namespace std;

struct sauvegardeId {
	unsigned int id;
	string name;
	unsigned int modeJeu;
	unsigned int tailleGrille;
	unsigned int chrono;
};

class gestSauvegarde
{
public:
	gestSauvegarde(string emplacement);
	~gestSauvegarde();
	sauvegardeId* listeSauvegarde;
	unsigned int nbSauvegarde,maxId;
 	string cheminDossier; //chemin vers le dossier qui contient les sauvegardes
	void updateListe();
	sauvegardeId& getSauvegardeId(unsigned char id) const;

	bool valideId(unsigned char id) const;

	void loadFromFile(int id);

	int sauvegarder(Jeu& jeu, string name, int mode, int id);

	void supprimerSauvegarde(unsigned char id);

private:

};

#endif

