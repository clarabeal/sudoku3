#ifndef _SDL_SAISIE_TEXTE_H 
#define _SDL_SAISIE_TEXTE_H

#include <string>

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

/**\brief Permet d'ouvir une fenetre permetant de saisir du texte du texte*/
class SaisieTextPopUp
{
public:
	SaisieTextPopUp(TTF_Font* font_);
	/**\brief Le pop up ferat hauteurxlargeur */
	SaisieTextPopUp(TTF_Font* font_, const int& largeur,const int& hauteur);
	~SaisieTextPopUp();
	string getTexteSaisie(const int& largeur_, const int& hauteur_, const string& nomZoneTexte_, const string& textePreSaisie_ = "", const string& texteDeFond_ = "", const bool& requis = 0);

	string getTexteSaisie(const bool& requis = 0);

	string nomZoneTexte, texteDeFond;

private:
	int largeur, hauteur;
	string texteSaisie;
	string textePreSaisie;

	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Event event;
	TTF_Font* font;
	SDL_Color font_color;

};



#endif
