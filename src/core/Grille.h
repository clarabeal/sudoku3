#ifndef _GRILLE_H
#define _GRILLE_H

#include "Case.h"
#include "Ligne.h"
#include "Colonne.h"
#include "Carre.h"
#include "TabCases2DTas.h"

class Grille {

    public :

    TabCases2DTas grille;
    unsigned char dim;

    Grille ();

    ~Grille();

    bool setCase (unsigned char x, unsigned char y, unsigned char nb);

    private :

    Ligne * lignes;
    Colonne * colonnes;
    Carre * carres ;

};


#endif