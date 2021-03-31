#include "TXT_PasAPas.h"
#include <stdlib.h>
#include <iostream>

using namespace std;

TXT_PasAPas::TXT_PasAPas(unsigned char d): jeu(d) {
    tabDiffCase = new unsigned char[d*d];
}

TXT_PasAPas::~TXT_PasAPas() {
    delete []tabDiffCase;
}

void TXT_PasAPas::termClear()  // efface le terminal
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void TXT_PasAPas::boucle() {

    bool stop = false; //booleen indiquant si la boucle de jeu doit continuer ou pas
    int valeur;
    int l,c;

    jeu.init();

    do {
        termClear();
        jeu.grilleJeu.grille.print();
        
        bool aideRemplir = false; //booleen indiquant si le joueur a besoin d'aide pour que le solveur remplisse une case à sa place (case au hasard ou la plus facile à placer?)
        bool aideCoor = false;

        do{
            cout <<"Quelle valeur voulez-vous placer ? | Aide pour remplir une case : " << jeu.grilleJeu.dim+1 << ", Aide pour position case : " << jeu.grilleJeu.dim+2 << endl;
            cin >> valeur;

            if(valeur==jeu.grilleJeu.dim+2){
                //donne les coordonnées de la case la plus simple à trouver
                cout << "rentre dans la boucle" << endl;
                //coordCaseSimple((unsigned char)l, (unsigned char)c);
                printTabDiff();
                cout << "[" << l << "][" << c << "] est facile a remplir" << endl;

                do{
                    cout << "Quelle valeur voulez-vous mettre à cette position?"<< endl;
                    cin >> valeur;

                } while (!jeu.estValValide((unsigned char)valeur)); //tant que la valeur n'est pas valide

                aideCoor = true;

            }
            else if (valeur==jeu.grilleJeu.dim+1){

                cout << "rentre dans la boucle" << endl;

                do{ //remplit une case au hasard
                    cout << "rentre dans le do" << endl;

                    l = rand() % jeu.grilleJeu.dim + 1;
			        c = rand() % jeu.grilleJeu.dim + 1;

                    cout << "l :" << l << "c :" << c << endl;

			        valeur = jeu.grilleJeu.grille.getCase(l - 1, c - 1).getVal();

                    if (valeur==0){ //place la valeur si la case est vide
                        cout <<"Case vide" << endl;
                        jeu.grilleJeu.setCase(l - 1, c - 1, jeu.grilleSolution.grille.getCase(l - 1, c - 1).getVal());
                        aideRemplir=true; //aide à savoir si la valeur à été placée
                    }

                } while (aideRemplir == false);

            }

        } while(!jeu.estValValide((unsigned char)valeur)|| aideRemplir || aideCoor);
        

        if(!aideRemplir && !aideCoor){ //pas besoin de saisir une valeur et des coordonnées si le joueur a utilise l'aide
            do {
                //saisie des coordonnees de la case ou on veut placer valeur si on a pas utilise l'aide
                cout << "Où voulez-vous placer votre prochaine valeur ?" << endl << "l : " << endl;;
                cin >> l;
                cout << "c : " << endl;
                cin >> c;
            } while (!jeu.sontCorValides(l, c)); //verif coord ok et case modifiable
        }  

        if(!aideRemplir){ //pas besoin de remplir une case qd le joueur a utilise l'aide du solveur (aide 0)
            jeu.grilleJeu.setCase(l - 1, c - 1, valeur); //on place la valeur dans la grille
        }

        if (jeu.verifGrillePleine(jeu.grilleJeu)) {
            stop = true;
            termClear();
            cout << "Grille remplie : partie terminee !" << endl<< "Votre grille:"<<endl;
            jeu.grilleJeu.grille.print();
            cout << endl;
            cout << "Grille solution :" << endl;
            jeu.grilleSolution.grille.print();
        }
        

    } while (!stop);

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

void TXT_PasAPas::updateDiffCase()
{
    unsigned char dimGrille = jeu.grilleJeu.dim;
    for (unsigned char li = 1; li <= dimGrille; ++li) {
        for (unsigned char co = 1; co <= dimGrille; ++co) {
            if (jeu.grilleJeu.grille.getCase(li-1, co-1).getVal() == 0) {
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
                tabDiffCase[(co - 1) * dimGrille + (li - 1)] = scoreCar + scoreCol + scoreLi;
                //std::cout << "La case " << (int)li << " " << (int)co << " a un score de: " << (int)tabDiffCase[(co - 1) * dimGrille + (li - 1)] << endl;
            }
            else {
                tabDiffCase[(co - 1) * dimGrille + (li - 1)] = 0;
            }
        }
    }
}


unsigned char TXT_PasAPas::getDiffCase(unsigned char l, unsigned char c)
{
    unsigned char dimGrille = jeu.grilleJeu.dim;
    return tabDiffCase[(c - 1) * dimGrille + (l - 1)];
}

void TXT_PasAPas::coordCaseSimple(unsigned char &l, unsigned char &c)
{
    unsigned char dimGrille = jeu.grilleJeu.dim;
    updateDiffCase();
    unsigned char l_f = 1;
    unsigned char c_f = 1;
    unsigned char max = getDiffCase(1, 1);
    for (unsigned char li = 2; li <= dimGrille; ++li) {
        for (unsigned char co = 2; co <= dimGrille; ++co) {
            unsigned char value = getDiffCase(li, co);
            if (value > max) {
                max = getDiffCase(li, co);
                l_f = li;
                c_f = co;
            }
        }
    }
    l = l_f;
    c = c_f;

}

void TXT_PasAPas::printTabDiff() const {

    for(int l=0;l<jeu.grilleJeu.dim;l++){
        for(int c=0;c<jeu.grilleJeu.dim;c++){
            cout << "tabDiffCase[" << l+1 << "][" << c+1 << "] = " << (int)tabDiffCase[c*jeu.grilleJeu.dim+l] << endl;
        }
    }
}
