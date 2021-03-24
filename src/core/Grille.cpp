#include "Grille.h"


Grille::Grille():grille(dim,dim){
    carres = new Carre[dim];
    lignes = new Ligne[dim];
    colonnes = new Colonne[dim];
    
    for(unsigned char i=1;i<=dim;i++)
    {
        carres[i].remplir(i,grille);
        lignes[i].remplir(i,grille);
        colonnes[i].remplir(i,grille);
    }
}

Grille::~Grille(){
    delete [] carres;
    delete [] lignes;
    delete [] colonnes;
}

void Grille::setCase (unsigned char l, unsigned char c, unsigned char nb){ //on devrait aussi mettre setL,setC,setCarre
    grille.get(l,c).setVal(nb);
}

