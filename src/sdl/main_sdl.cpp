#include "SDL_Classique.h"
#include "SDL_PasAPas.h"
#include "SDL_1vs1.h"

#include <iostream>
#include <algorithm>  //pour la fonciton min(a, b)

using namespace std;

//format 16/9
#define WIDTH 1024
#define HEIGHT 576


void affMenuSelectMode(int ModeOver, SDL_Renderer* renderer, TTF_Font* font, Image** tab_img, hitBox** tab_hit); //tab_img img contient les pointeurs sur les images dans lordre suivant: Image& im_modeClassiqueOver, Image& im_modeClassiqueAway, Image& im_modePasAPasOver, Image& im_modePasAPasAway, Image& im_mode1vs1Over, Image& im_mode1vs1Away, Image& im_sauvegardeOver, Image& im_sauvegardeAway
int selectMode(SDL_Renderer* renderer, TTF_Font* font, Image& im_fondEcran);
void affMenuSelectDim(int ModeOver, SDL_Renderer* renderer, TTF_Font* font, Image** tab_img, hitBox** tab_hit); //tab_img img contient les pointeurs sur les images dans lordre suivant:Image& im_4X4Over, Image& im_4X4Away, Image& im_9X9Over, Image& im_9X9Away, Image& im_16X16Over, Image& im_16X16Away, Image& im_retourOver, Image& im_retourAway
int selectDim(SDL_Renderer* renderer, TTF_Font* font, Image& im_fondEcran);
int selectSauvegarde(gestSauvegarde& gestS, SDL_Renderer* renderer, TTF_Font* font, Image& im_fondEcran);
void affMenuSelectSauvegarde(int boutonOver, unsigned int premiereSauvegardeAffichee, gestSauvegarde& gestS, SDL_Renderer* renderer, TTF_Font* font, hitBox** tab_hit, Image** tab_img);

int selectOptionSauvegarde(gestSauvegarde& gestS, unsigned int idSauvegarde, SDL_Renderer* renderer, TTF_Font* font);
void affMenuSelectOptionSauvegarde(int boutonOver, unsigned int idSauvegarde, gestSauvegarde& gestS, SDL_Renderer* renderer, TTF_Font* font, hitBox** tab_hit);


int main(int argc, char* argv[]) {
    SDL_Window* window;
    SDL_Renderer* renderer;

    TTF_Font* font_menu;
    // Initialisation de la SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    if (TTF_Init() != 0) {
        cout << "Erreur lors de l'initialisation de la SDL_ttf : " << TTF_GetError() << endl;
        SDL_Quit();
        exit(1);
    }
    //font_menu = TTF_OpenFont("data/fonts/arial.ttf", 120);
    font_menu = TTF_OpenFont("data/fonts/BungeeShade-Regular.ttf", 120);
    if (!font_menu) {
        font_menu = TTF_OpenFont("../data/fonts/BungeeShade-Regular.ttf", 120);
    }
  

    int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

   




    gestSauvegarde gestionnaireSauvegarde("../data/saves/", "data/saves/");
    bool jeuOuvert = true;
    bool fenetreEstFerme = true;
    bool menuSauvegardeOuvert = false;
    do {
        if (fenetreEstFerme) {
            window = SDL_CreateWindow("Sudoku 3", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
            if (window == nullptr)
            {
                cout << "Erreur lors de la creation de la fenetre : " << SDL_GetError() << endl;
                SDL_Quit();
                exit(1);
            }

            //creation du rendu : 
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            if (renderer == nullptr)
            {
                cout << "Erreur lors de la creation du renderer : " << SDL_GetError() << endl;
                SDL_Quit();
                exit(1);
            }
            fenetreEstFerme = false;
        }
        Image im_fondEcran;
        im_fondEcran.loadFromFile("data/assets/menu/principal/fondEcran.png", renderer);
        int mode = 0;
        mode = selectMode(renderer, font_menu, im_fondEcran);  //----------> Affiche et recupere l'info du mode de jeux dans le quel le joueur veux jouer ou si il il veut ouvrire une sauvegarde
        
        if (mode == -1) {//----->si le joueur veut quitter le jeu
            jeuOuvert = false;
            TTF_CloseFont(font_menu);
            TTF_Quit();
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            SDL_Quit();
            break;
        }
        //--------------------------Mode classique--------------------------//
        else if(mode == 1) {//----->si le joueur veut creer une nouvelle partie classique
            int dim = selectDim(renderer, font_menu, im_fondEcran);
            if (dim == -2) {//----->si le joueur veut quitter le jeu
                jeuOuvert = false;
                TTF_CloseFont(font_menu);
                TTF_Quit();
                SDL_DestroyRenderer(renderer);
                SDL_DestroyWindow(window);
                SDL_Quit();
            }
            else if (dim != -1) {//----->si le joueur NE veut PAS revenir au menu
                SDL_DestroyRenderer(renderer);
                SDL_DestroyWindow(window);
                fenetreEstFerme = true;
                sdlJeuClassique sJeu(dim);
                sJeu.sdlBoucle();
            }
        }
        //--------------------------Mode Pas a Pas--------------------------//
        else if (mode == 2) {//----->si le joueur veut creer une nouvelle partie pas a pas
            int dim = selectDim(renderer, font_menu, im_fondEcran);
            if (dim == -2) {//----->si le joueur veut quitter le jeu
                jeuOuvert = false;
                TTF_CloseFont(font_menu);
                TTF_Quit();
                SDL_DestroyRenderer(renderer);
                SDL_DestroyWindow(window);
                SDL_Quit();
            }
            else if (dim != -1) {//----->si le joueur NE veut PAS revenir au menu
                SDL_DestroyRenderer(renderer);
                SDL_DestroyWindow(window);
                fenetreEstFerme = true;

                sdlJeuPasAPas sJeu(dim);
                sJeu.sdlBoucle();
            }
        }
        //--------------------------Mode 1 vs 1--------------------------//
        else if (mode == 3) {//----->si le joueur veut creer une nouvelle partie 1 vs 1
            int dim = selectDim(renderer, font_menu, im_fondEcran);
            if (dim == -2) {//----->si le joueur veut quitter le jeu
                jeuOuvert = false;
                TTF_CloseFont(font_menu);
                TTF_Quit();
                SDL_DestroyRenderer(renderer);
                SDL_DestroyWindow(window);
                SDL_Quit();
            }
            else if (dim != -1) {//----->si le joueur NE veut PAS revenir au menu
                SDL_DestroyRenderer(renderer);
                SDL_DestroyWindow(window);
                fenetreEstFerme = true;
                sdl1Vs1 sJeu(dim);
                sJeu.sdlBoucle();
            }
        }
        //--------------------------ouvrire une sauvegarde--------------------------//
        else if (mode == 4) {//----->si le joueur veut acceder aux sauvegardes
            menuSauvegardeOuvert = true;
            do {//while(menuSauvegardeOuvert)
                int choixSauvegarde = -1; // contiendras l'id de la sauvegarde selectionnée
                choixSauvegarde = selectSauvegarde(gestionnaireSauvegarde, renderer, font_menu, im_fondEcran);

                if (choixSauvegarde == -1) {//retourn au menu
                    menuSauvegardeOuvert = false;
                }
                else {
                    int choixOption = 0;

                    choixOption = selectOptionSauvegarde(gestionnaireSauvegarde, gestionnaireSauvegarde.getInfoSauvegarde(choixSauvegarde).id, renderer, font_menu);
                    if (choixOption == -1) {//retour au menu des sauvegardes
                        menuSauvegardeOuvert = true;
                    }
                    else {
                        if (choixOption == 1) {//ouvrir
                            menuSauvegardeOuvert = false;

                            InfoSauvegarde infoSurLaPartie = gestionnaireSauvegarde.getInfoSauvegarde(choixSauvegarde);
                            
                            SDL_DestroyRenderer(renderer);
                            SDL_DestroyWindow(window);
                            if (infoSurLaPartie.modeJeu == 1) {
                                Grille g_sol(infoSurLaPartie.tailleGrille);
                                Grille g_orig(infoSurLaPartie.tailleGrille);
                                Grille g_jeu(infoSurLaPartie.tailleGrille);
                                gestionnaireSauvegarde.chargerSauvegarde(choixSauvegarde, g_sol, g_orig, g_jeu);
                                sdlJeuClassique sdlJeusauv((unsigned char)infoSurLaPartie.tailleGrille, infoSurLaPartie.id, infoSurLaPartie.chrono, g_sol, g_orig, g_jeu);
                                sdlJeusauv.sdlBoucle();
                            }
                            else if (infoSurLaPartie.modeJeu == 2) {
                                Grille g_sol(infoSurLaPartie.tailleGrille);
                                Grille g_orig(infoSurLaPartie.tailleGrille);
                                Grille g_jeu(infoSurLaPartie.tailleGrille);
                                gestionnaireSauvegarde.chargerSauvegarde(choixSauvegarde, g_sol, g_orig, g_jeu);
                                sdlJeuPasAPas sdlJeusauv((unsigned char)infoSurLaPartie.tailleGrille, infoSurLaPartie.id, infoSurLaPartie.chrono, g_sol, g_orig, g_jeu);
                                sdlJeusauv.sdlBoucle();
                            }
                            else {
                                Grille g_sol(infoSurLaPartie.tailleGrille);
                                Grille g_orig(infoSurLaPartie.tailleGrille);
                                Grille g_jeu(infoSurLaPartie.tailleGrille);
                                Grille g_J1(infoSurLaPartie.tailleGrille);
                                Grille g_J2(infoSurLaPartie.tailleGrille);
                                unsigned long int chronoJ1, chronoJ2;
                                bool stopJ1, stopJ2;
                                int nbErr1, nbErr2;
                                gestionnaireSauvegarde.chargerSauvegarde(choixSauvegarde, g_sol, g_orig, g_jeu, &g_J1, &g_J2, &chronoJ1, &chronoJ2, &nbErr1, &nbErr2, &stopJ1, &stopJ2);
                                sdl1Vs1 partieTxt((unsigned char)infoSurLaPartie.tailleGrille, infoSurLaPartie.id, infoSurLaPartie.chrono, g_sol, g_orig, g_jeu, g_J1, g_J2, chronoJ1, chronoJ2, nbErr1, nbErr2, stopJ1, stopJ2);
                                partieTxt.sdlBoucle();
                            }

                        }
                        else if (choixOption == 2) {//supprimer
                            gestionnaireSauvegarde.supprimerSauvegarde(gestionnaireSauvegarde.getInfoSauvegarde(choixSauvegarde).id);
                            menuSauvegardeOuvert = true;

                        }
                    }
                }
            } while (menuSauvegardeOuvert);
        }


        do {

        } while (menuSauvegardeOuvert);

    } while (jeuOuvert);

    

  

    return 0;
}

int selectMode(SDL_Renderer *renderer, TTF_Font* font, Image& im_fondEcran) {
    bool SelectionRunning = true;
    SDL_Event event;
    int modeOver = 0;
    //*********************On initialise les variable des images et hit box puis on met leurs pointeurs dans un tableau pour facilement les passé de fonction en fonction*****//
    Image *tab_img[9];
    hitBox *tab_hit[4];
    Image im_modeClassiqueOver;
    Image im_modeClassiqueAway;
    hitBox hit_classique;
    Image im_modePasAPasOver;
    Image im_modePasAPasAway;
    hitBox hit_PasAPAs;
    Image im_mode1vs1Over;
    Image im_mode1vs1Away;
    hitBox hit_1vs1;
    Image im_sauvegardeOver;
    Image im_sauvegardeAway;
    hitBox hit_sauvegarder;
    tab_img[0] = &im_modeClassiqueOver;
    tab_img[1] = &im_modeClassiqueAway;
    tab_img[2] = &im_modePasAPasOver;
    tab_img[3] = &im_modePasAPasAway;
    tab_img[4] = &im_mode1vs1Over;
    tab_img[5] = &im_mode1vs1Away;
    tab_img[6] = &im_sauvegardeOver;
    tab_img[7] = &im_sauvegardeAway;
    tab_img[8] = &im_fondEcran;

    tab_hit[0] = &hit_classique;
    tab_hit[1] = &hit_PasAPAs;
    tab_hit[2] = &hit_1vs1;
    tab_hit[3] = &hit_sauvegarder;
    //***********************On charge les images a partir du dossier asset ***************************//

    im_modeClassiqueOver.loadFromFile("data/assets/menu/principal/ModeClassique_MousseOver.png", renderer);
    im_modeClassiqueAway.loadFromFile("data/assets/menu/principal/ModeClassique_MousseAway.png", renderer);
    im_modePasAPasOver.loadFromFile("data/assets/menu/principal/ModePasAPas_MousseOver.png", renderer);
    im_modePasAPasAway.loadFromFile("data/assets/menu/principal/ModePasAPas_MousseAway.png", renderer);
    im_mode1vs1Over.loadFromFile("data/assets/menu/principal/Mode1vs1_MousseOver.png", renderer);
    im_mode1vs1Away.loadFromFile("data/assets/menu/principal/Mode1vs1_MousseAway.png", renderer);
    im_sauvegardeOver.loadFromFile("data/assets/menu/principal/Sauvegarde_MousseOver.png", renderer);
    im_sauvegardeAway.loadFromFile("data/assets/menu/principal/Sauvegarde_MousseAway.png", renderer);
    while (SelectionRunning) {

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT) return -1;;//Si l'utilisateur fermé la fenetre, on retourne -1
            //*********Si la souris est au dessus d'une des hitbox on l'indique a la fonction d'affichage pour mettre en avant la preselection ******/

            if (event.type == SDL_MOUSEMOTION) {
                int xm,ym;
                SDL_GetMouseState(&xm, &ym);

                if (hit_classique.is_in(xm,ym)) {
                    modeOver = 1;
                }
                else if(hit_PasAPAs.is_in(xm, ym)) {
                    modeOver = 2;
                }
                else if(hit_1vs1.is_in(xm, ym)) {
                    modeOver = 3;
                }
                else if(hit_sauvegarder.is_in(xm, ym)) {
                    modeOver = 4;
                }
                else {
                    modeOver = 0;
                }
            }
            //****Si l'utilisateur clic sur une des hitbox on fait l'action associée*****/

            if (event.type == SDL_MOUSEBUTTONDOWN) {
                int xm, ym;
                SDL_GetMouseState(&xm, &ym);

                if (hit_classique.is_in(xm, ym)) {
                    return 1;
                }
                else if (hit_PasAPAs.is_in(xm, ym)) {
                    return 2;
                }
                else if (hit_1vs1.is_in(xm, ym)) {
                    return 3;
                }
                else if (hit_sauvegarder.is_in(xm, ym)) {
                    return 4;
                }
            }

        }

        affMenuSelectMode(modeOver, renderer, font, tab_img, tab_hit);

        // on permute les deux buffers (cette fonction ne doit se faire qu'une seule fois dans la boucle)
        SDL_RenderPresent(renderer);
    }
    return -1;

}

void affMenuSelectMode(int ModeOver, SDL_Renderer* renderer, TTF_Font* font, Image** tab_img, hitBox** tab_hit){ //tab_img img contient les pointeurs sur les images dans lordre suivant: Image& im_modeClassiqueOver, Image& im_modeClassiqueAway, Image& im_modePasAPasOver, Image& im_modePasAPasAway, Image& im_mode1vs1Over, Image& im_mode1vs1Away, Image& im_sauvegardeOver, Image& im_sauvegardeAway
    //Remplir l'�cran de blanc
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    tab_img[8]->draw(renderer, 0, 0, WIDTH , HEIGHT);

    
    const  int largeur_tuile_mode = WIDTH/5;
    const  int espace_tuile_mode = (float)((WIDTH - 3*largeur_tuile_mode)/2*       /*Pourcentage de l'espace vide attribué au marge sur le cote                                               -->*/    20/100);
    const  int marge_cote_tuile_mode = (float)((WIDTH - 3 * largeur_tuile_mode)/2* /*Pourcentage de l'espace vide attribué pour entre les tuiles le total doit faire 100% avec celui du dessus -->*/   80/100);
    const  int marge_hauteur_tuile_mode = HEIGHT * 25 / 100;;
    const  int hauteur_tuile_mode = largeur_tuile_mode * 20/13;
   

    //*********************On indique les positions des hitBoxs **********************//
    //hitbox du mode classique
    tab_hit[0]->x1 = marge_cote_tuile_mode;
    tab_hit[0]->x2 = tab_hit[0]->x1 + largeur_tuile_mode;
    tab_hit[0]->y1 = marge_hauteur_tuile_mode;
    tab_hit[0]->y2 = tab_hit[0]->y1 + hauteur_tuile_mode;
    //hitbox du mode PasAPAs
    tab_hit[1]->x1 = marge_cote_tuile_mode + largeur_tuile_mode + espace_tuile_mode;
    tab_hit[1]->x2 = tab_hit[1]->x1 + largeur_tuile_mode;
    tab_hit[1]->y1 = marge_hauteur_tuile_mode;
    tab_hit[1]->y2 = tab_hit[1]->y1 + hauteur_tuile_mode;
    //hitbox du mode 1vs1
    tab_hit[2]->x1 = marge_cote_tuile_mode + 2 * (largeur_tuile_mode + espace_tuile_mode);
    tab_hit[2]->x2 = tab_hit[2]->x1 + largeur_tuile_mode;
    tab_hit[2]->y1 = marge_hauteur_tuile_mode;
    tab_hit[2]->y2 = tab_hit[2]->y1 + hauteur_tuile_mode;
    //hitbox du btn sauvegarde
    tab_hit[3]->x1 = marge_cote_tuile_mode;
    tab_hit[3]->x2 = tab_hit[3]->x1 + 3 * largeur_tuile_mode + 2 * espace_tuile_mode;
    tab_hit[3]->y1 = marge_hauteur_tuile_mode + hauteur_tuile_mode + HEIGHT*5/100;
    tab_hit[3]->y2 = tab_hit[3]->y1 + (1 / 9.23) * tab_hit[3]->getLargeur();

    //********************Place les image sur le render aux positions des hitbox associées************//

    tab_img[1]->draw(renderer, tab_hit[0]->x1 , tab_hit[0]->y1, tab_hit[0]->getLargeur(), tab_hit[0]->getHauteur());
    tab_img[3]->draw(renderer, tab_hit[1]->x1 , tab_hit[1]->y1, tab_hit[1]->getLargeur(), tab_hit[1]->getHauteur());
    tab_img[5]->draw(renderer, tab_hit[2]->x1 , tab_hit[2]->y1, tab_hit[2]->getLargeur(), tab_hit[2]->getHauteur());
    tab_img[7]->draw(renderer, tab_hit[3]->x1 , tab_hit[3]->y1, tab_hit[3]->getLargeur(), tab_hit[3]->getHauteur());

    //*********************Position Du titre***************************//
    SDL_Color couleur = { 0, 0, 0 };
    SDL_Surface* texte = nullptr;
    SDL_Rect position;
    SDL_Texture* texte_texture = nullptr;    //Create Texture pointer

    position.w = WIDTH*70/100;
    position.h = HEIGHT*20/100;
    position.x = WIDTH - position.w - (WIDTH - position.w)/2;
    position.y = WIDTH *1/100;
    char Titre[80] = "Selection du Mode de Jeu";
    texte = TTF_RenderText_Blended(font, Titre, couleur);
    texte_texture = SDL_CreateTextureFromSurface(renderer, texte);
    SDL_FreeSurface(texte);
    //********************Pour mettre la case sur la quelle est la souris*********************//

    if (ModeOver == 1) {
        tab_img[0]->draw(renderer, tab_hit[0]->x1, tab_hit[0]->y1, tab_hit[0]->getLargeur(), tab_hit[0]->getHauteur());

    }
    else  if (ModeOver == 2) {
        tab_img[2]->draw(renderer, tab_hit[1]->x1, tab_hit[1]->y1, tab_hit[1]->getLargeur(), tab_hit[1]->getHauteur());

    }
    else if (ModeOver == 3) {
        tab_img[4]->draw(renderer, tab_hit[2]->x1, tab_hit[2]->y1, tab_hit[2]->getLargeur(), tab_hit[2]->getHauteur());

    }
    else if (ModeOver == 4) {
        tab_img[6]->draw(renderer, tab_hit[3]->x1, tab_hit[3]->y1, tab_hit[3]->getLargeur(), tab_hit[3]->getHauteur());

    }

    SDL_RenderCopy(renderer, texte_texture, nullptr, &position);
    SDL_DestroyTexture(texte_texture);
}

int selectDim(SDL_Renderer* renderer, TTF_Font* font, Image& im_fondEcran){
    bool SelectionRunning = true;
    SDL_Event event;
    int dimOver = 0;

    //*********************On initialise les variable des images et hit box puis on met leurs pointeurs dans un tableau pour facilement les passé de fonction en fonction*****//
    Image* tab_img[9];
    hitBox* tab_hit[4];
    Image im_4X4Over;
    Image im_4X4Away;
    hitBox hit_4x4;
    Image im_9X9Over;
    Image im_9X9Away;
    hitBox hit_9x9;
    Image im_16X16Over;
    Image im_16X16Away;
    hitBox hit_16x16;
    Image im_retourOver;
    Image im_retourAway;
    hitBox hit_retour;
    tab_img[0] = &im_4X4Over;
    tab_img[1] = &im_4X4Away;
    tab_img[2] = &im_9X9Over;
    tab_img[3] = &im_9X9Away;
    tab_img[4] = &im_16X16Over;
    tab_img[5] = &im_16X16Away;
    tab_img[6] = &im_retourOver;
    tab_img[7] = &im_retourAway;
    tab_img[8] = &im_fondEcran;

    tab_hit[0] = &hit_4x4;
    tab_hit[1] = &hit_9x9;
    tab_hit[2] = &hit_16x16;
    tab_hit[3] = &hit_retour;

    //***********************On charge les images a partir du dossier asset ***************************//
    im_4X4Over.loadFromFile("data/assets/menu/principal/selectGrille4x4_MousseOver.png", renderer);
    im_4X4Away.loadFromFile("data/assets/menu/principal/selectGrille4x4_MousseAway.png", renderer);
    im_9X9Over.loadFromFile("data/assets/menu/principal/selectGrille9x9_MousseOver.png", renderer);
    im_9X9Away.loadFromFile("data/assets/menu/principal/selectGrille9x9_MousseAway.png", renderer);
    im_16X16Over.loadFromFile("data/assets/menu/principal/selectGrille16x16_MousseOver.png", renderer);
    im_16X16Away.loadFromFile("data/assets/menu/principal/selectGrille16x16_MousseAway.png", renderer);
    im_retourOver.loadFromFile("data/assets/menu/principal/retour_MousseOver.png", renderer);
    im_retourAway.loadFromFile("data/assets/menu/principal/retour_MousseAway.png", renderer);


    while (SelectionRunning) {

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT) return -2;//Si l'utilisateur fermé la fenetre, on retourne -2

            //*********Si la souris est au dessus d'une des hitbox on l'indique a la fonction d'affichage pour mettre en avant la preselection ******/
            if (event.type == SDL_MOUSEMOTION) {
                int xm, ym;
                SDL_GetMouseState(&xm, &ym);

                if (hit_4x4.is_in(xm, ym)) {
                    dimOver = 1;
                }
                else if (hit_9x9.is_in(xm, ym)) {
                    dimOver = 2;
                }
                else if (hit_16x16.is_in(xm, ym)) {
                    dimOver = 3;
                }
                else if (hit_retour.is_in(xm, ym)) {
                    dimOver = 4;
                }
                else {
                    dimOver = 0;
                }
            }
            //****Si l'utilisateur clic sur une des hitbox on fait l'action associée*****/
            if (event.type == SDL_MOUSEBUTTONDOWN) {
                int xm, ym;
                SDL_GetMouseState(&xm, &ym);

                if (hit_4x4.is_in(xm, ym)) {

                    return 4;
                }
                else if (hit_9x9.is_in(xm, ym)) {

                    return 9;
                }
                else if (hit_16x16.is_in(xm, ym)) {

                    return 16;
                }
                else if (hit_retour.is_in(xm, ym)) {

                    return -1;
                }
            }

        }

        affMenuSelectDim(dimOver, renderer, font, tab_img, tab_hit);

        // on permute les deux buffers (cette fonction ne doit se faire qu'une seule fois dans la boucle)
        SDL_RenderPresent(renderer);
    }
    return -1;

}

void affMenuSelectDim(int ModeOver, SDL_Renderer* renderer, TTF_Font* font, Image** tab_img, hitBox** tab_hit) {
    //Remplir l'�cran de blanc
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    tab_img[8]->draw(renderer, 0, 0, WIDTH, HEIGHT);


    

    //*********************On indique les positions des hitBoxs **********************//
    const  int largeur_tuile_mode = WIDTH / 4;
    const  int espace_tuile_mode = (float)((WIDTH - 3 * largeur_tuile_mode) / 2 *       /*Pourcentage de l'espace vide attribué au marge sur le cote                                               -->*/    20 / 100);
    const  int marge_cote_tuile_mode = (float)((WIDTH - 3 * largeur_tuile_mode) / 2 * /*Pourcentage de l'espace vide attribué pour entre les tuiles le total doit faire 100% avec celui du dessus -->*/   80 / 100);
    const  int marge_hauteur_tuile_mode = HEIGHT * 25 / 100;;
    const  int hauteur_tuile_mode = HEIGHT * 40/100;
    //hitbox du mode 4*4
    tab_hit[0]->x1 = marge_cote_tuile_mode;
    tab_hit[0]->x2 = tab_hit[0]->x1 + largeur_tuile_mode;
    tab_hit[0]->y1 = marge_hauteur_tuile_mode;
    tab_hit[0]->y2 = tab_hit[0]->y1 + hauteur_tuile_mode;
    //hitbox du mode 9*9
    tab_hit[1]->x1 = marge_cote_tuile_mode + largeur_tuile_mode + espace_tuile_mode;
    tab_hit[1]->x2 = tab_hit[1]->x1 + largeur_tuile_mode;
    tab_hit[1]->y1 = marge_hauteur_tuile_mode;
    tab_hit[1]->y2 = tab_hit[1]->y1 + hauteur_tuile_mode;
    //hitbox du mode 16*16
    tab_hit[2]->x1 = marge_cote_tuile_mode + 2 * (largeur_tuile_mode + espace_tuile_mode);
    tab_hit[2]->x2 = tab_hit[2]->x1 + largeur_tuile_mode;
    tab_hit[2]->y1 = marge_hauteur_tuile_mode;
    tab_hit[2]->y2 = tab_hit[2]->y1 + hauteur_tuile_mode;
    //hitbox du btn retour
    tab_hit[3]->x1 = marge_cote_tuile_mode;
    tab_hit[3]->x2 = tab_hit[3]->x1 + 3 * largeur_tuile_mode + 2 * espace_tuile_mode;
    tab_hit[3]->y1 = marge_hauteur_tuile_mode + hauteur_tuile_mode + HEIGHT * 5 / 100;
    tab_hit[3]->y2 = tab_hit[3]->y1 + (1 / 9.23) * tab_hit[3]->getLargeur();
 
    //********************Place les image sur le render aux positions des hitbox associées************//
    tab_img[1]->draw(renderer, tab_hit[0]->x1, tab_hit[0]->y1, tab_hit[0]->getLargeur(), tab_hit[0]->getHauteur());
    tab_img[3]->draw(renderer, tab_hit[1]->x1, tab_hit[1]->y1, tab_hit[1]->getLargeur(), tab_hit[1]->getHauteur());
    tab_img[5]->draw(renderer, tab_hit[2]->x1, tab_hit[2]->y1, tab_hit[2]->getLargeur(), tab_hit[2]->getHauteur());
    tab_img[7]->draw(renderer, tab_hit[3]->x1, tab_hit[3]->y1, tab_hit[3]->getLargeur(), tab_hit[3]->getHauteur());
    
    //*********************Position Du titre***************************//
    SDL_Color couleur = { 0, 0, 0 }; //Couleur du Titre
    SDL_Texture* texte_texture = nullptr;    //Create Texture pointer
    SDL_Surface* texte = nullptr;
    SDL_Rect position;//Position du titre

    position.w = WIDTH * 70 / 100;
    position.h = HEIGHT * 20 / 100;
    position.x = WIDTH - position.w - (WIDTH - position.w) / 2;
    position.y = WIDTH * 1 / 100;

    char Titre[80] = "Selection de la dimension de la grille";
    texte = TTF_RenderText_Blended(font, Titre, couleur);
    texte_texture = SDL_CreateTextureFromSurface(renderer, texte);
    SDL_FreeSurface(texte);

    //********************Pour mettre la case sur la quelle est la souris*********************//
    if (ModeOver == 1) {
        tab_img[0]->draw(renderer, tab_hit[0]->x1, tab_hit[0]->y1, tab_hit[0]->getLargeur(), tab_hit[0]->getHauteur());

    }
    else  if (ModeOver == 2) {
        tab_img[2]->draw(renderer, tab_hit[1]->x1, tab_hit[1]->y1, tab_hit[1]->getLargeur(), tab_hit[1]->getHauteur());

    }
    else if (ModeOver == 3) {
        tab_img[4]->draw(renderer, tab_hit[2]->x1, tab_hit[2]->y1, tab_hit[2]->getLargeur(), tab_hit[2]->getHauteur());

    }
    else if (ModeOver == 4) {
        tab_img[6]->draw(renderer, tab_hit[3]->x1, tab_hit[3]->y1, tab_hit[3]->getLargeur(), tab_hit[3]->getHauteur());

    }
    //********************************************************************************************//

    SDL_RenderCopy(renderer, texte_texture, nullptr, &position);
    SDL_DestroyTexture(texte_texture);
}


int selectSauvegarde(gestSauvegarde& gestS, SDL_Renderer* renderer, TTF_Font* font, Image& im_fondEcran) {
    bool SelectionRunning = true;
    SDL_Event event;
    int modeOver = 0;
    unsigned int premiereSauvegardeAffichee = 0;
    //*********************On initialise les variable des images et hit box puis on met leurs pointeurs dans un tableau pour facilement les passé de fonction en fonction*****//
    Image* tab_img[3];
    Image im_btnHaut;
    Image im_btnBas;
    hitBox* tab_hit[8];
    hitBox hit_btnHaut;
    hitBox hit_btnBas;
    hitBox hit_retour;
    hitBox hit_sauvegarde1;
    hitBox hit_sauvegarde2;
    hitBox hit_sauvegarde3;
    hitBox hit_sauvegarde4;
    hitBox hit_sauvegarde5;
    tab_img[0] = &im_btnHaut;
    tab_img[1] = &im_btnBas;
    tab_img[2] = &im_fondEcran;

    tab_hit[0] = &hit_btnHaut;
    tab_hit[1] = &hit_btnBas;
    tab_hit[2] = &hit_retour;
    tab_hit[3] = &hit_sauvegarde1;
    tab_hit[4] = &hit_sauvegarde2;
    tab_hit[5] = &hit_sauvegarde3;
    tab_hit[6] = &hit_sauvegarde4;
    tab_hit[7] = &hit_sauvegarde5;

    im_btnHaut.loadFromFile("data/assets/menu/principal/flecheHaut.png", renderer);
    im_btnBas.loadFromFile("data/assets/menu/principal/flechesBas.png", renderer);
    gestS.updateListe();
    //***********************On charge les images a partir du dossier asset ***************************//
    while (SelectionRunning) {

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT) return -1;;//Si l'utilisateur fermé la fenetre, on retourne -1

            //*********Si la souris est au dessus d'une des hitbox on l'indique a la fonction d'affichage pour mettre en avant la preselection ******
            if (event.type == SDL_MOUSEMOTION) {
                int xm, ym;
                SDL_GetMouseState(&xm, &ym);

                if (hit_btnHaut.is_in(xm, ym)) {
                    modeOver = 1;
                }
                else if (hit_btnBas.is_in(xm, ym)) {
                    modeOver = 2;
                }
                else if (hit_retour.is_in(xm, ym)) {
                    modeOver = 3;
                }
                else if (hit_sauvegarde1.is_in(xm, ym)) {
                    modeOver = 4;
                }
                else if (hit_sauvegarde2.is_in(xm, ym)) {
                    modeOver = 5;
                }
                else if (hit_sauvegarde3.is_in(xm, ym)) {
                    modeOver = 6;
                }
                else if (hit_sauvegarde4.is_in(xm, ym)) {
                    modeOver = 7;
                }
                else if (hit_sauvegarde5.is_in(xm, ym)) {
                    modeOver = 8;
                }
                else {
                    modeOver = 0;
                }
            }
            //****Si l'utilisateur clic sur une des hitbox on fait l'action associée*****/

            if (event.type == SDL_MOUSEBUTTONDOWN) {
                int xm, ym;
                SDL_GetMouseState(&xm, &ym);

                if (hit_btnHaut.is_in(xm, ym)) {
                    premiereSauvegardeAffichee--;
                }
                else if (hit_btnBas.is_in(xm, ym)) {
                    premiereSauvegardeAffichee++;
                }
                else if (hit_retour.is_in(xm, ym)) {
                    return -1;
                }
                else if (hit_sauvegarde1.is_in(xm, ym)) {
                    return  gestS.listeSauvegarde[premiereSauvegardeAffichee].id;
                }
                else if (hit_sauvegarde2.is_in(xm, ym)) {
                    return gestS.listeSauvegarde[premiereSauvegardeAffichee + 1].id;
                }
                else if (hit_sauvegarde3.is_in(xm, ym)) {
                    return gestS.listeSauvegarde[premiereSauvegardeAffichee + 2].id;
                }
                else if (hit_sauvegarde4.is_in(xm, ym)) {
                    return gestS.listeSauvegarde[premiereSauvegardeAffichee + 3].id;
                }
                else if (hit_sauvegarde5.is_in(xm, ym)) {
                    return gestS.listeSauvegarde[premiereSauvegardeAffichee + 4].id;
                }
            }

        }

        affMenuSelectSauvegarde(modeOver, premiereSauvegardeAffichee, gestS, renderer, font, tab_hit, tab_img);

        // on permute les deux buffers (cette fonction ne doit se faire qu'une seule fois dans la boucle)
        SDL_RenderPresent(renderer);
    }
    return -1;
}

void affMenuSelectSauvegarde(int boutonOver, unsigned int premiereSauvegardeAffichee, gestSauvegarde& gestS, SDL_Renderer* renderer, TTF_Font* font, hitBox** tab_hit, Image** tab_img) {
    //Remplir l'�cran de blanc
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    tab_img[2]->draw(renderer, 0, 0, WIDTH, HEIGHT);

    char message[200];
    string str;




    //*********************On indique les positions des hitBoxs **********************//
    
    //hitbox du bouton retour
    tab_hit[2]->x1 = 0;
    tab_hit[2]->x2 = 100;
    tab_hit[2]->y1 = 0;
    tab_hit[2]->y2 = 20;
    //hitbox de la premiere sauvegarde affichee
    tab_hit[3]->y1 = 230;
    tab_hit[3]->y2 = 280;
    tab_hit[3]->x1 = 70;
    tab_hit[3]->x2 = min(int(tab_hit[3]->x1 + (gestS.listeSauvegarde[premiereSauvegardeAffichee].name.length() + 2  + 12) * 60 * tab_hit[3]->getHauteur() / 100), WIDTH - 70);
    //hitbox de la deuxieme sauvegarde affichee
    tab_hit[4]->y1 = 300;
    tab_hit[4]->y2 = 350;
    tab_hit[4]->x1 = 70;
    tab_hit[4]->x2 = min(int(tab_hit[4]->x1 + (gestS.listeSauvegarde[premiereSauvegardeAffichee+1].name.length() + 2 + 12) * 60 * tab_hit[4]->getHauteur() / 100), WIDTH - 70);
    //hitbox de la troisieme sauvegarde affichee.
    tab_hit[5]->y1 = 370;
    tab_hit[5]->y2 = 420;
    tab_hit[5]->x1 = 70;
    tab_hit[5]->x2 = min(int(tab_hit[5]->x1 + (gestS.listeSauvegarde[premiereSauvegardeAffichee+2].name.length() + 2 + 12) * 60 * tab_hit[5]->getHauteur() / 100), WIDTH - 70);

    //hitbox de la quatrieme sauvegarde affichee
    tab_hit[6]->y1 = 440;
    tab_hit[6]->y2 = 490;
    tab_hit[6]->x1 = 70;
    tab_hit[6]->x2 = min(int(tab_hit[6]->x1 + (gestS.listeSauvegarde[premiereSauvegardeAffichee+3].name.length() + 2 + 12) * 60 * tab_hit[6]->getHauteur() / 100), WIDTH - 70);

    //hitbox de la cinquieme sauvegarde affichee
    tab_hit[7]->y1 = 510;
    tab_hit[7]->y2 = 560;
    tab_hit[7]->x1 = 70;
    tab_hit[7]->x2 = min(int(tab_hit[7]->x1 + (gestS.listeSauvegarde[premiereSauvegardeAffichee+4].name.length() + 2 + 12) * 60 * tab_hit[7]->getHauteur() / 100), WIDTH - 70);
    if (gestS.nbSauvegarde > premiereSauvegardeAffichee + 5) {
        //hitbox + image  du bouton bas
        tab_hit[1]->x1 = WIDTH - 60;
        tab_hit[1]->x2 = WIDTH - 10;
        tab_hit[1]->y1 = tab_hit[7]->y1;
        tab_hit[1]->y2 = tab_hit[7]->y1 + 50;
        tab_img[1]->draw(renderer, tab_hit[1]->x1, tab_hit[1]->y1, tab_hit[1]->getLargeur(), tab_hit[1]->getHauteur());
    }
    else {
        tab_hit[1]->reset();
    }
    if (premiereSauvegardeAffichee > 0) {
        //hitbox + image du bouton haut
        tab_hit[0]->x1 = WIDTH - 60;
        tab_hit[0]->x2 = WIDTH - 10;
        tab_hit[0]->y1 = tab_hit[3]->y1;
        tab_hit[0]->y2 = tab_hit[3]->y1 + 50;
        tab_img[0]->draw(renderer, tab_hit[0]->x1, tab_hit[0]->y1, tab_hit[0]->getLargeur(), tab_hit[0]->getHauteur());
    }
    else {
        tab_hit[0]->reset();
    }
    
    //*********************Position Du titre***************************//
    SDL_Color couleur = { 0, 0, 0 };
    SDL_Surface* texte = nullptr;
    SDL_Rect position;
    SDL_Texture* texte_texture = NULL;    //Create Texture pointer

    position.w = WIDTH * 70 / 100;
    position.h = 70;
    position.x = WIDTH - position.w - (WIDTH - position.w) / 2;
    position.y = 0;
    texte = TTF_RenderText_Blended(font, "Menu sauvegardes", couleur);
    texte_texture = SDL_CreateTextureFromSurface(renderer, texte);
    SDL_FreeSurface(texte);
    SDL_RenderCopy(renderer, texte_texture, NULL, &position);
    SDL_DestroyTexture(texte_texture);

    //*********************Position Du legend***************************//
    position.w = 600;
    position.h = 70;
    position.x = 200;
    position.y = 80;
    texte = TTF_RenderText_Blended(font, "Nom de la sauvegarde | taille de la grille", couleur);
    texte_texture = SDL_CreateTextureFromSurface(renderer, texte);
    SDL_FreeSurface(texte);
    SDL_RenderCopy(renderer, texte_texture, NULL, &position);
    SDL_DestroyTexture(texte_texture);
    //*********************Position Des btns save ***************************//
    for (int i = 0; i < 5; i++) {
        if (premiereSauvegardeAffichee + i < gestS.nbSauvegarde) {
            if (boutonOver == 4 + i) {
                couleur.r = 0;
                couleur.g = 0;
                couleur.b = 0;
            }
            else {
                couleur.r = 100;
                couleur.g = 100;
                couleur.b = 100;
            }
            position.w = tab_hit[3 + i]->getLargeur();
            position.h = tab_hit[3 + i]->getHauteur();
            position.x = tab_hit[3 + i]->x1;
            position.y = tab_hit[3 + i]->y1;
            /*str = (int(gestS.listeSauvegarde[premiereSauvegardeAffichee + i].id + '0'));
            str += " | ";*/
            str = gestS.listeSauvegarde[premiereSauvegardeAffichee + i].name;
            str += " | ";
            str += to_string((int)gestS.listeSauvegarde[premiereSauvegardeAffichee + i].tailleGrille);
            str += "x";
            str += to_string((int)gestS.listeSauvegarde[premiereSauvegardeAffichee + i].tailleGrille);
            str += " | Mode ";
            if (gestS.getInfoSauvegarde(gestS.listeSauvegarde[premiereSauvegardeAffichee + i].id).modeJeu == 1) {
                str += "classique";
            }else if (gestS.getInfoSauvegarde(gestS.listeSauvegarde[premiereSauvegardeAffichee + i].id).modeJeu == 2) {
                str += "Pas a Pas";
            }
            else if(gestS.getInfoSauvegarde(gestS.listeSauvegarde[premiereSauvegardeAffichee + i].id).modeJeu == 3) {
                str += "1 VS 1   ";
            }
            else {
                str += "inconnu  ";
            }
     
            strcpy(message, str.c_str());
            texte = TTF_RenderText_Blended(font, message, couleur);
            texte_texture = SDL_CreateTextureFromSurface(renderer, texte);
            SDL_FreeSurface(texte);
            SDL_RenderCopy(renderer, texte_texture, NULL, &position);
            SDL_DestroyTexture(texte_texture);
        }
        else {
            tab_hit[3 + i]->reset();
        }
    }
    //*********************Position btn retour ***************************//

    if (boutonOver == 3) {
        couleur.r = 0;
        couleur.g = 0;
        couleur.b = 0;
    }
    else {
        couleur.r = 100;
        couleur.g = 100;
        couleur.b = 100;
    }
    position.w = tab_hit[2]->getLargeur();
    position.h = tab_hit[2]->getHauteur();
    position.x = tab_hit[2]->x1;
    position.y = tab_hit[2]->y1;
    texte = TTF_RenderText_Blended(font, "Retour", couleur);
    texte_texture = SDL_CreateTextureFromSurface(renderer, texte);
    SDL_FreeSurface(texte);
    SDL_RenderCopy(renderer, texte_texture, NULL, &position);
    SDL_DestroyTexture(texte_texture);


}

int selectOptionSauvegarde(gestSauvegarde& gestS, unsigned int idSauvegarde, SDL_Renderer* renderer, TTF_Font* font) {

    bool SelectionRunning = true;
    SDL_Event event;
    int modeOver = 0;
    //*********************On initialise les variable des images et hit box puis on met leurs pointeurs dans un tableau pour facilement les passé de fonction en fonction*****//

    hitBox* tab_hit[4];
    hitBox hit_ouvrir;
    hitBox hit_supr;
    hitBox hit_retour;
    hitBox hit_renommer;

    tab_hit[0] = &hit_ouvrir;
    tab_hit[1] = &hit_supr;
    tab_hit[2] = &hit_retour;
    tab_hit[3] = &hit_renommer;


    //***********************On charge les images a partir du dossier asset ***************************//
    while (SelectionRunning) {

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT) return -1;;//Si l'utilisateur fermé la fenetre, on retourne -1

            //*********Si la souris est au dessus d'une des hitbox on l'indique a la fonction d'affichage pour mettre en avant la preselection ******
            if (event.type == SDL_MOUSEMOTION) {
                int xm, ym;
                SDL_GetMouseState(&xm, &ym);

                if (hit_ouvrir.is_in(xm, ym)) {
                    modeOver = 1;
                }
                else if (hit_supr.is_in(xm, ym)) {
                    modeOver = 2;
                }
                else if (hit_retour.is_in(xm, ym)) {
                    modeOver = 3;
                }
                else if (hit_renommer.is_in(xm, ym)) {
                    modeOver = 4;
                }
                else {
                    modeOver = 0;
                }
            }
            //****Si l'utilisateur clic sur une des hitbox on fait l'action associée*****/

            if (event.type == SDL_MOUSEBUTTONDOWN) {
                int xm, ym;
                SDL_GetMouseState(&xm, &ym);

                if (hit_ouvrir.is_in(xm, ym)) {
                    return 1;
                }
                else if (hit_supr.is_in(xm, ym)) {
                    return 2;
                }
                else if (hit_retour.is_in(xm, ym)) {
                    return -1;
                }
                else if (hit_renommer.is_in(xm, ym)) {
                    SaisieTextPopUp popUp(font);

                    string nouveauNom = popUp.getTexteSaisie(300, 100, "Nouveau nom de la partie", "",gestS.getInfoSauvegarde(idSauvegarde).name, true);
                    gestS.renommerSauvegarde(gestS.getInfoSauvegarde(idSauvegarde).id, nouveauNom);
                }

            }

        }

        affMenuSelectOptionSauvegarde(modeOver, idSauvegarde, gestS, renderer, font, tab_hit);

        // on permute les deux buffers (cette fonction ne doit se faire qu'une seule fois dans la boucle)
        SDL_RenderPresent(renderer);
    }
    return -1;
}

void affMenuSelectOptionSauvegarde(int boutonOver, unsigned int idSauvegarde, gestSauvegarde& gestS, SDL_Renderer* renderer, TTF_Font* font, hitBox** tab_hit) {
    //Remplir l'�cran de blanc
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    char message[200];
    string str;




    //*********************On indique les positions des hitBoxs **********************//

    //hitbox du bouton ouvrir
    tab_hit[0]->x1 = 20;
    tab_hit[0]->x2 = 100;
    tab_hit[0]->y1 = 300;
    tab_hit[0]->y2 = 320;
    //hitbox du btn supr
    tab_hit[1]->x1 = 20;
    tab_hit[1]->x2 = 100;
    tab_hit[1]->y1 = 350;
    tab_hit[1]->y2 = 370;
    //hitbox du btn retour
    tab_hit[2]->x1 = 20;
    tab_hit[2]->x2 = 100;
    tab_hit[2]->y1 = 400;
    tab_hit[2]->y2 = 420;
    //hitbox du btn renommer
    tab_hit[3]->x1 = 20;
    tab_hit[3]->x2 = 100;
    tab_hit[3]->y1 = 440;
    tab_hit[3]->y2 = 460;

    //*********************Position Du titre***************************//
    SDL_Color couleur = { 0, 0, 0 };
    SDL_Surface* texte = nullptr;
    SDL_Rect position;
    SDL_Texture* texte_texture = NULL;    //Create Texture pointer

    position.w = WIDTH * 70 / 100;
    position.h = 80;
    position.x = WIDTH - position.w - (WIDTH - position.w) / 2;
    position.y = 0;
    texte = TTF_RenderText_Blended(font, "Info sur la sauvegarde", couleur);
    texte_texture = SDL_CreateTextureFromSurface(renderer, texte);
    SDL_FreeSurface(texte);
    SDL_RenderCopy(renderer, texte_texture, NULL, &position);
    SDL_DestroyTexture(texte_texture);
    //*********************Position Des infos ***************************/

    couleur.r = 0;
    couleur.g = 0;
    couleur.b = 0;
    position.w = WIDTH * 70 / 100;
    position.h = 70;
    position.x = WIDTH - position.w - (WIDTH - position.w) / 2;
    position.y = 90;

    /*str = gestS.getInfoSauvegarde(idSauvegarde).id + '0';
    str += " | ";*/
    str = gestS.getInfoSauvegarde(idSauvegarde).name;
    str += " | ";
    str += to_string((int)gestS.getInfoSauvegarde(idSauvegarde).tailleGrille);
    str += "x";
    str += to_string((int)gestS.getInfoSauvegarde(idSauvegarde).tailleGrille);

    strcpy(message, str.c_str());
    texte = TTF_RenderText_Blended(font, message, couleur);
    texte_texture = SDL_CreateTextureFromSurface(renderer, texte);
    SDL_FreeSurface(texte);
    SDL_RenderCopy(renderer, texte_texture, NULL, &position);
    SDL_DestroyTexture(texte_texture);
    //*********************Position du btn ouvrir***************************/
    if (boutonOver == 1) {
        couleur.r = 0;
        couleur.g = 0;
        couleur.b = 0;
    }
    else {
        couleur.r = 100;
        couleur.g = 100;
        couleur.b = 100;
    }
    position.w = tab_hit[0]->getLargeur();
    position.h = tab_hit[0]->getHauteur();
    position.x = tab_hit[0]->x1;
    position.y = tab_hit[0]->y1;

    texte = TTF_RenderText_Blended(font, "Ouvrir", couleur);
    texte_texture = SDL_CreateTextureFromSurface(renderer, texte);
    SDL_FreeSurface(texte);
    SDL_RenderCopy(renderer, texte_texture, NULL, &position);
    SDL_DestroyTexture(texte_texture);

    //*********************Position du btn supr***************************/
    if (boutonOver == 2) {
        couleur.r = 0;
        couleur.g = 0;
        couleur.b = 0;
    }
    else {
        couleur.r = 100;
        couleur.g = 100;
        couleur.b = 100;
    }
    position.w = tab_hit[1]->getLargeur();
    position.h = tab_hit[1]->getHauteur();
    position.x = tab_hit[1]->x1;
    position.y = tab_hit[1]->y1;

    texte = TTF_RenderText_Blended(font, "Supprimer", couleur);
    texte_texture = SDL_CreateTextureFromSurface(renderer, texte);
    SDL_FreeSurface(texte);
    SDL_RenderCopy(renderer, texte_texture, NULL, &position);
    SDL_DestroyTexture(texte_texture);
    //*********************Position du btn retour***************************/
    if (boutonOver == 3) {
        couleur.r = 0;
        couleur.g = 0;
        couleur.b = 0;
    }
    else {
        couleur.r = 100;
        couleur.g = 100;
        couleur.b = 100;
    }
    position.w = tab_hit[2]->getLargeur();
    position.h = tab_hit[2]->getHauteur();
    position.x = tab_hit[2]->x1;
    position.y = tab_hit[2]->y1;

    texte = TTF_RenderText_Blended(font, "Retour", couleur);
    texte_texture = SDL_CreateTextureFromSurface(renderer, texte);
    SDL_FreeSurface(texte);
    SDL_RenderCopy(renderer, texte_texture, NULL, &position);
    SDL_DestroyTexture(texte_texture);
    //*********************Position du btn Renommer***************************/
    if (boutonOver == 4) {
        couleur.r = 0;
        couleur.g = 0;
        couleur.b = 0;
    }
    else {
        couleur.r = 100;
        couleur.g = 100;
        couleur.b = 100;
    }
    position.w = tab_hit[3]->getLargeur();
    position.h = tab_hit[3]->getHauteur();
    position.x = tab_hit[3]->x1;
    position.y = tab_hit[3]->y1;

    texte = TTF_RenderText_Blended(font, "Renommer", couleur);
    texte_texture = SDL_CreateTextureFromSurface(renderer, texte);
    SDL_FreeSurface(texte);
    SDL_RenderCopy(renderer, texte_texture, NULL, &position);
    SDL_DestroyTexture(texte_texture);

}
