#ifndef _TXT_PasAPas_H
#define _TXT_PasAPas_H

#include "../core/Sauvegarde.h"

class TXT_PasAPas
{
public:
	TXT_PasAPas(const unsigned char& d, const int& id, const unsigned long int& time, const Grille& g_sol, const Grille& g_orig, const Grille& g_jeu);
	TXT_PasAPas(const unsigned char& d);

	~TXT_PasAPas();
	
	/**
	\brief Boucle du jeu
	*/
	void boucle();

	void boucleTest();



private:
	JeuPasAPas jeu;

	void termClear() const;

	unsigned char menu();
};

#endif