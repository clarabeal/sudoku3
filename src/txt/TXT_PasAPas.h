#ifndef _TXT_PasAPas_H
#define _TXT_PasAPas_H

#include "../core/Sauvegarde.h"

class TXT_PasAPas
{
public:
	TXT_PasAPas(unsigned char d, int id,unsigned long int time, Grille& g_sol, Grille& g_orig, Grille& g_jeu);
	TXT_PasAPas(unsigned char d);

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