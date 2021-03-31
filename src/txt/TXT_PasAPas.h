#ifndef _TXT_PasAPas_H
#define _TXT_PasAPas_H

#include "../core/Jeu.h"

class TXT_PasAPas
{
public:
	TXT_PasAPas(unsigned char d);

	~TXT_PasAPas();
	
	/**
	\brief Boucle du jeu
	*/
	void boucle();

	void boucleTest();

	void updateDiffCase();

	unsigned char getDiffCase(unsigned char l, unsigned char c);

	void coordCaseSimple(unsigned char &l, unsigned char &c);

	void printTabDiff()const;

	unsigned char* tabDiffCase;

private:
	Jeu jeu;

	void termClear();
};

#endif