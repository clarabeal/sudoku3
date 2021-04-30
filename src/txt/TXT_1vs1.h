#ifndef _TXT_1Vs1_H
#define _TXT_1Vs1_H

#include "../core/Sauvegarde.h"

class TXT_1vs1
{
public:
	TXT_1vs1(unsigned char d);
	TXT_1vs1(unsigned char d, int id, unsigned long int time, Grille& g_sol, Grille& g_orig, Grille& g_jeu, Grille& grilleJ1_, Grille& grilleJ2_, unsigned long int chronoJ1_, unsigned long int chronoJ2_, int nbErrJ1, int nbErrj2, bool stopJ1, bool stopJ2);
	~TXT_1vs1();
	
	/**
	\brief Boucle du jeu
	*/
	void boucle();

	unsigned char menu();

private:

	Jeu1Vs1 jeu;
	gestSauvegarde gestionnaireSauvegarde;
	
	void termClear() const;
};


#endif