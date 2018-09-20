#include "shine.h"
//This will be the implementation of the shine class

void ShineSprite::makeTriangle(SDL_Point edge, int size) {
  SDL_RenderDrawLine(renderer, edge.x, edge.y,
    edge.x + 50,
    edge.y + 50);
  size = 1;
}
