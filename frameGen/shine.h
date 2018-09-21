#pragma once

#include "frameGenerator.h"
#include <SDL2/SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <math.h>

const SDL_Color ShineYellow = {204, 204, 0, 255};
const SDL_Color ShineBlack = {1, 1, 1, 225};

class ShineSprite {
  public:
    ShineSprite(SDL_Renderer* r) : renderer(r) {};
    ~ShineSprite() = default;
    ShineSprite(const ShineSprite&) = delete;
    void makeShine(SDL_Point center);
    void makeRandClouds(int number);
  private:
    SDL_Renderer *renderer;
    void makeBody(SDL_Point center);
    void makeEye(SDL_Point center);
    void makePoint(SDL_Point left, SDL_Point right,
                   SDL_Point top);
};

std::ostream& operator<<(std::ostream& out, const SDL_Point& p);

void drawCircle(SDL_Renderer* renderer,
  SDL_Point center, int radius, SDL_Color color);
