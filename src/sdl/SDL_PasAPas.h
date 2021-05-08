#ifndef _SDL_PasAPas
#define _SDL_PasAPas

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
class sdlJeuPasAPas {

public:

    // ============= FONCTION D'INITIALISATION DE LA PARTIE(CONSTRUCTEURS & CO) + DESTRUCTEUR =============== //

    /**
    \brief Constructeur nouvelle partie.
    \details Initialise une nouvelle partie de jeu et le gestionnaire de sauvegarde.
    \param [in] d La dimension de la grille de jeu.
    */
    sdlJeuPasAPas(unsigned char d);

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
    sdlJeuPasAPas(unsigned char d, int id, unsigned long time, Grille& g_sol, Grille& g_orig, Grille& g_jeu);

    /**
    \brief Initialise SDL
    \details Initialise sdl, charge la police, cree la fenetre et le rendu
    */
    void init_SDL();

    /**
    \brief Charge les assets
    \details Charge les differentes images, Grille, selection des nombres...
    */
    void init_assets();


    /**
    \brief Charge les images du menu
    */
    void init_im_menu();

    /**
    \brief Destructeur
    */
    ~sdlJeuPasAPas();


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
    void placementElementsMenu(int x1, int y1, int x2, int y2 = 0);

    /**
    \brief Reset toutes les hitboxs du menu
    \details doit être appelée pour supprimer les hitBoxs et que le joueurs ne puisse pas cliquer sur un element du menu qui n'est pas affiche*/
    void effacerElementsMenu();

    /**
    \brief Place les hitBoxs de chaque case de la grille*/
    void placerHitBoxCaseGrille(int x, int y, int largeur, int hauteur);


    // ============= FONCTION D'AFFICHAGE =============== //

    /**\brief Appel les differentes fonctions d'affichage pour creer le render qui sera afficher par SDL_RenderPresent(SDL_Renderer*);
    */
    void sdlAff();

    /**\brief Affiche le menu en placant le coin en haut a gauche en (x,y)
    \details affiche les images du menu aux positions des hitBoxs associes
    \see void placementElementsMenu(int x1, int y1, int x2, int y2 = 0) */
    void sdlAffMenu(int x, int y, int largeur, int hauteur);

    /**\brief Affiche le menu de selection des chiffres en placant le coin en haut a gauche en (x,y)
    \details Place les hitBoxes et affcihe les images du menu de selection des chiffres 
    \see void placementElementsMenu(int x1, int y1, int x2, int y2 = 0) */
    void sdlAffSelectionChiffre(int x, int y, int largeur, int hauteur);

    /**\brief Affiche la grille de jeu
    \details Affiche l'image de fond de la grille et si afficher vaut true, affiche egalement les valeur de la grille passee en parametre
    Au debut de chaque partie, la fonction jeu.colorerCases est appelee.
    see JeuPasAPas::colorerCase()*/
    void sdlAffGrille(Grille& grille, int x1, int y1, int x2, int y2, bool afficher = true);

    /**\brief Affiche la chrono
    \details si full est a true, les millisecondes sont également affichees*/
    void sdlAffChrono(int x, int y, int largeur, int hauteur, chronometre& chrono, bool full = false);

    /**\brief Affiche les informations de fin de partie*/
    void sdlAffFinDePartie();

    /**\brief Affiche un ecran de chargement*/
    void sdlAffChargement();


    // ============= CLASS SDLJEU =============== //

    /**\brief boucle de jeu, voire code*/
    void sdlBoucle();

    /**\brief sauvegarde la partie
    \details si force vaut true, la partie est sauvegarder sans prendre en compte le parametre autoSauvegarde. Un nom pour la sauvegarde sera demande si nescessaire.
    Si force vaut false la partie ne sera sauvegardee que si autoSave vaut true*/
    void sauvegarder(bool force = false);


    // ============= FONCTIONS UTILITAIRES =============== //
    /**\brief Affiche une image qui remplit la hitBox en parametre*/
    void affImgInHitBox(Image& img, hitBox& hit);

    /**\brief Affiche le texte de string*/
    void sdlAffTexte(string txt, int x, int y, int largeur, int hauteur, SDL_Color& couleur);



private:
    //------------------Donn�es core mode pas a pas
    JeuPasAPas jeu;

    const int dimGrille;
    int c_toChange, l_toChange;
    int mousse_x, mousse_y;
    bool finDePartie;
    bool autoSave;
    //------------------Donne�es/focntions sauvegarde
    gestSauvegarde gestionnaireSauvegarde;

    //------------------Donn�es SDL
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event event;
    TTF_Font* font;
    SDL_Color font_color;

    //------------------Image globale
    Image im_menu[24];
    Image im_grille;
    Image* im_selectionChiffre;
    Image bleu;
    Image gris;
    Image rouge;
    Image vert;
    //------------------HitBoxs
    hitBox  tabHitBoxSelectionMenu[24];//tableau 2D stockant les positions des bouton du menu (associe a im_menu)
    hitBox* tabHitBoxGrille;//tableau 2D stockant les positions des cases de la grille pour gerer les clics
    hitBox* tabHitBoxSelectionNombre;//tableau 2D stockant les positions des cases de la grille pour gerer les clics
};





#endif