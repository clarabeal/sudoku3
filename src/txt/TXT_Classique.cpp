#include "TXT_Classique.h"

#include <iostream>
#include "../core/Jeu.h"
#include <stdlib.h>

using namespace std;

TXT_Classique::TXT_Classique (unsigned char d) : jeu(d) {

}
TXT_Classique::TXT_Classique(unsigned char d, Grille& g_sol, Grille& g_orig, Grille& g_jeu) : jeu(d, g_sol, g_orig, g_jeu) {
}
TXT_Classique::~TXT_Classique () {

}

void TXT_Classique::termClear() const  // efface le terminal
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
    if (!jeu.initDone) {
        jeu.init();
        jeu.initDone = true;
    }
    do {
        termClear();
        
        jeu.grilleJeu.grille.print();

        do {
            //saisie de la valeur à placer 
            
            cout<<"Quelle valeur voulez-vous placer ? | Menu : 0" << endl;
            cin >> valeurEntree;
            if (!jeu.estValValide((unsigned char)valeurEntree)) {
                unsigned char resMenu = menu();
                if (resMenu == 0) {
                    jeu.grilleJeu.grille = jeu.grilleOriginale.grille;
                    termClear();
                    jeu.grilleJeu.grille.print();
                }
                else if (resMenu == 1) {
                    jeu.init();
                    termClear();
                    jeu.grilleJeu.grille.print();
                }
                else if (resMenu == 2) {
                    termClear();
                    cout << "ABANDON: partie terminee !" << endl << "Votre Grille : "<<endl;
                    jeu.grilleJeu.grille.print();
                    cout << endl;
                    cout << "Grille solution :" << endl;
                    jeu.grilleSolution.grille.print();
                    stop = true;
                }
                valeurEntree = 0;
            }
           
        } while (!jeu.estValValide((unsigned char)valeurEntree) && !stop);//tant qu'elle n'est pas valide 
        if (!stop) {
            do {
                //saisie des coordonnees de la case ou on veut placer valeur
                cout << "Ou voulez-vous placer votre prochaine valeur ?" << endl << "l : " << endl;;
                cin >> l;
                cout << "c : " << endl;
                cin >> c;
            } while (!jeu.sontCorValides((unsigned char)l, (unsigned char)c)); //verif coord ok et case modifiable

            jeu.grilleJeu.setCase(l - 1, c - 1, valeurEntree); //on place la valeur dans la grille

            if (jeu.verifGrillePleine(jeu.grilleJeu)) {
                stop = true;
                termClear();
                cout << "Grille remplie : partie terminee !" << endl<< "Votre grille :"<<endl;
                jeu.grilleJeu.grille.print();
                cout << endl;
                cout << "Grille solution :" << endl;
                jeu.grilleSolution.grille.print();
                cout<<"Vous avez fait "<<jeu.nbErreurs()<<" erreurs"<<endl;
                //on affiche la solution et la grille remplie par le joueur côte à côte
            }
        }

    } while (!stop);
}

unsigned char TXT_Classique::menu() const {
    int value;

    do {
        termClear();
        jeu.grilleJeu.grille.print();
        cout << "||||||||||||||||||||||||||||| MENU | SUDOKU 3 ||||||||||||||||||||||||||||||" << endl;
        cout << "||                                                                        ||" << endl;
        cout << "|| 0: Recommencer la meme grille                                          ||" << endl;
        cout << "|| 1: Generer une nouvelle grille                                          ||" << endl;
        cout << "|| 2: Abandonner la partie et afficher la solution                        ||" << endl;
        cout << "|| 3: Retour au jeu                                                       ||" << endl;
        cout << "||                                                                        ||" << endl;
        cout << "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
        cin >> value;
    } while (value < 0 || value > 3);

    termClear();
    jeu.grilleJeu.grille.print();
    return value;
}
