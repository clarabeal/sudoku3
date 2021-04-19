#include "SDL_Classique.h"
#include "SDL_PasAPas.h"
#include <iostream>
using namespace std;
//format 16/9
#define WIDTH 1024
#define HEIGHT 576


void affMenuSelectMode(int ModeOver, SDL_Renderer* renderer, TTF_Font* font, Image** tab_img, hitBox** tab_hit); //tab_img img contient les pointeurs sur les images dans lordre suivant: Image& im_modeClassiqueOver, Image& im_modeClassiqueAway, Image& im_modePasAPasOver, Image& im_modePasAPasAway, Image& im_mode1vs1Over, Image& im_mode1vs1Away, Image& im_sauvegardeOver, Image& im_sauvegardeAway
int selectMode(SDL_Renderer* renderer, TTF_Font* font);
void affMenuSelectDim(int ModeOver, SDL_Renderer* renderer, TTF_Font* font, Image** tab_img, hitBox** tab_hit); //tab_img img contient les pointeurs sur les images dans lordre suivant:Image& im_4X4Over, Image& im_4X4Away, Image& im_9X9Over, Image& im_9X9Away, Image& im_16X16Over, Image& im_16X16Away, Image& im_retourOver, Image& im_retourAway
int selectDim(SDL_Renderer* renderer, TTF_Font* font);

int main (int argc, char* argv[]){
    cout << "hello" << endl;
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
    font_menu = TTF_OpenFont("data/fonts/BungeeShade-Regular.ttf", 120);
    if (!font_menu) {
        font_menu = TTF_OpenFont("../data/fonts/BungeeShade-Regular.ttf", 120);

    }
    //font = TTF_OpenFont("../data/fonts/arial.ttf", 40);

    int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    //creation de la fenetre : 
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
    
    int dim = -1;
    int mode = 0;
    do {
        do {
            mode = selectMode(renderer, font_menu);
            if (mode == -1) {
                return 0;
            }else if (mode == 4) {
                //menu sauvegarde
            }
        } while (mode == 4);

        dim = selectDim(renderer, font_menu);
        if (dim == -2) return 0;

    } while (dim == -1);
    
    TTF_CloseFont(font_menu);
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

   if (mode == 1) {
       sdlJeuClassique sJeu(dim);
       sJeu.sdlBoucle();

   }else if (mode == 2) {
       sdlJeuPasAPas sJeu(dim);
       sJeu.sdlBoucle();
   }
   else if(mode == 3) {
       // 1vs1
   }

    return 0;
}

int selectMode(SDL_Renderer *renderer, TTF_Font* font) {
    bool SelectionRunning = true;
    SDL_Event event;
    int modeOver = 0;
    //*********************On initialise les variable des images et hit box puis on met leurs pointeurs dans un tableau pour facilement les passé de fonction en fonction*****//
    Image *tab_img[8];
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
                   // return 3;
                }
                else if (hit_sauvegarder.is_in(xm, ym)) {
                    //return 4;
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
   
    
    const  int largeur_tuile_mode = WIDTH/5;
    const  int espace_tuile_mode = (float)((WIDTH - 3*largeur_tuile_mode)/2*       /*Pourcentage de l'espace vide attribué au marge sur le cote                                               -->*/    20/100);
    const  int marge_cote_tuile_mode = (float)((WIDTH - 3 * largeur_tuile_mode)/2* /*Pourcentage de l'espace vide attribué pour entre les tuiles le total doit faire 100% avec celui du dessus -->*/   80/100);
    const  int marge_hauteur_tuile_mode = HEIGHT * 25 / 100;;
    const  int hauteur_tuile_mode = largeur_tuile_mode * 20/13;
   

    //*********************On indique les positions des hitboxes **********************//
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

int selectDim(SDL_Renderer* renderer, TTF_Font* font) {
    bool SelectionRunning = true;
    SDL_Event event;
    int dimOver = 0;

    //*********************On initialise les variable des images et hit box puis on met leurs pointeurs dans un tableau pour facilement les passé de fonction en fonction*****//
    Image* tab_img[8];
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


    

    //*********************On indique les positions des hitboxes **********************//
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
