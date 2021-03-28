#include "TXT_Classique.h"

#include <iostream>
#include "../core/GrilleDeJeu.h"
#include <stdlib.h>

using namespace std;

TXT_Classique::TXT_Classique (unsigned char d) : jeu(d) {

}

TXT_Classique::~TXT_Classique () {

}
/*
void termClear()  // efface le terminal
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}*/

void TXT_Classique::afficherGrille () {
    jeu.grilleJeu.grille.print();
}

/*
void TXT_Classique::boucle () {
    On efface le terminal
    On intitialise une grille solution
    On cree une grille de jeu
    Dans la boucle :
    On affiche la grille de jeu
    Tant que la grille n'est pas pleine ou que l'utilisateur ne veut pas quitter
    Systeme de question reponse : quelle nb placer? a quelle coordonnées?
    Grille pleine on compare a la grille solution et on indique le nb d'erreurs
    

    bool stop = false; //boleen indiquant si la boucle de jeu doit continuer ou pas
    int valeurEntree; //entier stockant les valeurs entrees en cin (valeur a placer et emplacement choisi par exemple)

    jeu.genererGrillePleine();
    jeu.genererGrilleMinimale();

    do {
        termClear();
        
        afficherGrille();

        do {
            //saisie de la valeur à placer (soit on numerote les cases soit coord en x et y)
            cout<<"Quelle valeur voulez-vous placer ?"<<endl;
            cin>>valeurEntree;
        } while ();//tant qu'elle nest pas valide 

        //il faut ajouter une fonction coordValide et valValide dans Jeu 

        do {
            //saisie des coordonnees de la case ou on veut placer valeur
            cout<<"Ou voulez-vous placer votre prochaine valeur ?"<<endl;
            cin>>valeurEntree;
        } while (); //verif coord ok et case vide

        if (jeu.verifGrillePleine()) {
            cout<<"Grille remplie : partie terminee !"<<endl;
            //on affiche la solution et la grille remplie par le joueur côte à côte
        }

    } while (!stop);
}

//FONCTIONS A AJOUTER DANS LE MODULE JEU

bool Jeu::estValValide (unsigned char valeur) {
    //une valeur valide est comprise entre 1 et dim
    return (valeur>0 && valeur<=grilleJeu.dim);
}

bool Jeu::estCoordValide (unsigned char coord) {
    //une coord est valide si elle est contenue entre 0 et dim*dim strictement et si elle indique une case encore vide

}

*/