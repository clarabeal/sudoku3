#include "sdlClassique.h"
#include <iostream>
using namespace std;

#define WIDTH 1280
#define HEIGHT 720

float temps () {
    return float(SDL_GetTicks()) / CLOCKS_PER_SEC;  // conversion des ms en secondes en divisant par 1000
}

// ============= CLASS IMAGE =============== //

Image::Image () {
    surface = NULL;
    texture = NULL;
    has_changed = false;
}

void Image::loadFromFile (const char* filename, SDL_Renderer * renderer) {
    surface = IMG_Load(filename);
    if (surface == NULL) {
        string nfn = string("../") + filename;
        cout << "Error: cannot load "<< filename <<". Trying "<<nfn<<endl;
        surface = IMG_Load(nfn.c_str());
        if (surface == NULL) {
            nfn = string("../") + nfn;
            surface = IMG_Load(nfn.c_str());
        }
    }
    if (surface == NULL) {
        cout<<"Error: cannot load "<< filename <<endl;
        SDL_Quit();
        exit(1);
    }

    SDL_Surface * surfaceCorrectPixelFormat = SDL_ConvertSurfaceFormat(surface,SDL_PIXELFORMAT_ARGB8888,0);
    SDL_FreeSurface(surface);
    surface = surfaceCorrectPixelFormat;

    texture = SDL_CreateTextureFromSurface(renderer,surfaceCorrectPixelFormat);
    if (texture == NULL) {
        cout << "Error: problem to create the texture of "<< filename<< endl;
        SDL_Quit();
        exit(1);
    }
}

void Image::loadFromCurrentSurface (SDL_Renderer * renderer) {
    texture = SDL_CreateTextureFromSurface(renderer,surface);
    if (texture == NULL) {
        cout << "Error: problem to create the texture from surface " << endl;
        SDL_Quit();
        exit(1);
    }
}

void Image::draw (SDL_Renderer * renderer, int x, int y, int w, int h) {
    int ok;
    SDL_Rect r;
    r.x = x;
    r.y = y;
    r.w = (w<0)?surface->w:w;
    r.h = (h<0)?surface->h:h;

    if (has_changed) {
        ok = SDL_UpdateTexture(texture,NULL,surface->pixels,surface->pitch);
        assert(ok == 0);
        has_changed = false;
    }

    ok = SDL_RenderCopy(renderer,texture,NULL,&r);
    assert(ok == 0);
}

SDL_Texture * Image::getTexture() const {return texture;}

void Image::setSurface(SDL_Surface * surf) {surface = surf;}

// ============= CLASS SDLJEU =============== //

sdlJeu::sdlJeu(unsigned char d) : jeu(d) {

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
    //font = TTF_OpenFont("data/fonts/BungeeShade-Regular.ttf", 12);
    font = TTF_OpenFont("data/fonts/arial.ttf", 12);

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

    //creation des images :
    if (d == 4) {
        im_grille.loadFromFile("data/assets/4x4color.jpg", renderer);
    }
    else if (d == 9) {
        im_grille.loadFromFile("data/assets/9x9color.jpg", renderer);
    }
    else if (d == 16) {
        im_grille.loadFromFile("data/assets/16x16color.jpg", renderer);
    }



}

sdlJeu::~sdlJeu(){

    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

}

void sdlJeu::sdlAff(){

    //Remplir l'écran de blanc
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    // Affiche la grille vide
    sdlAffGrille(jeu.grilleJeu, 10, 80, 600, 600);
    sdlAffChrono(620, 80, 400, 100);

}

void sdlJeu::sdlAffGrille(Grille& grille, int x, int y, int largeur, int hauteur) {
    im_grille.draw(renderer, x, y, largeur, hauteur);
    SDL_Color couleur = { 0, 0, 0 };
    SDL_Surface* texte = nullptr;
    SDL_Rect position;
    SDL_Texture* texte_texture = NULL;    //Create Texture pointer

    int dimGrille = (int)grille.dim;
    int largeurCase = largeur / dimGrille;
    int hauteurCase = hauteur / dimGrille;
    char* buffConversion = new char[3];
    for (int l = 0; l < dimGrille; l++) {
        for (int c = 0; c < dimGrille; c++) {
            if (grille.grille.getCase(l, c).getVal() != 0) {
                if (grille.grille.getCase(l, c).getVal() < 10) {
                    buffConversion[0] = (int)grille.grille.getCase(l, c).getVal() + '0';
                    buffConversion[1] = '\0';
                }
                else {

                    buffConversion[0] = '1';
                    buffConversion[1] = (int)grille.grille.getCase(l, c).getVal() - 10 + '0';
                    buffConversion[2] = '\0';

                }
                
                //cout << "res: " << (int)grille.grille.getCase(l, c).getVal() << " n1: " << buffConversion[0] << " n2: " << buffConversion[1] << endl;
                texte = TTF_RenderText_Blended(font, buffConversion, couleur);
                texte_texture = SDL_CreateTextureFromSurface(renderer, texte);
                SDL_FreeSurface(texte);

                //on positionne le nombre au centre de ca case
                if (dimGrille > 9) {
                    if (grille.grille.getCase(l, c).getVal() < 10) {// si il n'y a qu'un chiffre
                        position.x = x + c * largeurCase + 4*(largeurCase / 12);
                        position.y = y + l * hauteurCase + hauteurCase / 4;
                        position.w = 5 * (float)(largeurCase / 12);
                        position.h = 3 * (float)(hauteurCase / 4);
                    }
                    else {// si il y a deux chiffres
                        position.x = x + c * largeurCase + largeurCase / 12;
                        position.y = y + l * hauteurCase + hauteurCase / 4;
                        position.w = 10 * (float)(largeurCase / 12);
                        position.h = 3 * (float)(hauteurCase / 4);
                    }
                }
                else {
                    position.x = x + c * largeurCase + largeurCase / 4;
                    position.y = y + l * hauteurCase + hauteurCase / 4;
                    position.w = 3 * (float)(largeurCase / 4);
                    position.h = 3 * (float)(hauteurCase / 4);
                }
                int ok = SDL_RenderCopy(renderer, texte_texture, NULL, &position);
                assert(ok == 0);
            }
        }
    }
    delete []buffConversion;
}

void sdlJeu::sdlAffChrono(int x, int y, int largeur, int hauteur) {
    jeu.chrono.update();// a enlever apres les test, ne doit pa être la
    SDL_Color couleur = { 0, 0, 0 };
    SDL_Surface* texte = nullptr;
    SDL_Rect position;
    SDL_Texture* texte_texture = NULL;    //Create Texture pointer
    char buffConversion[80];
    buffConversion[sprintf(buffConversion, "%luh %lum %lus %lu ms", jeu.chrono.getTimeInHours(), jeu.chrono.getTimeInMin()%60, jeu.chrono.getTimeInSec()%60, jeu.chrono.getTimeInMSec()%1000)+1] = '\0';
    texte = TTF_RenderText_Blended(font, buffConversion, couleur);
    texte_texture = SDL_CreateTextureFromSurface(renderer, texte);
    SDL_FreeSurface(texte);


    position.x = x ;
    position.y = y ;
    position.w = largeur;
    position.h = hauteur;
                
    int ok = SDL_RenderCopy(renderer, texte_texture, NULL, &position);
    assert(ok == 0);
}

void sdlJeu::sdlBoucle(){

    bool gameRunning = true;
    SDL_Event event;
    if (!jeu.initDone) {
        jeu.init();
        jeu.initDone = true;
    }
    while (gameRunning) {

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT) gameRunning = false;
            if (event.type == SDL_KEYDOWN)
            {
                switch (event.key.keysym.scancode)
                {
                    case SDL_SCANCODE_Q:
                        gameRunning = false;
                        break;
                    default:
                        break;
                }
            }
        }


        sdlAff();

        // on permute les deux buffers (cette fonction ne doit se faire qu'une seule fois dans la boucle)
        SDL_RenderPresent(renderer); 
    }
}