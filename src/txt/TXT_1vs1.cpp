#include "TXT_1vs1.h"

#include <stdlib.h>
#include <iostream>

using namespace std;

TXT_1vs1::TXT_1vs1(unsigned char d) : jeu(d), grilleJ1(d), grilleJ2(d), gestionnaireSauvegarde("data/saves/", "../data/saves/"){
    nbErreurJ1 = 0;
    nbErreurJ2 = 0;
    stopBoucleJ1 = false;
    stopBoucleJ2 = false;
}
TXT_1vs1::TXT_1vs1(unsigned char d, int id, unsigned long int time, Grille& g_sol, Grille& g_orig, Grille& g_jeu, Grille& grilleJ1_, Grille& grilleJ2_, unsigned long int chronoJ1_, unsigned long int chronoJ2_, int nbErrJ1, int nbErrj2, bool stopJ1, bool stopJ2) : jeu(d, id, time, g_sol, g_orig, g_jeu), grilleJ1(d), grilleJ2(d), gestionnaireSauvegarde("data/saves/", "../data/saves/") {
    nbErreurJ1 = nbErrJ1;
    nbErreurJ2 = nbErrj2;
    stopBoucleJ1 = stopJ1;
    stopBoucleJ2 = stopJ2;
    chronoJ1.forceTime(chronoJ1_);
    chronoJ2.forceTime(chronoJ2_);
    grilleJ1 = grilleJ1_;
    grilleJ2 = grilleJ2_;
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

    
    bool stop = false;
    bool valOK = false;
    bool choix;
    int valeurEntree, l, c;
    unsigned char resMenu;

    int dim = jeu.grilleJeu.dim;

    if (!jeu.initDone) {
        jeu.init();
        cout << "Grille generee"<<endl;
        jeu.initDone = true;
        jeu.chrono.start();
        chronoJ1.reset();

    }

    
    //Premiere boucle de jeu
    /*On reste ds cette boucle tant que J1 n'a pas rempli la grille en entier*/
    chronoJ2.pause();
    chronoJ1.start();
    while (!stopBoucleJ1) {

        termClear();
        jeu.grilleJeu.grille.print();

        //Saisie de la valeur a placer
        do {
            cout << "J1 : Quelle valeur voulez-vous placer ? | Menu : " << dim + 1 << endl;
            cin >> valeurEntree;

            //Verification que la valeur saisie est OK
            if (jeu.estValValide((unsigned char)valeurEntree) || (valeurEntree == dim + 1)) {
                valOK = true;
            }

        } while (!valOK && !stop);
        //Si le joueur fait appel a une des fonctionnalites du menu
        if (valeurEntree == dim + 1) {
            resMenu = menu();
            switch (resMenu) {
            case 0:
                //Recommencer la meme grille
                jeu.grilleJeu.grille = jeu.grilleOriginale.grille;
                termClear();
                jeu.grilleJeu.grille.print();
                cout << endl;
                break;
            case 1:
                //Generer une nouvelle grille
                jeu.init();
                termClear();
                jeu.grilleJeu.grille.print();
                cout << endl;
                break;
            case 2:
                //Abandonner et afficher solution
                termClear();
                cout << "Abandon : partie terminee !" << endl << "Votre Grille :" << endl;
                jeu.grilleJeu.grille.print();
                cout << endl << "Grille solution :" << endl;
                jeu.grilleSolution.grille.print();
                stopBoucleJ1 = true;
                stop = true;
                break;
            case 3:

                if (jeu.sauvegardeId == 0) {

                    cout << "Nom de la sauvegarde(sans espace): ";
                    string name;
                    cin >> name;
                    jeu.sauvegardeId = gestionnaireSauvegarde.sauvegarder(jeu, name, 3, 0, &grilleJ1, &grilleJ2, &chronoJ1, &chronoJ2, nbErreurJ1, nbErreurJ2, stopBoucleJ1, stopBoucleJ2);
                    termClear();
                    jeu.grilleJeu.grille.print();
                    cout << "Votre temps ";
                    jeu.chrono.afficher();
                    cout << endl;
                    if (jeu.sauvegardeId != 0) {
                        cout << "La partie a bien ete sauvegardee" << endl;
                    }
                    else {
                        cout << "La partie n'a pas pu etre sauvegardee" << endl;
                    }
                }
                else {

                    jeu.sauvegardeId = gestionnaireSauvegarde.sauvegarder(jeu, "", 3, jeu.sauvegardeId, &grilleJ1, &grilleJ2, &chronoJ1, &chronoJ2, nbErreurJ1, nbErreurJ2, stopBoucleJ1, stopBoucleJ2);
                    termClear();
                    jeu.grilleJeu.grille.print();
                    cout << "Votre temps ";
                    jeu.chrono.afficher();
                    cout << endl;
                    if (jeu.sauvegardeId != -1) {
                        cout << "La partie a bien ete sauvegardee (sauvegarde deja existente mise a jour) | nom: " << gestionnaireSauvegarde.getInfoSauvegarde(jeu.sauvegardeId).name << endl;
                    }
                    else {
                        cout << "La partie n'a pas pu etre sauvegardee" << endl;
                    }
                }
                break;
            case 4:
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
                if (choix) { return; stop = true; stopBoucleJ1 = true; }
                else {
                    termClear();
                    jeu.grilleJeu.grille.print();
                    cout << endl;
                }
                break;
            default:
                //Retour au jeu
                cout << "Retour au jeu !" << endl;
                break;
            }
        }
        else {
            //placement de la valeur, etc
            //grille pleine -> enregistrement
            do {
                cout << "J1 : Sur quelle ligne ? " << endl;
                cin >> l;
                cout << "J1 : Et quelle colonne ?" << endl;
                cin >> c;
            } while (!jeu.sontCorValides(l, c));

            jeu.grilleJeu.setCase(l - 1, c - 1, valeurEntree); //on place la valeur ds la grille
        }
         //Si la grille est pleine
         if (jeu.verifGrillePleine(jeu.grilleJeu)) {
                termClear();
                jeu.grilleJeu.grille.print();
                chronoJ2.reset();
                chronoJ1.pause();
                stopBoucleJ1 = true;
                nbErreurJ1 = jeu.nbErreurs();
                //On copie la grille dans une grille temporaire
                grilleJ1 = jeu.grilleJeu;         
                //On remet la grille de jeu comme au départ
                jeu.grilleJeu = jeu.grilleOriginale;
                cout << "J1 : Grille remplie : au tour du joueur suivant !" << endl;
                jeu.chrono.reset();
                jeu.chrono.start();
         }
    }

    
    //Deuxième boucle de jeu
    chronoJ1.pause();
    chronoJ2.start();

    while (!stopBoucleJ2){

            termClear();
            jeu.grilleJeu.grille.print();

            do {
                cout << "J2 : Quelle valeur voulez-vous placer ? | Menu : " << dim + 1 << endl;
                cin >> valeurEntree;

                //Verification que la valeur saisie est OK
                if (jeu.estValValide((unsigned char)valeurEntree) || (valeurEntree == dim + 1)) {
                    valOK = true;
                }

            } while (!valOK && !stop);

            if (valeurEntree == dim + 1) {
                
                resMenu = menu();
                switch (resMenu) {
                case 0:
                    //Recommencer la meme grille
                    jeu.grilleJeu.grille = jeu.grilleOriginale.grille;
                    termClear();
                    jeu.grilleJeu.grille.print();
                    cout << endl;
                    break;
                case 1:
                    termClear();
                    cout << "Option Indisponible dans ce mode de jeu!"<<endl;
                    jeu.grilleJeu.grille.print();
                    cout << endl;
                    break;
                case 2:
                    //Abandonner et afficher solution
                    termClear();
                    cout << "Option Indisponible dans ce mode de jeu!" << endl;
                    jeu.grilleJeu.grille.print();
                    break;
                case 3:
                    
                    if (jeu.sauvegardeId == 0) {

                        cout << "Nom de la sauvegarde(sans espace): ";
                        string name;
                        cin >> name;
                        jeu.sauvegardeId = gestionnaireSauvegarde.sauvegarder(jeu, name, 3, 0, &grilleJ1, &grilleJ2, &chronoJ1, &chronoJ2, nbErreurJ1, nbErreurJ2, stopBoucleJ1, stopBoucleJ2);
                        termClear();
                        jeu.grilleJeu.grille.print();
                        cout << "Votre temps ";
                        jeu.chrono.afficher();
                        cout << endl;
                        if (jeu.sauvegardeId != 0) {
                            cout << "La partie a bien ete sauvegardee" << endl;
                        }
                        else {
                            cout << "La partie n'a pas pu etre sauvegardee" << endl;
                        }
                    }
                    else {

                        jeu.sauvegardeId = gestionnaireSauvegarde.sauvegarder(jeu, "", 3, jeu.sauvegardeId, &grilleJ1, &grilleJ2, &chronoJ1, &chronoJ2, nbErreurJ1, nbErreurJ2, stopBoucleJ1, stopBoucleJ2);
                        termClear();
                        jeu.grilleJeu.grille.print();
                        cout << "Votre temps ";
                        jeu.chrono.afficher();
                        cout << endl;
                        if (jeu.sauvegardeId != -1) {
                            cout << "La partie a bien ete sauvegardee (sauvegarde deja existente mise a jour) | nom: " << gestionnaireSauvegarde.getInfoSauvegarde(jeu.sauvegardeId).name << endl;
                        }
                        else {
                            cout << "La partie n'a pas pu etre sauvegardee" << endl;
                        }
                    }
                    break;
                case 4:
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
                    if (choix) { return; }
                    else {
                        termClear();
                        jeu.grilleJeu.grille.print();
                        cout << endl;
                    }
                    break;
                default:
                    //Retour au jeu
                    cout << "Retour au jeu !" << endl;
                    break;
                }
            }
            else {
                //placement de la valeur, etc
                //grille pleine -> affichage des grilles et solution

                do {
                    cout << "J2 : Sur quelle ligne ? " << endl;
                    cin >> l;
                    cout << "J2 : Et quelle colonne ?" << endl;
                    cin >> c;
                } while (!jeu.sontCorValides(l, c));

                jeu.grilleJeu.setCase(l - 1, c - 1, valeurEntree); //on place la valeur ds la grille
            }
            //Si la grille est pleine
            if (jeu.verifGrillePleine(jeu.grilleJeu)) {
                chronoJ2.pause();
                stopBoucleJ2 = true;
                nbErreurJ2 = jeu.nbErreurs();
                grilleJ2 = jeu.grilleJeu;
                termClear();                
            }
        }

    cout << "J2 : Grille remplie : partie terminée !" << endl;

    cout << endl << "Grille du joueur 1 :" << endl;
    grilleJ1.grille.print();
    cout << endl << "J1 a fait " << nbErreurJ1 << " erreur(s) en ";
    chronoJ1.afficher();
    cout << endl;

    cout << endl << "Grille du joueur 2 :" << endl;
    grilleJ2.grille.print();
    cout << endl << "J2 a fait " << nbErreurJ2 << " erreur(s) en ";
    chronoJ2.afficher();
    cout << endl;

    cout << endl << "Grille solution :" << endl;
    jeu.grilleSolution.grille.print();
}

unsigned char TXT_1vs1::menu (){
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
        cout << "|| 3: Sauvegarder                                                         ||" << endl;
        cout << "|| 4: Quitter la partie et revenir au menu                                ||" << endl;
        cout << "|| 5: Retour au jeu                                                       ||" << endl;
        cout << "||                                                                        ||" << endl;
        cout << "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
        cin >> value;
    } while (value < 0 || value > 5);

    termClear();
    jeu.grilleJeu.grille.print();
    return value;
}