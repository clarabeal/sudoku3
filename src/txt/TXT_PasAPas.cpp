#include "TXT_PasAPas.h"
#include "../core/Sauvegarde.h"

#include <stdlib.h>
#include <iostream>
#include <string>
using namespace std;

TXT_PasAPas::TXT_PasAPas(unsigned char d, int id, unsigned long int time, Grille& g_sol, Grille& g_orig, Grille& g_jeu) : jeu(d, id, time, g_sol, g_orig, g_jeu) {
    tabDiffCase = new unsigned char[2*d*d];
}

TXT_PasAPas::TXT_PasAPas(unsigned char d) : jeu(d) {
    tabDiffCase = new unsigned char[2 * d * d];
}

TXT_PasAPas::~TXT_PasAPas() {
    delete []tabDiffCase;
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
                    coordCaseSimple(l_simple, c_simple);
                    l = (int)l_simple;
                    c = (int)c_simple;
                    //printTabDiff();
                    cout << "[" << l << "][" << c << "] est facile a remplir il n'y a que " << dimGrille - tabDiffCase[(c - 1) * dimGrille + (l - 1)] << " possibilite(s)" <<   endl;
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
                            cout << "[" << l << "][" << c << "] est facile a remplir il n'y a que " << dimGrille - tabDiffCase[(c - 1) * dimGrille + (l - 1)] << " possibilite(s)" << endl;
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
                    retirerCasesFausses();
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

unsigned char TXT_PasAPas::menu() const {
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
    coordCaseSimple(l, c);
    printTabDiff();
    cout << "La premiere case la plus simple se trouve aux coordonees: " << (int) l << " " << (int)c << endl;

}

void TXT_PasAPas::updateDiffCase(){
    unsigned char dimGrille = jeu.grilleJeu.dim;
    for (unsigned char li = 1; li <= dimGrille; ++li) {
        for (unsigned char co = 1; co <= dimGrille; ++co) {
            if (jeu.grilleJeu.grille.getCase(li-1, co-1).getVal() == 0 || jeu.grilleSolution.grille.getCase(li - 1, co - 1).getVal() != jeu.grilleJeu.grille.getCase(li - 1, co - 1).getVal()) {
                // Verison nombre total indices l/c/carre
                unsigned char scoreLi = 1;
                unsigned char scoreCol = 1;
                unsigned char scoreCar = 1;

                for (unsigned char i = 0; i < dimGrille; i++) {
                    if (jeu.grilleJeu.lignes[li - 1].tabl[i]->getVal() == jeu.grilleSolution.lignes[li - 1].tabl[i]->getVal()) {
                        scoreLi = scoreLi * 2;
                    }
                    if (jeu.grilleJeu.colonnes[co - 1].tabcl[i]->getVal() == jeu.grilleSolution.colonnes[co - 1].tabcl[i]->getVal()) {
                        scoreCol = scoreCol * 2;
                    }
                    if (jeu.grilleJeu.carres[jeu.trouverNumeroCarre(li, co) - 1].tabc[i]->getVal() == jeu.grilleSolution.carres[jeu.trouverNumeroCarre(li, co) - 1].tabc[i]->getVal()) {
                        scoreCar = scoreCar * 2;
                    }
                }
                tabDiffCase[(co - 1) * dimGrille + (li - 1) + dimGrille* dimGrille] = scoreCar + scoreCol + scoreLi;
                //std::cout << "La case " << (int)li << " " << (int)co << " a un score de: " << (int)tabDiffCase[(co - 1) * dimGrille + (li - 1)] << endl;

                //version nombre d'indice different
                bool *liste_val = new bool[dimGrille];//les valeur a true sont les valeurs possible pour la case (liste_val[0] == true veux dire que 1 est une valeur possible, liste_val[1] == false veux dire que 2 n'est pas  une valeur possible...)
                for (unsigned char i = 0; i < dimGrille; i++) {
                    liste_val[i] = true;
                }
                for (unsigned char i = 0; i < dimGrille; i++) {
                    if (jeu.grilleJeu.lignes[li - 1].tabl[i]->getVal() == jeu.grilleSolution.lignes[li - 1].tabl[i]->getVal()) {
                        liste_val[jeu.grilleJeu.lignes[li - 1].tabl[i]->getVal()-1] = false;
                    }
                    if (jeu.grilleJeu.colonnes[co - 1].tabcl[i]->getVal() == jeu.grilleSolution.colonnes[co - 1].tabcl[i]->getVal()) {
                        liste_val[jeu.grilleJeu.colonnes[co - 1].tabcl[i]->getVal()-1] = false;
                    }
                    if (jeu.grilleJeu.carres[jeu.trouverNumeroCarre(li, co) - 1].tabc[i]->getVal() == jeu.grilleSolution.carres[jeu.trouverNumeroCarre(li, co) - 1].tabc[i]->getVal()) {
                        liste_val[jeu.grilleJeu.carres[jeu.trouverNumeroCarre(li, co) - 1].tabc[i]->getVal()-1] = false;
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


unsigned char TXT_PasAPas::getDiffCase(unsigned char l, unsigned char c,bool diff_type)//diff type = 1: retourne le nombre de valeur possible, diff type = 0, retourne "la tendance a avoir bcp de chiffre dans un meme bloc/ligne/col permet de departager en les diff type = 1 egaux 
{
    unsigned char dimGrille = jeu.grilleJeu.dim;
    if (diff_type) {
        return tabDiffCase[(c - 1) * dimGrille + (l - 1)];
    }
    return tabDiffCase[(c - 1) * dimGrille + (l - 1) + dimGrille*dimGrille];
}

void TXT_PasAPas::coordCaseSimple(unsigned char &l, unsigned char &c)
{
    unsigned char dimGrille = jeu.grilleJeu.dim;
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
                if (getDiffCase(li, co) > getDiffCase(l_f, c_f)){
                    l_f = li;
                    c_f = co;
                }
            }
        }
    }
    l = l_f;
    c = c_f;

}

void TXT_PasAPas::printTabDiff() const {

    for(int l=0;l<jeu.grilleJeu.dim;l++){
        for(int c=0;c<jeu.grilleJeu.dim;c++){
            cout << "tabDiffCase[" << l + 1 << "][" << c + 1 << "] = " << (int)tabDiffCase[c * jeu.grilleJeu.dim + l] << endl;
        }
    }
}

void TXT_PasAPas::retirerCasesFausses()
{
    unsigned char dimGrille = jeu.grilleJeu.dim;
    for (unsigned char li = 0; li < dimGrille; ++li) {
        for (unsigned char co = 0; co < dimGrille; ++co) {
            if (jeu.grilleJeu.grille.getCase(li, co).getVal() != jeu.grilleSolution.grille.getCase(li, co).getVal()) {
                jeu.grilleJeu.grille.getCase(li, co).setVal(0);
                
            }
        }
    }
}
