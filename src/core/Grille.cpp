#include "Grille.h"
#include "TabCases2DTas.h"

Grille::Grille():grille(dim,dim){
    carres = new Carre[dim];
    
    for(unsigned char i=1;i<=dim;i++)
    {
        carres[i].remplir(i,grille);
    }
}

