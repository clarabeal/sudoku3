#ifndef _TXT_1Vs1_H
#define _TXT_1Vs1_H

#include "../core/Sauvegarde.h"

class TXT_1vs1
{
public:
	TXT_1vs1(unsigned char d);
	TXT_1vs1(unsigned char d, int id, unsigned long int time, Grille& g_sol, Grille& g_orig, Grille& g_jeu, Grille& grilleJ1, Grille& grilleJ2, unsigned long int chronoJ1, unsigned long int chronoJ2, int nbErrJ1, int nbErrj2, bool stopJ1, bool stopJ2);
	~TXT_1vs1();
	
	/**
	\brief Boucle du jeu
	*/
	void boucle();

	unsigned char menu();

private:

	Jeu jeu;
	gestSauvegarde gestionnaireSauvegarde;
	Grille grilleJ1;
	Grille grilleJ2;

	chronometre chronoJ1;
	chronometre chronoJ2;

	int nbErreurJ1;
	int nbErreurJ2;

	bool stopBoucleJ1;
	bool stopBoucleJ2;
	void termClear() const;
};


#endif