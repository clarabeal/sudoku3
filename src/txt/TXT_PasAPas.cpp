#include "TXT_PasAPas.h"

#include <stdlib.h>
#include <iostream>
#include <string>
using namespace std;

TXT_PasAPas::TXT_PasAPas(unsigned char d, int id, unsigned long int time, Grille& g_sol, Grille& g_orig, Grille& g_jeu) : jeu(d, id, time, g_sol, g_orig, g_jeu) {

}

TXT_PasAPas::TXT_PasAPas(unsigned char d) : jeu(d) {

}

TXT_PasAPas::~TXT_PasAPas() {
 
}

void TXT_PasAPas::termClear() const  // efface le terminal
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void TXT_PasAPas::boucle() {
    unsigned char dimGrille = jeu.grilleJeu.dim;
    bool stop = false; //booleen indiquant si la boucle de jeu doit continuer ou pas
    int valeur;
    int l,c;

    if (!jeu.initDone) {
        jeu.init();
        cout << "grille generé";
      
    }
    do {
        termClear();
        jeu.grilleJeu.grille.print();
        cout << "Votre temps ";
        jeu.chrono.afficher();
        cout << endl;
        
        bool aideRemplir = false; //booleen indiquant si le joueur a besoin d'aide pour que le solveur remplisse une case à sa place (case au hasard ou la plus facile à placer?)
        bool aideCoor = false;
        bool valValide = false;

        do{
            cout <<"Quelle valeur voulez-vous placer ? | Menu: " << jeu.grilleJeu.dim+1  << endl;
            cin >> valeur;
            if(valeur == jeu.grilleJeu.dim + 1){
                jeu.chrono.update();// On met le chrono en pause 
                unsigned char menuRes = menu();
                if (menuRes == 0) {
                    //donne les coordonnées de la case la plus simple à trouver
                    unsigned char l_simple, c_simple;
                    jeu.coordCaseSimple(l_simple, c_simple);
                    l = (int)l_simple;
                    c = (int)c_simple;
                    //jeu.printTabDiff();
                    cout << "[" << l << "][" << c << "] est facile a remplir il n'y a que " << dimGrille - jeu.tabDiffCase[(c - 1) * dimGrille + (l - 1)] << " possibilite(s)" <<   endl;
                    bool stop_place_chiffre_facile = false;
                    do {
                        cout << "Quelle valeur voulez-vous mettre a cette position? | Annuler : " << jeu.grilleJeu.dim + 1 << endl;
                        cin >> valeur;
                        if (valeur == jeu.grilleJeu.dim + 1){
                            stop_place_chiffre_facile = true;
                            aideCoor = true;
                            termClear();
                            jeu.grilleJeu.grille.print();
                            cout << "Votre temps ";
                            jeu.chrono.afficher();
                            cout << endl;
                            cout << "[" << l << "][" << c << "] est facile a remplir il n'y a que " << dimGrille - jeu.tabDiffCase[(c - 1) * dimGrille + (l - 1)] << " possibilite(s)" << endl;
                        }

                    } while (!jeu.estValValide((unsigned char)valeur) && !stop_place_chiffre_facile); //tant que la valeur n'est pas valide

                    aideCoor = !aideCoor;

                }
                else if (menuRes == 1) {

                    do { //remplit une case au hasard

                        l = rand() % jeu.grilleJeu.dim + 1;
                        c = rand() % jeu.grilleJeu.dim + 1;

                        cout << "l :" << l << "c :" << c << endl;

                        valeur = jeu.grilleJeu.grille.getCase(l - 1, c - 1).getVal();

                        if (valeur == 0) { //place la valeur si la case est vide
                            jeu.grilleJeu.setCase(l - 1, c - 1, jeu.grilleSolution.grille.getCase(l - 1, c - 1).getVal());
                            aideRemplir = true; //aide à savoir si la valeur à été placée
                        }

                    } while (aideRemplir == false);
                    jeu.grilleJeu.grille.getCase(l - 1, c - 1).modifiable = false;
                    cout << "[" << l << "][" << c << "] a été remplit automatiquement" << endl;
                }
                else if (menuRes == 2) {
                    jeu.grilleJeu.grille = jeu.grilleOriginale.grille;
                    termClear();
                    jeu.grilleJeu.grille.print();
                    cout << "Votre temps ";
                    jeu.chrono.afficher();
                    cout << endl;
                }
                else if (menuRes == 3) {
                    jeu.init();
                    termClear();
                    jeu.grilleJeu.grille.print();
                    cout << "Votre temps ";
                    jeu.chrono.afficher();
                    cout << endl;
                }
                else if (menuRes == 4) {
                    termClear();
                    cout << "ABANDON: partie terminee !" << endl << "Votre Grille : " << endl;
                    jeu.grilleJeu.grille.print();
                    cout << endl;
                    cout << "Grille solution :" << endl;
                    jeu.grilleSolution.grille.print();
                    cout << "Vous avez fait " << jeu.nbErreurs() << " erreurs" << endl;
                    stop = true;
                    aideRemplir = true;//on skip tout le reste du programme en faisant comme si une case avait etait placé aléatoirement
                }
                else if (menuRes == 5) {
                    jeu.retirerCasesFausses();
                    termClear();
                    jeu.grilleJeu.grille.print();
                    cout << "Votre temps ";
                    jeu.chrono.afficher();
                    cout << endl;
                    cout << "Les cases fausses ont ete retirees!"<< endl;
                    cout << endl;
                }
                else if (menuRes == 6) {
                    termClear();
                    jeu.grilleJeu.grille.print();
                    cout << "Votre temps ";
                    jeu.chrono.afficher();
                    cout << " En pause" << endl;
                    gestSauvegarde gestionnaireSauvegarde("../data/saves/", "data/saves/");

                    if (jeu.sauvegardeId == 0) {

                        cout << "Nom de la sauvegarde(sans espaces!): ";
                        string name;
                        cin >> name;
                        jeu.sauvegardeId = gestionnaireSauvegarde.sauvegarder(jeu, name, 2, 0);
                        termClear();
                        jeu.grilleJeu.grille.print();
                        jeu.chrono.start();
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

                        jeu.sauvegardeId = gestionnaireSauvegarde.sauvegarder(jeu, "", 2, jeu.sauvegardeId);
                        termClear();
                        jeu.grilleJeu.grille.print();
                        cout << "Votre temps ";
                        jeu.chrono.afficher();
                        cout << endl;
                        if (jeu.sauvegardeId != -1) {
                            cout << "La partie a bien ete sauvegardee(sauvegarde deja existente mise a jour) | nom: " << gestionnaireSauvegarde.getInfoSauvegarde(jeu.sauvegardeId).name << endl;
                        }
                        else {
                            cout << "La partie n'a pas pu etre sauvegardee" << endl;
                        }
                    }
                
                    
                }
                else if (menuRes == 7) {
                    int choix;
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
                    if (choix == 1) {

                        aideRemplir = true;//on skip tout le reste du programme en faisant comme si une case avait etait placé aléatoirement
                        stop = true;
                    }
                    else {
                        termClear();
                        jeu.grilleJeu.grille.print();
                        cout << "Votre temps ";
                        jeu.chrono.afficher();
                        cout << endl;
                    }
                    
                }
                jeu.chrono.start();// On redemarre le chrono en ignorant le temps passé dans le menu

            }
            else if (jeu.estValValide((unsigned char)valeur)) {
                valValide = true;
            }
           

        } while(!valValide && !aideRemplir && !aideCoor);
        

        if(!aideRemplir && !aideCoor){ //pas besoin de saisir une valeur et des coordonnées si le joueur a utilise l'aide
            do {
                //saisie des coordonnees de la case ou on veut placer valeur si on a pas utilise l'aide
                cout << "Ou voulez-vous placer votre prochaine valeur ?" << endl << "l : " << endl;;
                cin >> l;
                cout << "c : " << endl;
                cin >> c;
            } while (!jeu.sontCorValides(l, c)); //verif coord ok et case modifiable
        }  

        if(!aideRemplir){ //pas besoin de remplir une case qd le joueur a utilise l'aide du solveur (aide 0)
            jeu.chrono.update();//on fixe le chrono 
            jeu.grilleJeu.setCase(l - 1, c - 1, valeur); //on place la valeur dans la grille
        }

        if (jeu.verifGrillePleine(jeu.grilleJeu)) {
            jeu.chrono.update();//on fixe le chrono 
            stop = true;
            termClear();
            cout << "Grille remplie : partie terminee !" << endl<< "Votre grille :"<<endl;
            jeu.grilleJeu.grille.print();
            cout << endl;
            cout << "Grille solution :" << endl;
            jeu.grilleSolution.grille.print();
            cout << "Vous avez fait " << jeu.nbErreurs() << " erreurs" << endl;
            cout << "Votre temps ";
            jeu.chrono.afficher();
            cout << endl;

        }
        
    jeu.chrono.update();

    } while (!stop);

}

unsigned char TXT_PasAPas::menu(){
    int value;

    do {
    termClear();
    jeu.grilleJeu.grille.print();
    cout << "Votre temps ";
    jeu.chrono.afficher();
    cout <<" (EN PAUSE) " << endl;
    cout << "||||||||||||||||||||||||||||| MENU | SUDOKU 3 ||||||||||||||||||||||||||||||" << endl;
    cout << "||                                                                        ||" << endl;
    cout << "|| 0: Obtenir les coor. de la case la plus simple                         ||" << endl;
    cout << "|| 1: Remplit une case (vide) au hasard pour vous                         ||" << endl;
    cout << "|| 2: Recommencer la meme grille                                          ||" << endl;
    cout << "|| 3: Generer une nouvelle gille                                          ||" << endl;
    cout << "|| 4: Abandonner la partie et afficher la solution                        ||" << endl;
    cout << "|| 5: Enlever les cases fausses                                           ||" << endl;
    cout << "|| 6: Sauvegarder                                                         ||" << endl;
    cout << "|| 7: Quitter la partie et revenir au menu sans sauvegarder               ||" << endl;
    cout << "|| 8: Retour au jeu                                                       ||" << endl;
    cout << "||                                                                        ||" << endl;
    cout << "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
    cin >> value;
    } while (value < 0 || value > 8);

    termClear();
    jeu.grilleJeu.grille.print();
    cout << "Votre temps ";
    jeu.chrono.afficher();
    cout << endl;
    return value;
}

void TXT_PasAPas::boucleTest()
{
    jeu.init();
    jeu.grilleJeu.grille.print();
    unsigned char l, c;
    jeu.coordCaseSimple(l, c);
    jeu.printTabDiff();
    cout << "La premiere case la plus simple se trouve aux coordonees: " << (int) l << " " << (int)c << endl;

}


