#include "Image.h"

#include <iostream>
using namespace std;

// ============= CLASS IMAGE =============== //

Image::Image():name("test") {
    surface = nullptr;
    texture = nullptr;
    has_changed = false;

}

Image::~Image()
{
    SDL_DestroyTexture(this->texture);
    SDL_FreeSurface(this->surface);
    cout <<" deleted: "<< name << endl;
}


void Image::loadFromFile(const char* filename, SDL_Renderer* renderer) {
    strcpy(name, filename);
    surface = IMG_Load(filename);
    if (surface == nullptr) {
        string nfn = string("../") + filename;
        cout << "Error: cannot load " << filename << ". Trying " << nfn << endl;
        surface = IMG_Load(nfn.c_str());
        if (surface == nullptr) {
            nfn = string("../") + nfn;
            surface = IMG_Load(nfn.c_str());
        }
    }
    if (surface == nullptr) {
        cout << "Error: cannot load " << filename << endl;
        SDL_Quit();
        exit(1);
    }

    SDL_Surface* surfaceCorrectPixelFormat = SDL_ConvertSurfaceFormat(surface, SDL_PIXELFORMAT_ARGB8888, 0);
    SDL_FreeSurface(surface);
    surface = surfaceCorrectPixelFormat;

    texture = SDL_CreateTextureFromSurface(renderer, surfaceCorrectPixelFormat);
    if (texture == nullptr) {
        cout << "Error: problem to create the texture of " << filename << endl;
        SDL_Quit();
        exit(1);
    }
}

void Image::loadFromCurrentSurface(SDL_Renderer* renderer) {
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == nullptr) {
        cout << "Error: problem to create the texture from surface " << endl;
        SDL_Quit();
        exit(1);
    }
}

void Image::draw(SDL_Renderer* renderer, int x, int y, int w, int h) {
    int ok;
    SDL_Rect r;
    r.x = x;
    r.y = y;
    r.w = (w < 0) ? surface->w : w;
    r.h = (h < 0) ? surface->h : h;

    if (has_changed) {
        ok = SDL_UpdateTexture(texture, nullptr, surface->pixels, surface->pitch);
        assert(ok == 0);
        has_changed = false;
    }

    ok = SDL_RenderCopy(renderer, texture, nullptr, &r);
    assert(ok == 0);
}

SDL_Texture* Image::getTexture() const { return texture; }

void Image::setSurface(SDL_Surface* surf) { surface = surf; }