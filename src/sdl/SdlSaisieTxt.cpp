#include "SdlSaisieTxt.h"

#include <iostream>
#include <algorithm>  //pour la fonciton max(a, b)

#pragma warning(disable : 4996)

SaisieTextPopUp::SaisieTextPopUp(TTF_Font *font_)
{
    texteDeFond = "";
    nomZoneTexte = "";
    textePreSaisie = "";
    hauteur = 0;
    largeur = 0;
    //Initialisation de la sdl : 
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    if (TTF_Init() != 0) {
        cout << "Erreur lors de l'initialisation de la SDL_ttf : " << SDL_GetError() << endl;
        SDL_Quit();
        exit(1);
    }





    //creation de la police.
   //font_menu = TTF_OpenFont("data/fonts/BungeeShade-Regular.ttf", 120);
    font = font_;

    font_color.r = 255;
    font_color.g = 85;
    font_color.b = 0;
    font_color.a = 0;
}

SaisieTextPopUp::SaisieTextPopUp(TTF_Font* font_, const int& largeur_, const int& hauteur_)
{
    texteDeFond = "";
    nomZoneTexte = "";
    textePreSaisie = "";
    hauteur = hauteur_;
    largeur = largeur_;
    //Initialisation de la sdl : 
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    if (TTF_Init() != 0) {
        cout << "Erreur lors de l'initialisation de la SDL_ttf : " << SDL_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

 

   

    //creation de la police.
    font = font_;

    font_color.r = 255;
    font_color.g = 85;
    font_color.b = 0;
    font_color.a = 0;
    
}

SaisieTextPopUp::~SaisieTextPopUp()
{
    //TTF_CloseFont(font);
    //TTF_Quit();
    //SDL_Quit();
}

string SaisieTextPopUp::getTexteSaisie(const int& largeur_, const int& hauteur_, const string& nomZoneTexte_, const string& textePreSaisie_,const string& texteDeFond_, const bool& requis)
{

    largeur = largeur_;
    hauteur = hauteur_;
    nomZoneTexte = nomZoneTexte_;
    texteDeFond = texteDeFond_;
    textePreSaisie = textePreSaisie_;
    return getTexteSaisie(requis);
}

string SaisieTextPopUp::getTexteSaisie(const bool& requis)
{
    texteSaisie = textePreSaisie;
    char message[200];

    //creation de la fenetre : 
    window = SDL_CreateWindow("Saisie de texte !", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, largeur, hauteur, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
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

    bool selectRunning = true;
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    bool invalidInput = false;
    do {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderClear(renderer);
            //------------------------------------------------------------------------------------------------------------Affichage
           
            //creation de la boite qui contient le texte
            SDL_Rect rectSaisie;
            rectSaisie.x = largeur * 2 / 100;
            rectSaisie.y = hauteur * 40 / 100;
            rectSaisie.w = largeur * 96 / 100;
            rectSaisie.h = hauteur * 35 / 100;
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            if (invalidInput) {
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                SDL_RenderDrawRect(renderer, &rectSaisie);
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            }
            else {
                SDL_RenderDrawRect(renderer, &rectSaisie);
            }
           


            //affichage du texte deja saisie ou du texte de preSaisie;
            SDL_Color couleur = { 0, 0, 0 };
            SDL_Surface* texte = nullptr;
            SDL_Rect position;
            SDL_Texture* texte_texture = NULL;    //Create Texture pointer
            if (texteSaisie == "") {
                strcpy(message, texteDeFond.c_str());
                position.h = rectSaisie.h;
                position.w = position.h * texteDeFond.length();
                position.x = rectSaisie.x;
                position.y = rectSaisie.y;
                if (position.w > rectSaisie.w) {
                    position.w = rectSaisie.w;
                    position.h = position.w / texteDeFond.length();
                }
                couleur.a = 50;

            }
            else {
                strcpy(message, texteSaisie.c_str());
                position.h = rectSaisie.h;
                position.w = position.h * texteSaisie.length();
                position.x = rectSaisie.x;
                position.y = rectSaisie.y;
                if (position.w > rectSaisie.w) {
                    position.w = rectSaisie.w;
                    position.h = position.w / texteSaisie.length();
                }
            }
            texte = TTF_RenderText_Blended(font, message, couleur);
            texte_texture = SDL_CreateTextureFromSurface(renderer, texte);
            SDL_FreeSurface(texte);
            SDL_RenderCopy(renderer, texte_texture, NULL, &position);
            SDL_DestroyTexture(texte_texture);
            couleur.a = 255;

            //affichage du nom de la boite de saisie

            strcpy(message, nomZoneTexte.c_str());
            position.h = rectSaisie.h;
            if (position.h * nomZoneTexte.length()*60/100   <= rectSaisie.w) {
                position.w = position.h * nomZoneTexte.length()*60/100;
            }
            else {
                position.w = rectSaisie.w;
            }
            position.x = rectSaisie.x;
            position.y = rectSaisie.y - position.h;
            texte = TTF_RenderText_Blended(font, message, couleur);
            texte_texture = SDL_CreateTextureFromSurface(renderer, texte);
            SDL_FreeSurface(texte);
            SDL_RenderCopy(renderer, texte_texture, NULL, &position);
            SDL_DestroyTexture(texte_texture);

        //------------------------------------------------------------------------------------------------------------gestion events
        while (SDL_PollEvent(&event))
        {

            SDL_GetWindowSize(window, &largeur, &hauteur);
            
            if (event.type == SDL_QUIT) { 
                selectRunning = false;
            }
            if (event.type == SDL_KEYDOWN)
            {

                if (event.key.keysym.sym == SDLK_BACKSPACE) {
                    if(texteSaisie.length() > 0)
                       texteSaisie.pop_back();
                }else if(event.key.keysym.sym == SDLK_SPACE) {
                   
                }
                else if (event.key.keysym.sym == SDLK_RETURN) {
                    if (!requis) {
                        selectRunning = false;
                    }
                    else {
                        if (texteSaisie == "") {
                            invalidInput = true;
                        }
                        else {
                            selectRunning = false;

                        }
                    }
                }
                else{
                    invalidInput = false;
                    texteSaisie += event.key.keysym.sym;                  
                }
                
            }
        }
        SDL_RenderPresent(renderer);

    
    
    
    } while (selectRunning);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    return texteSaisie;
}
