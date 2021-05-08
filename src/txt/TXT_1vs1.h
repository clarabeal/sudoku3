#ifndef _TXT_1Vs1_H
#define _TXT_1Vs1_H

#include "../core/Sauvegarde.h"

class TXT_1vs1
{
public:
	TXT_1vs1(const unsigned char& d);
	TXT_1vs1(const unsigned char& d, const int& id, const unsigned long int& time, const Grille& g_sol, const Grille& g_orig, const Grille& g_jeu, const Grille& grilleJ1_, const Grille& grilleJ2_, const long int& chronoJ1_, const unsigned long int& chronoJ2_, const int& nbErrJ1, const int& nbErrJ2, const bool& stopJ1, const bool& stopJ2);
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