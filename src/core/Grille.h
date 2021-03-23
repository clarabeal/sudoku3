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

    void setCase (unsigned char l, unsigned char c, unsigned char nb);

    private :

    Ligne * lignes;
    Colonne * colonnes;
    Carre * carres ;

};


#endif