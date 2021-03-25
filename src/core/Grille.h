#ifndef _GRILLE_H
#define _GRILLE_H

#include "Ligne.h"
#include "Colonne.h"
#include "Carre.h"

class Grille {

    public :

    TabCases2DTas grille;
    unsigned char dim;

    Grille(unsigned char d);

    ~Grille();

    void setCase (unsigned char l, unsigned char c, unsigned char nb);
    Ligne* lignes;
    Colonne* colonnes;
    Carre* carres;
    private :

    

};


#endif