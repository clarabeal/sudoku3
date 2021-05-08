#ifndef _SDL_CLASSIQUE
#define _SDL_CLASSIQUE

#include "../core/Sauvegarde.h"
#include "Image.h"
#include "HitBox.h"
#include "SdlSaisieTxt.h"

#ifdef _WIN32
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#elif __linux__
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#endif

using namespace std;
/**
    La classe gerant le jeu avec un affichage SDL
*/
class sdlJeuClassique {

public:

    // ============= FONCTION D'INITIALISATION DE LA PARTIE(CONSTRUCTEURS & CO) + DESTRUCTEUR =============== //

    /**
    \brief Constructeur nouvelle partie.
    \details Initialise une nouvelle partie de jeu et le gestionnaire de sauvegarde.
    \param [in] d La dimension de la grille de jeu.
    */
    sdlJeuClassique(const unsigned char& d);

    /**
    \brief Constructeur apartir d'une partie sauvegardee
    \details Charge les données passées en parametre pour initialiser une partie de jeu(chargement d'une sauvegarde) et le gestionnaire de sauvegarde
    \param [in] d La dimension de la grille de jeu.
    \param [in] id L'id de la partie de jeu chargée
    \param [in] time Le chrono du joueur au moment de la derniere sauvegarde.
    \param [in] g_sol La grille solution chargee
    \param [in] g_orig La grille d'origine chargee
    \param [in] g_jeu La grille de jeu chargee

    */
    sdlJeuClassique(const unsigned char& d, const int& id, const unsigned long& time, const Grille& g_sol, const Grille& g_orig, const Grille& g_jeu);

    /**
    \brief Initialise SDL
    \details Initialise sdl, charge la police, cree la fenetre et le rendu
    */
    void init_SDL();

    /**
    \brief Charge les assets
    \details Charge les differentes images, grille, selection des nombres...
    */
    void init_assets();


    /**
    \brief Charge les images du menu
    */
    void init_im_menu();

    /**
    \brief Destructeur
    */
    ~sdlJeuClassique();


    // ============= FONCTION DE GESTION DES HITBoxS =============== //
    /**
    \brief Reset toutes les hitboxs de la grille
    \details doit être appelée pour supprimer les hitBoxs et que le joueurs ne puisse pas cliquer sur des elements de la grille lorsqu'elle n'est pas affichée(Ex: Le jeu est en pause)*/
    void resetTabHitGrille();

    /**
    \brief Reset toutes les hitboxs de selection de nombre
    \details doit être appelée pour supprimer les hitBoxs et que le joueurs ne puisse pas cliquer sur un nombre lorsqu'aucune case n'est selectionnee*/
    void resetTabHitSelectionNombre();

    /**
    \brief Place les hitBoxs du menu
    \details doit être appelée pour supprimer les hitBoxs et que le joueurs ne puisse pas cliquer sur un nombre lorsqu'aucune case n'est selectionnee*/
    void placementElementsMenu(const int& x1, const int& y1, const int& x2, int y2 = 0);

    /**
    \brief Reset toutes les hitboxs du menu
    \details doit être appelée pour supprimer les hitBoxs et que le joueurs ne puisse pas cliquer sur un element du menu qui n'est pas affiche*/
    void effacerElementsMenu();

    /**
    \brief Place les hitBoxs de chaque case de la grille*/
    void placerHitBoxCaseGrille(const int& x, const int& y, const int& largeur, const int& hauteur);


    // ============= FONCTION D'AFFICHAGE =============== //

    /**\brief Appel les differentes fonctions d'affichage pour creer le render qui sera afficher par SDL_RenderPresent(SDL_Renderer*);
    */
    void sdlAff();

    /**\brief Affiche le menu en placant le coin en haut a gauche en (x,y)
    \details affiche les images du menu aux positions des hitBoxs associes
    \see void placementElementsMenu(int x1, int y1, int x2, int y2 = 0) */
    void sdlAffMenu(const int& x, const int& y, const int& largeur, const int& hauteur);

    /**\brief Affiche le menu de selection des chiffres en placant le coin en haut a gauche en (x,y)
    \details Place les hitBoxes et affcihe les images du menu de selection des chiffres
    \see void placementElementsMenu(int x1, int y1, int x2, int y2 = 0) */
    void sdlAffSelectionChiffre(const int& x, const int& y, const int& largeur, const int& hauteur);

    /**\brief Affiche la grille de jeu
    \details Affiche l'image de fond de la grille et si afficher vaut true, affiche egalement les valeur de la grille passee en parametre
    Au debut de chaque partie, la fonction jeu.colorerCases est appelee.
    see JeuPasAPas::colorerCase()*/
    void sdlAffGrille(const Grille& grille, const int& x1, const int& y1, const int& x2, const int& y2, const bool& afficher = true);

    /**\brief Affiche la chrono
    \details si full est a true, les millisecondes sont également affichees*/
    void sdlAffChrono(const int& x, const int& y, const int& largeur, const int& hauteur, chronometre& chrono, const bool& full = false);

    /**\brief Affiche les informations de fin de partie*/
    void sdlAffFinDePartie();

    /**\brief Affiche un ecran de chargement*/
    void sdlAffChargement();


    // ============= CLASS SDLJEU =============== //

    /**\brief boucle de jeu, voire code*/
    void sdlBoucle();

    /**\brief sauvegarde la partie
    \details si force vaut true, la partie est sauvegarder sans prendre en compte le parametre autoSauvegarde. Un nom pour la sauvegarde sera demande si nescessaire.
    modeJeu: 1
    Si force vaut false la partie ne sera sauvegardee que si autoSave vaut true*/
    void sauvegarder(const int& modeJeu, const bool& force = false);


    // ============= FONCTIONS UTILITAIRES =============== //
    /**\brief Affiche une image qui remplit la hitBox en parametre*/
    void affImgInHitBox(Image& img, const hitBox& hit);

    /**\brief Affiche le texte de string*/
    void sdlAffTexte(const string& txt, const int& x, const int& y, const int& largeur, const int& hauteur, const SDL_Color& couleur);



private :
//------------------Donn�es core mode pas a pas
    /**\see JeuPasAPas*/
    Jeu jeu;

    /**\brief La dimension des grilles de la partie en cours*/
    const int dimGrille;

    /**\brief colonne de la case en cours de modification
    \details vaut 0 si aucune case n'est entrain d'etre modifiee */
    int c_toChange;
    /**\brief ligne de la case en cours de modification
        \details vaut 0 si aucune case n'est entrain d'etre modifiee */
    int l_toChange;

    /**\brief position x de la souris*/
    int mousse_x;
    /**\brief position y de la souris*/
    int mousse_y;

    /**\brief indique si la partie est finie
    \details true = finie, false = en cours*/
    bool finDePartie;

    /**\brief etat de la sauvegarde automatique
       \details true = activee, false = desactivee*/
    bool autoSave;

    //------------------Donne�es/focntions sauvegarde
    /**\see gestSauveagrde*/
    gestSauvegarde gestionnaireSauvegarde;

    //------------------Donn�es SDL
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event event;
    TTF_Font* font;
    SDL_Color font_color;

    //------------------Image globale
    /**
    \brief Tableaux contenant les images du menu
    \see void init_im_menu()*/
    Image im_menu[14];

    /**\brief L'image de fond de la grille
    \see void init_assets()*/
    Image im_grille;

    /**\brief contient les images du menu de selection des images
       \details Tableau de taille dim+1
       \see void init_assets() */
    Image* im_selectionChiffre;

    /**\brief Image a afficher par dessus la case selectionnee
       \see void init_assets() */
    Image indicateurCaseSelectionee;

    //------------------HitBoxs
    /**\brief Tableau de hitBox contenant toutes les zones clicables associees au menu
       \details Chaque elements i de tabHitBoxSelectionMenu[i] est associe a l'image im_menu[i]
       \see void placementElementsMenu(int x1, int y1, int x2, int y2 = 0)
       \see hitBox*/
    hitBox  tabHitBoxSelectionMenu[14];

    /**\brief Tableau de hitBox contenant toutes les zones clicables de la grille (une par case)
       \see void placerHitBoxCaseGrille(int x, int y, int largeur, int hauteur);
       \see hitBox*/
    hitBox* tabHitBoxGrille;//tableau 2D stockant les positions des cases de la grille pour gerer les clics

    /**\brief Tableau de hitBox contenant toutes les zones clicables de la selection des nombres
       \see sdlAffSelectionChiffre(int x, int y, int largeur, int hauteur);
       \see resetTabHitSelectionNombre()
       \see hitBox*/
    hitBox* tabHitBoxSelectionNombre;//tableau 2D stockant les positions des cases de la grille pour gerer les clics
};

#endif