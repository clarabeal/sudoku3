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
    //On efface le terminal
    //On intitialise une grille solution
   // On cree une grille de jeu
    //Dans la boucle :
   // On affiche la grille de jeu
    //Tant que la grille n'est pas pleine ou que l'utilisateur ne veut pas quitter
    //Systeme de question reponse : quelle nb placer? a quelle coordonnées?
    //Grille pleine on compare a la grille solution et on indique le nb d'erreurs
    

    bool stop = false; //booleen indiquant si la boucle de jeu doit continuer ou pas
    int valeur,nbAide,l,c;

    jeu.init();
    do {
        termClear();
        
        jeu.grilleJeu.grille.print();

        bool aideCoor = false; //booleen indiquant si le joueur a besoin d'aide pour trouver la case la plus facile à remplir
        bool aideRemplir = false; //booleen indiquant si le joueur a besoin d'aide pour que le solveur remplisse une case à sa place (case au hasard ou la plus facile à placer?)

        cout <<"Voulez-vous savoir quelle case est la plus facile à poser ou que le solveur remplisse une case? | Position Case : 0, Remplir une case : 1" << endl;
        cin >> nbAide;

        if(nbAide==0){
           //mettre fct que herve fait et qui donnera la meilleure position avec comme paramètre l et c qui seront les coordonnées de la case la plus simple à trouver
            aideCoor=true;
            coordCaseSimple(l,c);
        } 
        else if (nbAide==1){

            do{ //remplit une case au hasard

                l = rand() % jeu.grilleJeu.dim + 1;
			    c = rand() % jeu.grilleJeu.dim + 1;

			    cout << "l : " << l << " c : " << c << endl; //pour vérifier que les coordonnées soient bonnes

			    valeur = jeu.grilleJeu.grille.getCase(l - 1, c - 1).getVal();

                if (valeur==0){ //place la valeur si la case est vide
                    jeu.grilleJeu.setCase(l - 1, c - 1, valeur); 
                    aideRemplir=true; //aide à savoir si la valeur à été placée (peut être créer un autre booléen)
                }

            } while (aideRemplir = false);

        }

        do { //remplacer en while sinon ça le fera qd même une fois même si l'utilisateur a utilisé l'aide ou mettre un if
            //saisie de la valeur à placer 
            
            cout<< "Quelle valeur voulez-vous placer ?" << endl;
            cin >> valeur;
           
        } while (!jeu.estValValide((unsigned char)valeur) && !stop && !aideCoor && !aideRemplir);//tant qu'elle n'est pas valide, que le joueur n'a pas dit stop et que le joueur n'a utilisé aucune aide

        if (!stop) {
            do {
                //saisie des coordonnees de la case ou on veut placer valeur si on a pas utilise l'aide
                cout << "Ou voulez-vous placer votre prochaine valeur ?" << endl << "l : " << endl;;
                cin >> l;
                cout << "c : " << endl;
                cin >> c;
            } while (!jeu.sontCorValides((unsigned char)l, (unsigned char)c)); //verif coord ok et case vide

            jeu.grilleJeu.setCase(l - 1, c - 1, valeur); //on place la valeur dans la grille

            if (jeu.verifGrillePleine(jeu.grilleJeu)) {
                stop = true;
                termClear();
                cout << "Grille remplie : partie terminee !" << endl<< "Votre grille:"<<endl;
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

void TXT_PasAPas::boucleTest()
{
    jeu.init();
    jeu.grilleJeu.grille.print();
    unsigned char l, c;
    coordCaseSimple(l, c);
    cout << " la (premiere) case la plus simple se trouve aux coordonees: " << (int) l << " " << (int)c << endl;
    int a;
    cin >> a;

}

void TXT_PasAPas::updateDiffCase()
{
    unsigned char dimGrille = jeu.grilleJeu.dim;
    for (unsigned char li = 1; li <= dimGrille; ++li) {
        for (unsigned char co = 1; co <= dimGrille; ++co) {
            unsigned char scoreLi = 1;
            unsigned char scoreCol = 1;
            unsigned char scoreCar = 1;

            for (unsigned char i = 0; i < dimGrille; i++) {
                if (jeu.grilleJeu.lignes[li-1].tabl[i]->getVal() == jeu.grilleSolution.lignes[li-1].tabl[i]->getVal()) {
                    scoreLi = scoreLi * 2;
                }
                if (jeu.grilleJeu.colonnes[co-1].tabcl[i]->getVal() == jeu.grilleSolution.colonnes[co-1].tabcl[i]->getVal()) {
                    scoreCol = scoreCol * 2;
                }
                if (jeu.grilleJeu.carres[jeu.trouverNumeroCarre(li, co)-1].tabc[i]->getVal() == jeu.grilleSolution.carres[jeu.trouverNumeroCarre(li, co)-1].tabc[i]->getVal()) {
                    scoreCar  = scoreCar * 2;
                }
            }
            tabDiffCase[(co - 1) * dimGrille + (li - 1)] = scoreCar + scoreCol + scoreLi;
            //std::cout << "La case " << (int)li << " " << (int)co << " a un score de: " << (int)tabDiffCase[(co - 1) * dimGrille + (li - 1)] << endl;

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
