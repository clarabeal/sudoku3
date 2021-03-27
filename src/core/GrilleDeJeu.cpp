#include "GrilleDeJeu.h"
#include <time.h>
#include <stdlib.h>
#include <math.h>
using namespace std;


GrilleDeJeu::GrilleDeJeu(unsigned char d): grilleSolution(d), grilleJeu(d) {

}

GrilleDeJeu::~GrilleDeJeu(){
	
}

bool GrilleDeJeu::genererGrillePleine(int etape)
{
	srand((unsigned int)time(NULL));// a mettre dans le main apres
	//cout << "///////Etape: " << etape<<  endl;

	unsigned char dimGrille = grilleSolution.dim;
	for (unsigned char l=1; l <= dimGrille; l++) {
		for (unsigned char c=1; c <= dimGrille; c++) {
			//cout << "on check si il faut remplir la case " << (int)l << " " << (int)c << endl;
			if (grilleSolution.grille.getCase(l-1, c-1).getVal() == 0) { //si la case est vide
				//cout << "la case " << (int)l << " " << (int)c << " n'est pas remplit, on le fait." << endl;
				unsigned char* tab = new unsigned char[(int)dimGrille]; //on cree un tableau de taille dimGrille sur le tas
				remplirTblAlea(tab, dimGrille);// on remplit un tableau avec les nombres a placer dans un ordre aleatoire
				for (unsigned char i = 0; i < dimGrille; i++) { //on parcourt ts les elements du tableau qu'on vient de creer
					unsigned char value = tab[i];//on tire les elements du tableau un a un
					//cout << "on essaye de placer la valeur " << (int)value << endl;

					if (!grilleSolution.lignes[l-1].isIn(value)) { //si la valeur n'est pas deja dans la ligne
						//cout << "Pas dans la ligne" << endl;
						if (!grilleSolution.colonnes[c-1].isIn(value)) { //si la valeur n'est pas deja dans la colonne
							//cout << "Pas dans la colonne" << endl;
							if (!grilleSolution.carres[trouverNumeroCarre(l,c)-1].isIn(value)) { //si elle n'est pas dans le carre
								//cout << "Pas dans le carre" << endl;
								if (verifGrillePleine()) { //si la grille est pleine
									//cout << "La grille est pleine fini" << endl;
									delete []tab;//on supprime le tableau de valeurs aleatoires
									return true;//grille remplie : on sort
								}
								else {
									//cout << "La case " << (int)l << " " << (int)c << " prend la valeur " << (int)value <<endl;
									grilleSolution.grille.getCase(l-1, c-1).setVal(value);
									//grilleSolution.grille.print();
									if (genererGrillePleine(etape + 1)) {
										delete[]tab;//on supprime le tableau de valeurs aleatoires
										return true;//on rappelle la fonction
									}
									/*else {
										cout << "retour a l'etape "<< etape - 1 << endl;
									}*/
								}
							}//else { cout << "Deja dans le carre" << endl; }
						}//else {cout << "Deja dans la colonne" << endl;}
					}//else{cout << "Deja dans la ligne" << endl;}

				}
				//cout << "Les etapes precedentes rendent la generation impossible on essaye de changer des valeur en amont" << endl;
				grilleSolution.grille.getCase(l - 1, c - 1).setVal(0);
				delete []tab;//on supprime le tableau de valeurs aleatoires
				return false;
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
			for (int j = 0; j < i; j++) {
				if (tab[j] == nb) {
					disponible = false;
				}
			}
		}
		tab[i] = nb;
	}
}

unsigned char GrilleDeJeu::nombreDeSolutions(unsigned char nbSolution) const
{
	//cout << "///////Etape: " << (int)nbSolution <<  endl;

	unsigned char dimGrille = grilleSolution.dim;
	for (unsigned char l = 1; l <= dimGrille; l++) {
		for (unsigned char c = 1; c <= dimGrille; c++) {
			//cout << "on check si il faut remplir la case " << (int)l << " " << (int)c << endl;
			if (grilleSolution.grille.getCase(l - 1, c - 1).getVal() == 0) { //si la case est vide
				//cout << "la case " << (int)l << " " << (int)c << " n'est pas remplit, on le fait." << endl;
				unsigned char* tab = new unsigned char[(int)dimGrille]; //on cree un tableau de taille dimGrille sur le tas
				for (int i = 0; i < dimGrille; i++) {tab[i] = i+1;}// on remplit un tableau avec les nombres 1 a taille grille
				for (unsigned char i = 0; i < dimGrille; i++) { //on parcourt ts les elements du tableau qu'on vient de creer
					unsigned char value = tab[i];//on tire les elements du tableau un a un
					//cout << "on essaye de placer la valeur " << (int)value << endl;

					if (!grilleSolution.lignes[l - 1].isIn(value)) { //si la valeur n'est pas deja dans la ligne
						//cout << "Pas dans la ligne" << endl;
						if (!grilleSolution.colonnes[c - 1].isIn(value)) { //si la valeur n'est pas deja dans la colonne
							//cout << "Pas dans la colonne" << endl;
							if (!grilleSolution.carres[trouverNumeroCarre(l, c) - 1].isIn(value)) { //si elle n'est pas dans le carre
								//cout << "Pas dans le carre" << endl;
								//cout << "La case " << (int)l << " " << (int)c << " prend la valeur " << (int)value <<endl;
								grilleSolution.grille.getCase(l - 1, c - 1).setVal(value);
								//grilleSolution.grille.print();
								if (verifGrillePleine()) { //si la grille est pleine
									//cout << "La grille est pleine fini" << endl;
									nbSolution++;//grille remplie : on sort
								}
								else {
									nbSolution = nbSolution + nombreDeSolutions(0);
									//cout << "nb solution " << (int)nbSolution << endl;
								}
							}else {// cout << "Deja dans le carre" << endl; 
							}
						}else {//cout << "Deja dans la colonne" << endl;
						}
					}else{//cout << "Deja dans la ligne" << endl;
					}

				}
				//cout << "Les etapes precedentes rendent la generation impossible on essaye de changer des valeur en amont" << endl;
				grilleSolution.grille.getCase(l - 1, c - 1).setVal(0);
				delete[]tab;//on supprime le tableau de valeurs aleatoires
				return nbSolution;
			}
		}
	}
	return nbSolution;
}

void GrilleDeJeu::genererGrilleMinimale (){
	grilleJeu = grilleSolution;
	unsigned char l,c,val;
	
	srand((unsigned int)time(NULL));// a mettre dans le main apres

	do {
		l=rand()%9+1;
		c=rand()%9+1;

		cout << "l : " << (int)l << " c : " << (int)c << endl;

		val=grilleJeu.grille.getCase(l-1,c-1).getVal(); //on garde la valeur de la case au cas où on doit la remettre plus tard
		grilleJeu.grille.getCase(l-1,c-1).setVal(0); //on enlève la valeur

	}while (nombreDeSolutions()==1); // sort de la boucle dès qu'il y a plus d'une solution

	grilleJeu.grille.getCase(l,c).setVal(val); //on remet la valeur d'avant pour retrouver le nbDeSol égal à 1
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
	for (unsigned char l = 0; l <= dimGrille -1; l++) {
		for (unsigned char c = 0; c <= dimGrille -1; c++) {
			if (grilleSolution.grille.getCase(l, c).getVal() == 0) {
				return false;
			}
		}
	}
	return true;
}
