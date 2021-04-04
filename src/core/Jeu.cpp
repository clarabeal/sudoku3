#include "Jeu.h"
#include <time.h>
#include <stdlib.h>
#include <math.h>
using namespace std;

Jeu::Jeu(unsigned char d): grilleSolution(d), grilleOriginale(d), grilleJeu(d){
	initDone = false;
	sauvegardeId = 0;

}

Jeu::Jeu(unsigned char d, int id, Grille &g_sol, Grille &g_orig, Grille &g_jeu) : grilleSolution(d), grilleOriginale(d), grilleJeu(d) {
	grilleSolution.grille = g_sol.grille;
	grilleOriginale.grille = g_orig.grille;
	grilleJeu.grille = g_jeu.grille;
	initDone = true;
	sauvegardeId = id;
}


Jeu::~Jeu(){
	
}

bool Jeu::genererGrillePleine(int etape)
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
								if (verifGrillePleine(grilleSolution)) { //si la grille est pleine
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
	return true;
}

void Jeu::remplirTblAlea(unsigned char *tab, unsigned char max){// remplit un tbl sur le tas de nombre alea entre 1 et MAX
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

unsigned char Jeu::nombreDeSolutions(Grille &grille) const
{
	unsigned char nbSolution =0;
	//cout << "///////Etape: " << (int)nbSolution <<  endl;

	unsigned char dimGrille = grille.dim;
	for (unsigned char l = 1; l <= dimGrille; l++) {
		for (unsigned char c = 1; c <= dimGrille; c++) {
			//cout << "on check si il faut remplir la case " << (int)l << " " << (int)c << endl;
			if (grille.grille.getCase(l - 1, c - 1).getVal() == 0) { //si la case est vide
				//cout << "la case " << (int)l << " " << (int)c << " n'est pas remplit, on le fait." << endl;
				unsigned char *tab = new unsigned char[(int)dimGrille]; //on cree un tableau de taille dimGrille sur le tas
				for (unsigned char i = 0; i < dimGrille; i++) {tab[i] = i+1;}// on remplit un tableau avec les nombres 1 a taille grille
				for (unsigned char i = 0; i < dimGrille; i++) { //on parcourt ts les elements du tableau qu'on vient de creer
					unsigned char value = tab[i];//on tire les elements du tableau un a un
					//cout << "on essaye de placer la valeur " << (int)value << endl;
					if (!grille.lignes[l - 1].isIn(value)) { //si la valeur n'est pas deja dans la ligne
						//cout << "Pas dans la ligne" << endl;
						if (!grille.colonnes[c - 1].isIn(value)) { //si la valeur n'est pas deja dans la colonne
							//cout << "Pas dans la colonne" << endl;
							if (!grille.carres[trouverNumeroCarre(l, c) - 1].isIn(value)) { //si elle n'est pas dans le carre
								//cout << "Pas dans le carre" << endl;
								//cout << "La case " << (int)l << " " << (int)c << " prend la valeur " << (int)value <<endl;
								grille.grille.getCase(l - 1, c - 1).setVal(value);
								//grilleSolution.grille.print();
								if (verifGrillePleine(grille)) { //si la grille est pleine
									
									nbSolution++;//grille remplie : on sort
																		
								}
								else {
									nbSolution = nbSolution + nombreDeSolutions(grille);
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
				grille.grille.getCase(l - 1, c - 1).setVal(0);
				delete[]tab;//on supprime le tableau de valeurs aleatoires
				return nbSolution;
			}
		}
	}
	return nbSolution;
}

void Jeu::genererGrilleMinimale (){
	unsigned char dimGrille = grilleSolution.dim;

	/*for (unsigned char l = 1; l <= dimGrille; l++) {
		for (unsigned char c = 1; c <= dimGrille; c++) {
			grilleJeu.grille.getCase(l - 1, c - 1).setVal(grilleSolution.grille.getCase(l - 1, c - 1).getVal());
		}
	} //copie de la grille solution dans la grille de jeu*/
	grilleJeu.grille = grilleSolution.grille;
	

	unsigned char l,c,val;
	
	srand((unsigned int)time(NULL));// a mettre dans le main apres
	unsigned char attempt = dimGrille;//plus ce chiffre est grand plus le nb de trous dans la grille aurat tendance a être grand mais plus il faudra de temps pour generer la grille partielle(un chiffre trop grand et ca finit jamais
	//unsigned char atp = attempt;//juste pour aficher le %
	//cout << "generation grille partielle" << endl << "0%" << endl;
	while (attempt > 0) {
		do {
			l = rand() % dimGrille + 1;
			c = rand() % dimGrille + 1;

			//cout << "l : " << (int)l << " c : " << (int)c << endl;

			val = grilleJeu.grille.getCase(l - 1, c - 1).getVal(); //on garde la valeur de la case au cas où on doit la remettre plus tard
			grilleJeu.grille.getCase(l - 1, c - 1).setVal(0); //on enlève la valeur
			grilleJeu.grille.getCase(l - 1, c - 1).modifiable = true;
			//cout << (int)nombreDeSolutions(grilleJeu) << endl;
		} while (nombreDeSolutions(grilleJeu) == 1); // sort de la boucle dès qu'il y a plus d'une solution
		grilleJeu.grille.getCase(l - 1, c - 1).setVal(val); //on remet la valeur d'avant pour retrouver le nbDeSol égal à 1
		grilleJeu.grille.getCase(l - 1, c - 1).modifiable = false;
		attempt--;
		//cout << (int)((atp - attempt) * 100 / atp) << "%" << endl;
	}
}

unsigned char Jeu::trouverNumeroCarre(unsigned char l, unsigned char c) const
{
	unsigned char tailleCarre = sqrt(grilleSolution.dim);
	unsigned char nb_carre = ((l - 1) / tailleCarre) * tailleCarre + ((c - 1) / tailleCarre) + 1;
		return nb_carre;
}

bool Jeu::verifGrillePleine(Grille &grille) const
{
	unsigned char dimGrille = grille.dim;
	for (unsigned char l = 0; l <= dimGrille -1; l++) {
		for (unsigned char c = 0; c <= dimGrille -1; c++) {
			if (grille.grille.getCase(l, c).getVal() == 0) {
				return false;
			}
		}
	}
	return true;
}

void Jeu::init()
{
	grilleSolution.viderGrille();
	grilleJeu.viderGrille();
	genererGrillePleine();
	genererGrilleMinimale();
	grilleOriginale.grille = grilleJeu.grille;
}

bool Jeu::estValValide (unsigned char valeur) const {
    return (valeur>0 && valeur<=grilleJeu.dim);
}

bool Jeu::sontCorValides (unsigned char l, unsigned char c) const {
	return ((l > 0 && l <= grilleJeu.dim) && (c > 0 && c <= grilleJeu.dim) && grilleJeu.grille.getCase(l - 1, c - 1).modifiable);
}

bool Jeu::getModifCase (unsigned char l, unsigned char c) const {
	return grilleJeu.grille.getCase(l-1,c-1).modifiable;
}

unsigned int Jeu::nbErreurs () const {
	unsigned int compteur = 0, dim = grilleSolution.dim;
	unsigned char i, j;

	for (i=0; i<dim; i++) {
		for (j=0; j<dim; j++) {
			if (grilleJeu.grille.getCase(i, j).getVal() != grilleSolution.grille.getCase(i, j).getVal()) compteur++;
			
		}
	}
	return compteur;
}