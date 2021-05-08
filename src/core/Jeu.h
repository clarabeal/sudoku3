#ifndef _JEU_H
#define _JEU_H

#include "Grille.h"
#include <ctime>

/**
\brief Chrno permettant la gestion du temps des parties*/
class chronometre
{
public:
    chronometre();
    /**
    \brief Constructeur qui initialise le chorno avec un certain temps en ms 
    */
    chronometre(const unsigned long int& ms);

    ~chronometre();
    
    /**
   \brief Regle le chrnometre a un certain temps en ms
   */
    void forceTime(const unsigned long int& ms);
    /**
    \brief Met a jour le temps du chronometre
    */
    void update();

    /**
    \brief (Re)Demarre le chrono
    */
    void start();

    /**
    \brief Mets en pause le chrono
    */
    void pause();
    /**
    \brief Remet le chronometre a 0
    */
    void reset();

    /**
    \brief Retourne le temps en millisecondes sans mettre a jour le chrono
    \details Permet de recuperer le temps a partir d'un chrno passe const
    */
    unsigned long int getTimeInMSecNoUpdate() const;
    /**
    \brief Retourne le temps en millisecondes
    */
    unsigned long int getTimeInMSec();
    /**
    \brief Retourne le temps en secondes
    */
    unsigned long int getTimeInSec();
    /**
    \brief Retourne le temps en minutes
    */
    unsigned long int getTimeInMin();
    /**
    \brief Retourne le temps en heures
    */
    unsigned long int getTimeInHours();

    /**
    \brief Affiche le temps ecoule sous la forme hh:mm:ss:msmsmsms*/
    void afficher();

    bool estEnPause();
private:
    clock_t t1, t2;
    unsigned long int ms;
    bool enPause;

};


/**\brief coeur du jeu*/
class Jeu {

    public :
    /**
    @brief Constructeur a parametres
    @details Cree une grilleJeu et une grilleSolution toutes les 2 de taille dim
    */
    Jeu(const unsigned char& d);

    /**
    @brief Constructeur a parametres a partir d'une sauvegarde
    @details Recommence une partie avec les grilles passees en parametres
    */
    Jeu(const unsigned char& d, const int& id, const unsigned long& time, const Grille& g_sol, const Grille& g_orig, const Grille& g_jeu);

    /**
    @brief Grille pleine, contient la solution du sudoku
    */
    Grille grilleSolution;

    /**
    @brief Grille a remplir avant que le joueur ne l'ai modifiée
    */
    Grille grilleOriginale;

    /**
    @brief Grille a remplir, celle avec lequel le joueur interagit
    */
    Grille grilleJeu;

    


    /**
    @brief Destructeur
    */
    ~Jeu();

    /**
    @brief Genere une grille pleine, qui respecte les contraintes d'une grille de sudoku
    */
    bool genererGrillePleine (const int& etape = 0);

    /**
    @brief Remplit un tableau avec des entiers aleatoires compris entre 1 et max
    @param [je sais pas] tab : le tableau a remplir
    @param [in] max la valeur maximale que doit prendre les nombres geres aleatoirement
    */
    void remplirTblAlea(unsigned char* tab, const unsigned char& max);


    /**
    @brief Renvoie le nombre de solution possible pour une grille
    */
    unsigned char nombreDeSolutions (const Grille& grille) const;

    /**
    @brief Genere la grille de jeu a partir de la grille de solution
    */
    void genererGrilleMinimale ();

    /**
    @brief Verifie si la grille est pleine ou non
    @details Retourne 1 si pleine, 0 sinon
     */
    bool verifGrillePleine(const Grille& grille) const;

    /**
    @brief Initialise une grille
    @details Genere une nouvelle grille pleine stockee dans grilleSolution et une grille a trou dans grilleJeu
    \see genererGrillePleine genererGrilleMinimale
    */
    void init();

    /**
    @brief Verifie si la valeur donnée est valide
    @details Retourne true si la valeur est valide, false sinon
    */
    bool estValValide (const unsigned char& valeur) const;

    /**
    @brief Verifie si les coordonnées données sont valides et si la case est modifiable
    @details Retourne true si elles sont valides, false sinon
    */
    bool sontCorValides (const unsigned char& l, const unsigned char& c) const;

    /**
    @brief Verifie si la case est modifiable
    @details Retourne true si la case est modifiable, false sinon
    */
    bool getModifCase (const unsigned char& l, const unsigned char& c) const;


    /**
    @brief Retourne le nombre d'erreurs dans la grille de jeu
    */
    unsigned int nbErreurs () const;

    /**
    @brief Determine dans quel carre de la grille se trouve la case [l][c]
    @details Retourne l'indice du carre dans lequel se trouve la case
    */
    unsigned char trouverNumeroCarre(const unsigned char& l, const unsigned char& c) const;

    /**
    @brief Indique si la partie a déja été initialisé
    @details Utilise pour la gestion des sauvegardes
    */
    bool initDone;

    /**
    @brief Id de la sauvegarde associee a cette partie, vaut -1 si la partie n'a jamais été sauvegardee
    */
    int sauvegardeId;

    /**
    \brief Permer de gerer le temps de la partie
    \see chronometre
    */
    chronometre chrono;

private:


};


/**\brief coeur du jeu + fonctions et donnees membre du mode pas a pas*/
class JeuPasAPas: public Jeu
{
public:
    /**
    @brief Constructeur a parametres
    @details Cree une grilleJeu et une grilleSolution toutes les 2 de taille dim
    */
    JeuPasAPas(const unsigned char& d);

    /**
    @brief Constructeur a parametres a partir d'une sauvegarde
    @details Recommence une partie avec les grilles passees en parametres
    */
    JeuPasAPas(const unsigned char& d, const int& id, const unsigned long& time, const Grille& g_sol,const Grille& g_orig, const Grille& g_jeu);

    ~JeuPasAPas();

    /**\brief Met a jour le tableau tabDiffCase*/
    void updateDiffCase();

    /**\brief Retourne la difficulte de la case passee en parametre*/
    unsigned char getDiffCase(const unsigned char& l, const unsigned char& c, const bool& diff_type = 1);

    /**\brief Fait passer les coordonnees de la case la plus simle dans l et c*/
    void coordCaseSimple(unsigned char& l, unsigned char& c);

    void printTabDiff()const;

    /**\brief Retire les cases fausses de la grille de jeu*/
    void retirerCasesFausses();

    /** Tableau contenant la difficulte de chaque case de la grille
    \see updateDiffCase()*/
    unsigned char* tabDiffCase;
    
    /**\brief Inique si l'aide affichante les cases fausses est activee*/
    bool coloration;

    /**\brief Mets a jour l'etat de chaque case*/
    void colorerCase();

private:


};


/**\brief coeur du jeu + fonctions et donnees membre du mode 1vs1 */
class Jeu1Vs1 : public Jeu
{
public:
    /**
    @brief Constructeur a parametres
    @details Cree une grilleJeu et une grilleSolution toutes les 2 de taille dim
    */
    Jeu1Vs1(const unsigned char& d);

    /**
     @brief Constructeur a parametres a partir d'une sauvegarde
     @details Recommence une partie avec les donnees passees en parametres
     */
    Jeu1Vs1(const unsigned char& d, const int& id, const unsigned long int& time, const Grille& g_sol, const Grille& g_orig, const Grille& g_jeu, const Grille& grilleJ1_, const Grille& grilleJ2_, const unsigned long int& chronoJ1_, const unsigned long int& chronoJ2_, const int& nbErrJ1, const int& nbErrj2, const bool& stopJ1, const bool& stopJ2);

    ~Jeu1Vs1();

    /**\brief contient la grille du joueur 1*/
    Grille grilleJ1;

    /**\brief contient la grille du joueur 2*/
    Grille grilleJ2;

    /**\brief contient le chrono du joueur 1*/
    chronometre chronoJ1;

    /**\brief contient le chrono du joueur 2*/
    chronometre chronoJ2;

    int nbErreurJ1;
    int nbErreurJ2;

    bool stopBoucleJ1;
    bool stopBoucleJ2;

private:


};
#endif