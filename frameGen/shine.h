#pragma once

#include "frameGenerator.h"
#include <SDL2/SDL.h>
#include <SDL_ttf.h>

//This will be the header class for my shine sprite

class ShineSprite {
  public:
    ShineSprite(SDL_Renderer* r) : renderer(r), bgColor({255, 255, 255, 255}) {};
    void makeTriangle(SDL_Point edge, int size);
    void makeBody(SDL_Point center, int size);
    void makeCrown(SDL_Point crown, int size);
    void makeEye(SDL_Point center, int size);
    void makeBackground(SDL_Color color);
  private:
    SDL_Renderer *renderer;
    SDL_Color bgColor;
    void colorBack();
    void randomClouds();
};
