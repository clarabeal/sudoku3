#include "TXT_Classique.h"

#include <iostream>
#include "../core/Jeu.h"
#include <stdlib.h>

using namespace std;

TXT_Classique::TXT_Classique (unsigned char d) : jeu(d) {

}

TXT_Classique::~TXT_Classique () {

}

void termClear()  // efface le terminal
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}


void TXT_Classique::boucle () {
    //On efface le terminal
    //On intitialise une grille solution
   // On cree une grille de jeu
    //Dans la boucle :
   // On affiche la grille de jeu
    //Tant que la grille n'est pas pleine ou que l'utilisateur ne veut pas quitter
    //Systeme de question reponse : quelle nb placer? a quelle coordonnées?
    //Grille pleine on compare a la grille solution et on indique le nb d'erreurs
    

    bool stop = false; //boleen indiquant si la boucle de jeu doit continuer ou pas
    int valeurEntree,l,c; //entier stockant les valeurs entrees en cin (valeur a placer et emplacement choisi par exemple)

    jeu.init();
    do {
        termClear();
        
        jeu.grilleJeu.grille.print();

        do {
            //saisie de la valeur à placer 
            
            cout<<"Quelle valeur voulez-vous placer ? | Menu | Recommencer: " << jeu.grilleJeu.dim + 1 << ", Generer une nouv. grille: "<< jeu.grilleJeu.dim + 2 <<", Abandonner: "<< jeu.grilleJeu.dim + 3<< endl;
            cin >> valeurEntree;
            if (!jeu.estValValide((unsigned char)valeurEntree)) {
                termClear();
                if (valeurEntree == jeu.grilleJeu.dim + 1) {
                    jeu.grilleJeu.grille = jeu.grilleOriginale.grille;
                    termClear();
                    jeu.grilleJeu.grille.print();
                }
                else if (valeurEntree == jeu.grilleJeu.dim + 2) {
                    jeu.init();
                    termClear();
                    jeu.grilleJeu.grille.print();
                }
                else if (valeurEntree == jeu.grilleJeu.dim + 3) {
                    cout << "ABANDON: partie terminee !" << endl << "Votre Grille: "<<endl;
                    jeu.grilleJeu.grille.print();
                    cout << endl;
                    cout << "Grille solution :" << endl;
                    jeu.grilleSolution.grille.print();
                    //on affiche la solution et la grille remplie par le joueur côte à côte
                    stop = true;
                }
                valeurEntree = 0;
            }
           
        } while (!jeu.estValValide((unsigned char)valeurEntree));//tant qu'elle n'est pas valide 
        if (!stop) {
            do {
                //saisie des coordonnees de la case ou on veut placer valeur
                cout << "Ou voulez-vous placer votre prochaine valeur ?" << endl << "l : " << endl;;
                cin >> l;
                cout << "c : " << endl;
                cin >> c;
            } while (!jeu.sontCorValides((unsigned char)l, (unsigned char)c)); //verif coord ok et case vide

            jeu.grilleJeu.setCase(l - 1, c - 1, valeurEntree); //on place la valeur dans la grille

            if (jeu.verifGrillePleine(jeu.grilleJeu)) {
                stop = true;
                cout << "Grille remplie : partie terminee !" << endl<< "Votre grille:"<<endl;
                jeu.grilleJeu.grille.print();
                cout << endl;
                cout << "Grille solution :" << endl;
                jeu.grilleSolution.grille.print();
                //on affiche la solution et la grille remplie par le joueur côte à côte
            }
        }

    } while (!stop);
}
