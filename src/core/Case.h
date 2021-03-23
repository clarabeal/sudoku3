#ifndef _CASE_H
#define _CASE_H

class Case {

    public:

    /**
    @brief indique si la case est modifiable par le joueur
    */
    bool modifiable;

    /**
    @brief Constructeur par defaut d'une case vide
    */
    Case();

    /**
     @brief Constructeur avec parametres de case
     @param [in] ligne 
     @param [in] colonne
     @param [in] car
     @param [in] valeur
     @param [in] mod
    */
    Case (unsigned int ligne, unsigned int colonne, unsigned int car, unsigned int valeur, bool mod);

    /**
     @brief Accesseur L : retourne l
    */
    unsigned int getL () const;

    /**
     @brief Accesseur C : retourne c
    */
    unsigned int getC () const;

    /**
     @brief Accesseur Carre : retourne carre
    */
    unsigned int getCarre () const;

    /**
     @brief Accesseur val : retourne Val
    */
    unsigned int getVal () const;

    /**
     @brief mutateur : modifie la valeur de la case
    */
    void setVal (unsigned int nb);

    private:

    /**
     @brief contient la valeur de la case
    */
    unsigned int val;
    
    /**
     @brief indique la ligne sur laquelle se trouve la case
    */
    unsigned int l;
    
    /**
     @brief indique la colonne sur laquelle se trouve la case
    */
    unsigned int c;
    
    /**
     @brief indique le carre de la grille sur laquelle se trouve la case
    */
    unsigned int carre;
};

#endif