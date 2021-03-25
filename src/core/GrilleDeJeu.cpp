#include "GrilleDeJeu.h"
#include <time.h>
#include <stdlib.h>
#include <math.h>
using namespace std;
GrilleDeJeu::GrilleDeJeu(unsigned char d): grilleSolution(d), grilleJeu(d) {

}

GrilleDeJeu::~GrilleDeJeu(){
	
}

bool GrilleDeJeu::genererGrillePleine()
{
	srand((unsigned int)time(NULL));// a mettre dans le main apres


	unsigned char dimGrille = grilleSolution.dim;
	for (unsigned char l=1; l <= dimGrille; l++) {
		for (unsigned char c=1; c <= dimGrille; c++) {
			if (grilleSolution.grille.getCase(l, c).getVal() == 0) {
				unsigned char* tab = new unsigned char[dimGrille];// on remplit un tableau avec les nombres a placer dans un ordre aleatoire
				remplirTblAlea(tab, dimGrille);
				for (unsigned char i = 0; i < dimGrille; i++) {
					unsigned char value = tab[i];
					if (!grilleSolution.lignes[l - 1].isIn(value)) {
						if (!grilleSolution.colonnes[c - 1].isIn(value)) {
							if (!grilleSolution.carres[trouverNumeroCarre(l,c)].isIn(value)) {
								if (verifGrillePleine()) {
									return true;
								}
								else {
									genererGrillePleine();
								}
							}
						}
					}

				}
				delete []tab;
			}
		}
	}

}

void GrilleDeJeu::remplirTblAlea(unsigned char *tab, unsigned char max){// remplit un tbl sur le tas de nombre alea entre 1 et MAX
	unsigned char nb = 0;
	for (int i = 0; i < max; i++) {
		bool disponible = false;
		while (disponible == false) {
			disponible = true;
			nb = (rand() % max) + 1;
			for (int j = 1; j < i; j++) {
				if (tab[j] == nb) {
					disponible = false;
				}
			}
		}
		tab[i] = nb;
	}
}

unsigned char GrilleDeJeu::trouverNumeroCarre(unsigned char l, unsigned char c) const
{
	unsigned char tailleCarre = sqrt(grilleSolution.dim);
	unsigned char nb_carre = ((l - 1) / tailleCarre) * tailleCarre + ((c - 1) / tailleCarre) + 1;
		return nb_carre;
}

bool GrilleDeJeu::verifGrillePleine() const
{
	unsigned char dimGrille = grilleSolution.dim;
	for (unsigned char l = 1; l <= dimGrille; l++) {
		for (unsigned char c = 1; c <= dimGrille; c++) {
			if (grilleSolution.grille.getCase(l, c).getVal() == 0) {
				return false;
			}
		}
	}
	return true;
}
