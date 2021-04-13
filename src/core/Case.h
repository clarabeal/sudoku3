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
     @param [in] valeur
     @param [in] mod
    */
    Case (unsigned char valeur, bool mod,unsigned char etat_);

    /**
     @brief Accesseur val : retourne Val
    */
    unsigned char getVal () const;

    /**
     @brief mutateur : modifie la valeur contenue par la case
    */
    void setVal (unsigned char nb);

    /**
     @brief indique l'etat de la case
     \details  0: On sait pas, 1 : La case est juste(vert), 2:La case est fausse(rouge), 3:la case est facile(bleu)
    */
    unsigned char etat;
    private:

    /**
     @brief contient la valeur de la case
    */
    unsigned char val;
    
 
    
};

#endif