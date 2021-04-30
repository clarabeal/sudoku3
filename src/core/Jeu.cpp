#include "Jeu.h"

#include <time.h>
#include <stdlib.h>
#include <math.h>
using namespace std;


//---------Class Jeu
Jeu::Jeu(unsigned char d): grilleSolution(d), grilleOriginale(d), grilleJeu(d){
	initDone = false;
	sauvegardeId = 0;

}

Jeu::Jeu(unsigned char d, int id, unsigned long int time, Grille &g_sol, Grille &g_orig, Grille &g_jeu) : grilleSolution(d), grilleOriginale(d), grilleJeu(d), chrono(time) {
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
	srand((unsigned int)time(nullptr));// a mettre dans le main apres
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
	
	srand((unsigned int)time(nullptr));// a mettre dans le main apres
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
	unsigned char dimGrille = grilleSolution.dim;

	for (unsigned char l = 0; l < dimGrille; l++) {
		for (unsigned char c = 0; c < dimGrille; c++) {
			grilleSolution.grille.getCase(l, c).modifiable = false; // on indique que tt les cases de la grille solution ne sont pas modfiable
		}
	}

	grilleOriginale = grilleJeu;
	chrono.reset();
	chrono.start();
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


//---------Class jeuPasAPas (herité de jeu)
JeuPasAPas::JeuPasAPas(unsigned char d):Jeu(d) {
	tabDiffCase = new unsigned char[2 * d * d];
	coloration = false;
}

JeuPasAPas::JeuPasAPas(unsigned char d, int id, unsigned long time, Grille& g_sol, Grille& g_orig, Grille& g_jeu): Jeu(d, id, time, g_sol, g_orig, g_jeu) {
	tabDiffCase = new unsigned char[2 * d * d];
	coloration = false;

}

JeuPasAPas::~JeuPasAPas() {
	delete[]tabDiffCase;
}

void JeuPasAPas::updateDiffCase() {
	unsigned char dimGrille = grilleJeu.dim;
	for (unsigned char li = 1; li <= dimGrille; ++li) {
		for (unsigned char co = 1; co <= dimGrille; ++co) {
			if (grilleJeu.grille.getCase(li - 1, co - 1).getVal() == 0 || grilleSolution.grille.getCase(li - 1, co - 1).getVal() != grilleJeu.grille.getCase(li - 1, co - 1).getVal()) {
				// Verison nombre total indices l/c/carre
				unsigned char scoreLi = 1;
				unsigned char scoreCol = 1;
				unsigned char scoreCar = 1;

				for (unsigned char i = 0; i < dimGrille; i++) {
					if (grilleJeu.lignes[li - 1].tabl[i]->getVal() == grilleSolution.lignes[li - 1].tabl[i]->getVal()) {
						scoreLi = scoreLi * 2;
					}
					if (grilleJeu.colonnes[co - 1].tabcl[i]->getVal() == grilleSolution.colonnes[co - 1].tabcl[i]->getVal()) {
						scoreCol = scoreCol * 2;
					}
					if (grilleJeu.carres[trouverNumeroCarre(li, co) - 1].tabc[i]->getVal() == grilleSolution.carres[trouverNumeroCarre(li, co) - 1].tabc[i]->getVal()) {
						scoreCar = scoreCar * 2;
					}
				}
				tabDiffCase[(co - 1) * dimGrille + (li - 1) + dimGrille * dimGrille] = scoreCar + scoreCol + scoreLi;
				//std::cout << "La case " << (int)li << " " << (int)co << " a un score de: " << (int)tabDiffCase[(co - 1) * dimGrille + (li - 1)] << endl;

				//version nombre d'indice different
				bool* liste_val = new bool[dimGrille];//les valeur a true sont les valeurs possible pour la case (liste_val[0] == true veux dire que 1 est une valeur possible, liste_val[1] == false veux dire que 2 n'est pas  une valeur possible...)
				for (unsigned char i = 0; i < dimGrille; i++) {
					liste_val[i] = true;
				}
				for (unsigned char i = 0; i < dimGrille; i++) {
					if (grilleJeu.lignes[li - 1].tabl[i]->getVal() == grilleSolution.lignes[li - 1].tabl[i]->getVal()) {
						liste_val[grilleJeu.lignes[li - 1].tabl[i]->getVal() - 1] = false;
					}
					if (grilleJeu.colonnes[co - 1].tabcl[i]->getVal() == grilleSolution.colonnes[co - 1].tabcl[i]->getVal()) {
						liste_val[grilleJeu.colonnes[co - 1].tabcl[i]->getVal() - 1] = false;
					}
					if (grilleJeu.carres[trouverNumeroCarre(li, co) - 1].tabc[i]->getVal() == grilleSolution.carres[trouverNumeroCarre(li, co) - 1].tabc[i]->getVal()) {
						liste_val[grilleJeu.carres[trouverNumeroCarre(li, co) - 1].tabc[i]->getVal() - 1] = false;
					}
				}
				tabDiffCase[(co - 1) * dimGrille + (li - 1)] = dimGrille;
				for (unsigned char i = 0; i < dimGrille; i++) {
					if (liste_val[i]) {
						tabDiffCase[(co - 1) * dimGrille + (li - 1)] --;
					}
				}

			}
			else {
				tabDiffCase[(co - 1) * dimGrille + (li - 1)] = 0;
			}
		}
	}
}


unsigned char JeuPasAPas::getDiffCase(unsigned char l, unsigned char c, bool diff_type)//diff type = 1: retourne le nombre de valeur possible, diff type = 0, retourne "la tendance a avoir bcp de chiffre dans un meme bloc/ligne/col permet de departager en les diff type = 1 egaux 
{
	unsigned char dimGrille = grilleJeu.dim;
	if (diff_type) {
		return tabDiffCase[(c - 1) * dimGrille + (l - 1)];
	}
	return tabDiffCase[(c - 1) * dimGrille + (l - 1) + dimGrille * dimGrille];
}

void JeuPasAPas::coordCaseSimple(unsigned char& l, unsigned char& c)
{
	unsigned char dimGrille = grilleJeu.dim;
	updateDiffCase();
	unsigned char l_f = 1;
	unsigned char c_f = 1;
	unsigned char max = getDiffCase(1, 1);
	for (unsigned char li = 1; li <= dimGrille; ++li) {
		for (unsigned char co = 2; co <= dimGrille; ++co) {
			unsigned char value = getDiffCase(li, co);
			if (value > max) {
				max = getDiffCase(li, co);
				l_f = li;
				c_f = co;
			}
			else if (value == max) {
				if (getDiffCase(li, co) > getDiffCase(l_f, c_f)) {
					l_f = li;
					c_f = co;
				}
			}
		}
	}
	l = l_f;
	c = c_f;

}

void JeuPasAPas::printTabDiff() const {

	for (int l = 0; l < grilleJeu.dim; l++) {
		for (int c = 0; c < grilleJeu.dim; c++) {
			cout << "tabDiffCase[" << l + 1 << "][" << c + 1 << "] = " << (int)tabDiffCase[c * grilleJeu.dim + l] << endl;
		}
	}
}

void JeuPasAPas::retirerCasesFausses()
{
	unsigned char dimGrille = grilleJeu.dim;
	for (unsigned char li = 0; li < dimGrille; ++li) {
		for (unsigned char co = 0; co < dimGrille; ++co) {
			if (grilleJeu.grille.getCase(li, co).getVal() != grilleSolution.grille.getCase(li, co).getVal()) {
				grilleJeu.grille.getCase(li, co).setVal(0);

			}
		}
	}
}

void JeuPasAPas::colorerCase() {
	if (coloration) {
		for (int l = 0; l < grilleJeu.dim; l++) {
			for (int c = 0; c < grilleJeu.dim; c++) {
				if (grilleJeu.grille.getCase(l, c).getVal() != 0 && grilleJeu.grille.getCase(l, c).modifiable && grilleJeu.grille.getCase(l, c).etat != 3) {
					if (grilleJeu.grille.getCase(l, c).getVal() == grilleSolution.grille.getCase(l, c).getVal()) {
						grilleJeu.grille.getCase(l, c).etat = 1;
					}
					else {
						grilleJeu.grille.getCase(l, c).etat = 2;
					}
				}
			}
		}
	}
	else {
		for (int l = 0; l < grilleJeu.dim; l++) {
			for (int c = 0; c < grilleJeu.dim; c++) {
				if (grilleJeu.grille.getCase(l, c).etat != 3) {
					grilleJeu.grille.getCase(l, c).etat = 0;
				}
			}
		}
	}
}

//---------Class chronometre

chronometre::chronometre()
{
	ms = 0;
	t1 = clock();
	t2 = clock();
	enPause = true;

}

chronometre::chronometre(unsigned long int ms)
{
	this->ms = ms;
	t1 = clock();
	t2 = clock();
	enPause = true;

}

void chronometre::forceTime(unsigned long int ms)
{
	this->ms = ms;
	t1 = clock();
	t2 = clock();
}

chronometre::~chronometre()
{
}

void chronometre::update()
{
	if (!enPause) {
		t2 = clock();
		ms = ms + ((t2 - t1) * 1000 / CLOCKS_PER_SEC);
		t1 = clock();
	}
}

void chronometre::start()
{	
	if (enPause) {
		enPause = false;
		t1 = clock();
		update();
	}
}

void chronometre::pause()
{
	if (!enPause) {
		update();
		enPause = true;
	}
}

void chronometre::reset()
{
	ms = 0;
	pause();
}

unsigned long int chronometre::getTimeInMSec()
{
	update();
	return ms;
}

unsigned long int chronometre::getTimeInSec()
{
	return (unsigned long int) getTimeInMSec() /1000;
}

unsigned long int chronometre::getTimeInMin()
{
	return (unsigned long int) getTimeInSec()/60;
}

unsigned long int chronometre::getTimeInHours()
{
	return (unsigned long int) getTimeInMin()/60;
}

void chronometre::afficher()
{
	cout << getTimeInHours() << "h " << getTimeInMin() % 60 << "m " << getTimeInSec() % 60 << "s " << getTimeInMSec() % 1000<< "ms";
}

bool chronometre::estEnPause()
{
	return enPause;
}
