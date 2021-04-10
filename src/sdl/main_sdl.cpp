#include "SDL_Classique.h"
#include <iostream>
using namespace std;
//format 16/9
#define WIDTH 1024
#define HEIGHT 576


void affMenuSelectMode(int ModeOver, SDL_Renderer* renderer, TTF_Font* font, Image& im_modeClassiqueOver, Image& im_modeClassiqueAway, Image& im_modePasAPasOver, Image& im_modePasAPasAway, Image& im_mode1vs1Over, Image& im_mode1vs1Away, Image& im_sauvegardeOver, Image& im_sauvegardeAway);
int selectMode(SDL_Renderer* renderer, TTF_Font* font);
void affMenuSelectDim(int ModeOver, SDL_Renderer* renderer, TTF_Font* font, Image& im_4X4Over, Image& im_4X4Away, Image& im_9X9Over, Image& im_9X9Away, Image& im_16X16Over, Image& im_16X16Away, Image& im_retourOver, Image& im_retourAway);
int selectDim(SDL_Renderer* renderer, TTF_Font* font);

int main (int argc, char* argv[]){
    SDL_Window* window;
    SDL_Renderer* renderer;

    TTF_Font* font_menu;
    Image font_im;
    SDL_Color font_color;

    Image im_grille;


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
    if (window == NULL)
    {
        cout << "Erreur lors de la creation de la fenetre : " << SDL_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    //creation du rendu : 
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL)
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
            if (mode == 4) {
                //menu sauvegarde
            }
        } while (mode == 4);

        dim = selectDim(renderer, font_menu);


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
       // Pas aPAs
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
    Image im_modeClassiqueOver;
    Image im_modeClassiqueAway;
    Image im_modePasAPasOver;
    Image im_modePasAPasAway;
    Image im_mode1vs1Over;
    Image im_mode1vs1Away;
    Image im_sauvegardeOver;
    Image im_sauvegardeAway;
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
            if (event.type == SDL_QUIT) SelectionRunning = false;
            if (event.type == SDL_KEYDOWN)
            {
                switch (event.key.keysym.scancode)
                {
                case SDL_SCANCODE_Q:
                    SelectionRunning = false;
                    break;
                default:
                    break;
                }
            }
            if (event.type == SDL_MOUSEMOTION) {
                int xm,ym;
                SDL_GetMouseState(&xm, &ym);

                if (xm>150 && xm<150+200 && ym > 150 && ym < 150+307) {
                    modeOver = 1;
                }
                else if(xm > 150 +200 +62 && xm < 150 + 2*(200)+62 && ym > 150 && ym < 150 + 307) {
                    modeOver = 2;
                }
                else if(xm > 150 + 2 * (200 + 62)  && xm < 150 + 3 * (200) + 2*62 && ym > 150 && ym < 150 + 307) {
                    modeOver = 3;
                }
                else if(xm > 150 && xm < WIDTH - 150 && ym > 470 && ym < 570) {
                    modeOver = 4;
                }
                else {
                    modeOver = 0;
                }
            }
            if (event.type == SDL_MOUSEBUTTONDOWN) {
                int xm, ym;
                SDL_GetMouseState(&xm, &ym);

                if (xm > 150 && xm < 150 + 200 && ym > 150 && ym < 150 + 307) {
                    return 1;
                }
                else if (xm > 150 + 200 + 62 && xm < 150 + 2 * (200) + 62 && ym > 150 && ym < 150 + 307) {
                   // return 2;
                }
                else if (xm > 150 + 2 * (200 + 62) && xm < 150 + 3 * (200) + 2 * 62 && ym > 150 && ym < 150 + 307) {
                   // return 3;
                }
                else if (xm > 150 && xm < WIDTH - 150 && ym > 470 && ym < 570) {
                    //return 4;
                }
            }

        }

        affMenuSelectMode(modeOver, renderer, font,im_modeClassiqueOver,im_modeClassiqueAway,im_modePasAPasOver,im_modePasAPasAway,im_mode1vs1Over,im_mode1vs1Away,im_sauvegardeOver,im_sauvegardeAway);

        // on permute les deux buffers (cette fonction ne doit se faire qu'une seule fois dans la boucle)
        SDL_RenderPresent(renderer);
    }
}

void affMenuSelectMode(int ModeOver, SDL_Renderer* renderer, TTF_Font* font, Image& im_modeClassiqueOver, Image& im_modeClassiqueAway, Image& im_modePasAPasOver,Image& im_modePasAPasAway, Image& im_mode1vs1Over, Image& im_mode1vs1Away, Image& im_sauvegardeOver, Image& im_sauvegardeAway) {
    //Remplir l'�cran de blanc
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    SDL_Color couleur = { 0, 0, 0 };
    SDL_Surface* texte = nullptr;
    SDL_Rect position;
    SDL_Texture* texte_texture = NULL;    //Create Texture pointer
    
    const unsigned int largeur_tuile_mode = 200;
    const unsigned int hauteur_tuile_mode = 307;
    char Titre[80] = "Selection du Mode de Jeu";
    texte = TTF_RenderText_Blended(font, Titre, couleur);
    texte_texture = SDL_CreateTextureFromSurface(renderer, texte);
    SDL_FreeSurface(texte);

   

    im_modeClassiqueAway.draw(renderer, 150, 150, largeur_tuile_mode, hauteur_tuile_mode);
    im_modePasAPasAway.draw(renderer, 150 + largeur_tuile_mode + 62, 150, largeur_tuile_mode, hauteur_tuile_mode);
    im_mode1vs1Away.draw(renderer, 150 + 2*(largeur_tuile_mode +62), 150, largeur_tuile_mode, hauteur_tuile_mode);
    im_sauvegardeAway.draw(renderer, 150, 470, 3 * largeur_tuile_mode + 2 * 62, (1 / 9.23) * (3 * largeur_tuile_mode + 2 * 62));

    position.w = 700;
    position.h = 100;
    position.x = WIDTH - position.w - (WIDTH - position.w)/2;
    position.y = 10;
    if (ModeOver == 1) {
        im_modeClassiqueOver.draw(renderer, 150, 150, largeur_tuile_mode, hauteur_tuile_mode);

    }else  if (ModeOver == 2) {
        im_modePasAPasOver.draw(renderer, 150 + largeur_tuile_mode + 62, 150, largeur_tuile_mode, hauteur_tuile_mode);

    }
    else if (ModeOver == 3) {
        im_mode1vs1Over.draw(renderer, 150 + 2 * (largeur_tuile_mode + 62), 150, largeur_tuile_mode, hauteur_tuile_mode);

    }
    else if (ModeOver == 4) {
        im_sauvegardeOver.draw(renderer, 150, 470, 3 * largeur_tuile_mode + 2 * 62, (1 / 9.23) * (3 * largeur_tuile_mode + 2 * 62));

    }

    int ok = SDL_RenderCopy(renderer, texte_texture, NULL, &position);
    SDL_DestroyTexture(texte_texture);
}

int selectDim(SDL_Renderer* renderer, TTF_Font* font) {
    bool SelectionRunning = true;
    SDL_Event event;
    int modeOver = 0;
    Image im_4X4Over;
    Image im_4X4Away;
    Image im_9X9Over;
    Image im_9X9Away;
    Image im_16X16Over;
    Image im_16X16Away;
    Image im_retourOver;
    Image im_retourAway;
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
            if (event.type == SDL_QUIT) SelectionRunning = false;
            if (event.type == SDL_KEYDOWN)
            {
                switch (event.key.keysym.scancode)
                {
                case SDL_SCANCODE_Q:
                    SelectionRunning = false;
                    break;
                default:
                    break;
                }
            }
            if (event.type == SDL_MOUSEMOTION) {
                int xm, ym;
                SDL_GetMouseState(&xm, &ym);

                if (xm > 150 && xm < 150 + 200 && ym > 150 && ym < 150 + 200) {
                    modeOver = 1;
                }
                else if (xm > 150 + 200 + 62 && xm < 150 + 2 * (200) + 62 && ym > 150 && ym < 150 + 200) {
                    modeOver = 2;
                }
                else if (xm > 150 + 2 * (200 + 62) && xm < 150 + 3 * (200) + 2 * 62 && ym > 150 && ym < 150 + 200) {
                    modeOver = 3;
                }
                else if (xm > 150 && xm < WIDTH - 150 && ym > 470 && ym < 570) {
                    modeOver = 4;
                }
                else {
                    modeOver = 0;
                }
            }
            if (event.type == SDL_MOUSEBUTTONDOWN) {
                int xm, ym;
                SDL_GetMouseState(&xm, &ym);

                if (xm > 150 && xm < 150 + 200 && ym > 150 && ym < 150 + 307) {
                    return 4;
                }
                else if (xm > 150 + 200 + 62 && xm < 150 + 2 * (200) + 62 && ym > 150 && ym < 150 + 307) {
                    return 9;
                }
                else if (xm > 150 + 2 * (200 + 62) && xm < 150 + 3 * (200) + 2 * 62 && ym > 150 && ym < 150 + 307) {
                    return 16;
                }
                else if (xm > 150 && xm < WIDTH - 150 && ym > 470 && ym < 570) {
                    return -1;
                }
            }

        }

        affMenuSelectMode(modeOver, renderer, font, im_4X4Over, im_4X4Away, im_9X9Over, im_9X9Away, im_16X16Over, im_16X16Away, im_retourOver, im_retourAway);

        // on permute les deux buffers (cette fonction ne doit se faire qu'une seule fois dans la boucle)
        SDL_RenderPresent(renderer);
    }
}

void affMenuSelectDim(int ModeOver, SDL_Renderer* renderer, TTF_Font* font, Image& im_4X4Over, Image& im_4X4Away, Image& im_9X9Over, Image& im_9X9Away, Image& im_16X16Over, Image& im_16X16Away, Image& im_retourOver, Image& im_retourAway){
    //Remplir l'�cran de blanc
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    SDL_Color couleur = { 0, 0, 0 };
    SDL_Surface* texte = nullptr;
    SDL_Rect position;
    SDL_Texture* texte_texture = NULL;    //Create Texture pointer

    const unsigned int largeur_tuile_mode = 200;
    const unsigned int hauteur_tuile_mode = 200;
    char Titre[80] = "Selection de la dimension de la grille";
    texte = TTF_RenderText_Blended(font, Titre, couleur);
    texte_texture = SDL_CreateTextureFromSurface(renderer, texte);
    SDL_FreeSurface(texte);



    im_4X4Away.draw(renderer, 150, 150, largeur_tuile_mode, hauteur_tuile_mode);
    im_9X9Away.draw(renderer, 150 + largeur_tuile_mode + 62, 150, largeur_tuile_mode, hauteur_tuile_mode);
    im_16X16Away.draw(renderer, 150 + 2 * (largeur_tuile_mode + 62), 150, largeur_tuile_mode, hauteur_tuile_mode);
    im_retourAway.draw(renderer, 150, 470, 3 * largeur_tuile_mode + 2 * 62, (1 / 9.23) * (3 * largeur_tuile_mode + 2 * 62));

    position.w = 700;
    position.h = 100;
    position.x = WIDTH - position.w - (WIDTH - position.w) / 2;
    position.y = 10;
    if (ModeOver == 1) {
        im_4X4Over.draw(renderer, 150, 150, largeur_tuile_mode, hauteur_tuile_mode);

    }
    else  if (ModeOver == 2) {
        im_9X9Over.draw(renderer, 150 + largeur_tuile_mode + 62, 150, largeur_tuile_mode, hauteur_tuile_mode);

    }
    else if (ModeOver == 3) {
        im_16X16Over.draw(renderer, 150 + 2 * (largeur_tuile_mode + 62), 150, largeur_tuile_mode, hauteur_tuile_mode);

    }
    else if (ModeOver == 4) {
        im_retourOver.draw(renderer, 150, 470, 3 * largeur_tuile_mode + 2 * 62, (1 / 9.23) * (3 * largeur_tuile_mode + 2 * 62));

    }

    int ok = SDL_RenderCopy(renderer, texte_texture, NULL, &position);
    SDL_DestroyTexture(texte_texture);
}
