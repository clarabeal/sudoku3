#ifndef _CASE_H
#define _CASE_H

class Case {
    public:

    bool modifiable;
    /**
    @brief Constructeur par defaut d'une case vide 
   */
    Case();
    /**
     @brief Constructeur case
    */
    Case (unsigned int ligne, unsigned int colonne, unsigned int czr, unsigned int valeur, bool mod);

    /**
     @brief Accesseur L
    */
    unsigned int getL () const;

    /**
     @brief Accesseur C
    */
    unsigned int getC () const;

    unsigned int getCarre () const;

    unsigned int getVal () const;

    void setVal (unsigned int nb);

    private:

    unsigned int val, l, c, carre;
};

#endif