#include "Grille.h"

#include <stdlib.h>
using namespace std;

//fait appel au constructeur de Tab2DCasesTas ac grille(d,d)
Grille::Grille(const unsigned char& d):grille(d,d){
    dim = d;
    carres = new Carre[dim];
    lignes = new Ligne[dim];//chaque grille contient dim lignes
    colonnes = new Colonne[dim];
    
    for(int i=1;i<=dim;i++)
    {
        //cout << "creation carre|ligne|col num: " << (int)i << endl;
        carres[i-1].remplir(i,grille);//chaque case de carres est un carre
        lignes[i-1].remplir(i,grille);//chaque case de lignes est une ligne
        colonnes[i-1].remplir(i,grille);//on remplit la case i de colonnes la colonne i de la grille
    }
}

Grille::~Grille(){
    delete [] carres;
    delete [] lignes;
    delete [] colonnes;
}

void Grille::setCase (const unsigned char& l, const unsigned char& c, const unsigned char& nb){ //on devrait aussi mettre setL,setC,setCarre
    grille.getCase(l,c).setVal(nb);

}

void Grille::viderGrille()
{
    grille.vider();
}

void Grille::operator=(const Grille& tab)
{
    assert(dim = tab.dim);
    grille = tab.grille;
}

