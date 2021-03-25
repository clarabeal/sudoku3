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
    @details Initialise toutes les donnees membres a 0
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
    Case (unsigned char ligne, unsigned char colonne, unsigned char car, unsigned char valeur, bool mod);

    /**
     @brief Accesseur L : retourne l
    */
    unsigned char getL () const;

    /**
     @brief Accesseur C : retourne c
    */
    unsigned char getC () const;

    /**
     @brief Accesseur Carre : retourne carre
    */
    unsigned char getCarre () const;

    /**
     @brief Accesseur val : retourne Val
    */
    unsigned char getVal () const;

    /**
     @brief mutateur : modifie la valeur contenue par la case
    */
    void setVal (unsigned char nb);

    private:

    /**
     @brief contient la valeur de la case
    */
    unsigned char val;
    
    /**
     @brief indique la ligne sur laquelle se trouve la case
    */
    unsigned char l;
    
    /**
     @brief indique la colonne sur laquelle se trouve la case
    */
    unsigned char c;
    
    /**
     @brief indique le carre de la grille sur laquelle se trouve la case
    */
    unsigned char carre;
};

#endif