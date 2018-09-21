#include <iostream>
#include <SDL2/SDL.h>
#include <SDL_ttf.h>
#include "frameGenerator.h"
#include "shine.h"

const std::string TITLE = "Brett Probert's Shine Sprite";
const std::string NAME = "bmprobe";

const int WIDTH = 650;
const int HEIGHT = 650;

void writeName(SDL_Renderer* renderer) {
  TTF_Init();
  TTF_Font* font = TTF_OpenFont("fonts/ikarus.ttf", 24);
  if (font == NULL) {
    throw std::string("error: font not found");
  }
  SDL_Color textColor = {100, 0, 0, 1};
  SDL_Surface* surface =
    TTF_RenderText_Solid(font, TITLE.c_str(), textColor);
  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

  int textWidth = surface->w;
  int textHeight = surface->h;
  SDL_FreeSurface(surface);
  SDL_Rect dst = {20, HEIGHT-40, textWidth, textHeight};

  SDL_RenderCopy(renderer, texture, NULL, &dst);
  SDL_DestroyTexture(texture);
}


int main(void) {
  try {
    if ( SDL_Init(SDL_INIT_VIDEO) != 0 ) {
      std::cout << "Failed to initialize SDL2" << std::endl;
      return EXIT_FAILURE;
    }
    SDL_Window* window = SDL_CreateWindow(
      TITLE.c_str(),
      SDL_WINDOWPOS_CENTERED,
      SDL_WINDOWPOS_CENTERED,
      WIDTH,
      HEIGHT,
      SDL_WINDOW_SHOWN
    );
    // Apparently we can't use hardware acceleration with
    // SDL_GetWindowSurface
    SDL_Renderer* renderer = SDL_CreateRenderer(
      window, -1, SDL_RENDERER_SOFTWARE
    );
    //Temporary line (this one and the one below)
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    SDL_SetRenderDrawColor( renderer, 135, 206, 235, 255 );
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    //My code
    SDL_Point center = {325, 325};
    ShineSprite shineMaker(renderer);

    shineMaker.makeShine(center);

    writeName(renderer);
    SDL_RenderPresent(renderer);
    FrameGenerator frameGen(renderer, window, WIDTH, HEIGHT, NAME);
    frameGen.makeFrame();

    SDL_Event event;
    const Uint8* keystate;
    while ( true ) {
      keystate = SDL_GetKeyboardState(0);
      if (keystate[SDL_SCANCODE_ESCAPE]) { break; }
      if (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
          break;
        }
      }
  }
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  }
  catch (const std::string& msg) { std::cout << msg << std::endl; }
  catch (...) {
    std::cout << "Oops, someone threw an exception!" << std::endl;
  }
  return EXIT_SUCCESS;
}
