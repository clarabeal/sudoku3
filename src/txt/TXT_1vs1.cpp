#include "TXT_1vs1.h"
#include "../core/Grille.h"
#include <stdlib.h>
#include <iostream>

using namespace std;

TXT_1vs1::TXT_1vs1(unsigned char d) : jeu(d) {
}

TXT_1vs1::~TXT_1vs1 () {
}

void TXT_1vs1::termClear () const {

#ifdef _WIN32
    system("cls");  
#else
    system("clear");
#endif
}

void TXT_1vs1::boucle () {

    /*
    DESCRIPTIF DE LA BOUCLE
    Le joueur 1 remplit sa grille de jeu
    On enregistre la grille remplie par le joueur 1
    Le joueur 2 remplit a son tour la grille de jeu
    On affiche la grille de chacun des joueurs ainsi que la grille solution
    Ajout des chronos dans un deuxieme temps
    */

    bool stop1 = false;
    bool stop2 = false;
    bool stop = false;
    bool valOK = false;
    bool choix;
    int valeurEntree, l, c, nb1, nb2;
    unsigned char resMenu;

    int dim = jeu.grilleJeu.dim;

    //La grille qu'on utilise pour stocker celle de J1
    Grille grilleJ1 (dim);

    if (!jeu.initDone) {
        jeu.init();
        cout << "Grille generee"<<endl;
        jeu.initDone = true;
    }

    //BOUCLE DE JEU PRINCIPALE
    do {
        //Premiere boucle de jeu
        /* On reste ds cette boucle tant que J1 n'a pas rempli la grille en entier
        */
        do {

            termClear();
            jeu.grilleJeu.grille.print();

            //Saisie de la valeur a placer
            do {
                cout << "J1 : Quelle valeur voulez-vous placer ? | Menu : "<<dim + 1<< endl;
                cin >> valeurEntree;

                //Verification que la valeur saisie est OK
                if (jeu.estValValide((unsigned char)valeurEntree) || (valeurEntree == dim + 1)) {
                    valOK = true;
                }
            
            } while (!valOK && !stop);
                //Si le joueur fait appel a une des fonctionnalites du menu
                if (valeurEntree == dim + 1) {
                resMenu = menu ();
                switch (resMenu) {
                    case 0 :
                        //Recommencer la meme grille
                        jeu.grilleJeu.grille = jeu.grilleOriginale.grille;
                        termClear();
                        jeu.grilleJeu.grille.print();
                        cout<<endl;
                        break;
                    case 1 :
                        //Generer une nouvelle grille
                        jeu.init();
                        termClear();
                        jeu.grilleJeu.grille.print();
                        cout<<endl;
                        break;
                    case 2 :
                        //Abandonner et afficher solution
                        termClear();
                        cout<<"Abandon : partie terminee !"<<endl<<"Votre Grille :"<<endl;
                        jeu.grilleJeu.grille.print();
                        cout<<endl<<"Grille solution :"<<endl;
                        jeu.grilleSolution.grille.print();
                        stop1= true;
                        stop = true;
                        break;
                    case 3 :
                        //Quitter et retour au menu
                        do {
                            termClear();
                            cout << "||||||||||||||||||||||||||||||||| SUDOKU 3 |||||||||||||||||||||||||||||||||" << endl;
                            cout << "||                                                                        ||" << endl;
                            cout << "|| Voulez vous vraiment quitter la partie?                                ||" << endl;
                            cout << "||                                                                        ||" << endl;
                            cout << "|| 1: OUI                                                                 ||" << endl;
                            cout << "|| 0: NON                                                                 ||" << endl;
                            cout << "||                                                                        ||" << endl;
                            cout << "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
                            cout << "Votre choix: ";
                            cin >> choix;

                        } while (choix != 0 && choix != 1);
                        if (choix) { stop = true; stop1 = true; }
                        else {
                            termClear();
                            jeu.grilleJeu.grille.print();
                            cout<<endl;
                        }
                        break;
                     default :
                        //Retour au jeu
                        cout<<"Retour au jeu !"<<endl;
                        break;
                }   
            }
            //placement de la valeur, etc
            //grille pleine -> enregistrement
            do {
                cout<<"J1 : Sur quelle ligne ? "<<endl;
                cin >>l;
                cout<<"J1 : Et quelle colonne ?"<<endl;
                cin >> c;
            } while (!jeu.sontCorValides(l, c));
                
            jeu.grilleJeu.setCase(l - 1, c - 1, valeurEntree); //on place la valeur ds la grille

            //Si la grille est pleine
            if (jeu.verifGrillePleine(jeu.grilleJeu)) {
                termClear();
                jeu.grilleJeu.grille.print();
                stop1 = true;
                nb1 = jeu.nbErreurs();
                //On copie la grille dans une grille temporaire
                grilleJ1 = jeu.grilleJeu;
                //On remet la grille de jeu comme au départ
                jeu.grilleJeu = jeu.grilleOriginale;
                
            }
        } while (!stop1);

        cout<<"J1 : Grille remplie : au tour du joueur suivant !"<<endl;

        //Deuxième boucle de jeu
        do {

            termClear();
            jeu.grilleJeu.grille.print();

            do {
                //saisie de la valeur a placer
                cout << "J2 : Quelle valeur voulez-vous placer ?"<< endl;
                cin >> valeurEntree;

            } while (!jeu.estValValide((unsigned char)valeurEntree) && !stop);

            //placement de la valeur, etc
            //grille pleine -> affichage des grilles et solution

            do {
                cout<<"J2 : Sur quelle ligne ? "<<endl;
                cin >>l;
                cout<<"J2 : Et quelle colonne ?"<<endl;
                cin >> c;
            } while (!jeu.sontCorValides(l, c));
                
            jeu.grilleJeu.setCase(l - 1, c - 1, valeurEntree); //on place la valeur ds la grille

            //Si la grille est pleine
            if (jeu.verifGrillePleine(jeu.grilleJeu)) {
                stop = true;
                stop2 = true;

                nb2 = jeu.nbErreurs();
                termClear();

                cout<<"J2 : Grille remplie : partie terminée !"<<endl;
                    
                cout<<endl<<"Grille du joueur 1 :"<<endl;
                grilleJ1.grille.print();
                cout<<endl<<"J1 a fait "<<nb1<<" erreur(s)"<<endl;

                cout<<endl<<"Grille du joueur 2 :"<<endl;
                jeu.grilleJeu.grille.print();
                cout<<endl<<"J2 a fait "<<nb2<<" erreur(s)"<<endl;

                cout<<endl<<"Grille solution :"<<endl;
                jeu.grilleSolution.grille.print();
            }
        } while (!stop2);  
    } while (!stop);
}

unsigned char TXT_1vs1::menu () const {
    int value;

    do {
        termClear();
        jeu.grilleJeu.grille.print();
        //cout << "Votre temps ";
        //jeu.chrono.afficher();
        cout << endl;
        cout << "||||||||||||||||||||||||||||| MENU | SUDOKU 3 ||||||||||||||||||||||||||||||" << endl;
        cout << "||                                                                        ||" << endl;
        cout << "|| 0: Recommencer la meme grille                                          ||" << endl;
        cout << "|| 1: Generer une nouvelle grille                                         ||" << endl;
        cout << "|| 2: Abandonner la partie et afficher la solution                        ||" << endl;
        cout << "|| 3: Quitter la partie et revenir au menu                                ||" << endl;
        cout << "|| 4: Retour au jeu                                                       ||" << endl;
        cout << "||                                                                        ||" << endl;
        cout << "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
        cin >> value;
    } while (value < 0 || value > 4);

    termClear();
    jeu.grilleJeu.grille.print();
    return value;
}