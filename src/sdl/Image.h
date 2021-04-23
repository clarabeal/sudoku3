#ifndef _SDL_Image_
#define _SDL_Image_

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

#include <string>

//! \brief Pour gerer une image avec SDL2
class Image {

public:
    Image();
    ~Image();

    void loadFromFile(const char* filename, SDL_Renderer* renderer);
    void loadFromCurrentSurface(SDL_Renderer* renderer);
    void draw(SDL_Renderer* renderer, int x, int y, int w = -1, int h = -1);
    SDL_Texture* getTexture() const;
    void setSurface(SDL_Surface* surf);

private:

    SDL_Surface* surface;
    SDL_Texture* texture;
    bool has_changed;
    char name[100];

};
#endif