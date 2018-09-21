#include "shine.h"

void ShineSprite::makeShine(SDL_Point center) {
  std::cout << "Making Shine Sprite at: "
            << center << std::endl;

  makePoint({center.x - 50, center.y + 190},
            {center.x + 50, center.y + 190},
            {center.x, center.y + 275});
  makePoint({center.x - 50, center.y - 190},
            {center.x + 50, center.y - 190},
            {center.x, center.y - 275});
  makePoint({center.x + 190, center.y - 50},
            {center.x + 275, center.y},
            {center.x + 190, center.y + 50});
  makePoint({center.x - 275, center.y},
            {center.x - 190, center.y - 50},
            {center.x - 190, center.y + 50});
  makePoint({center.x + 100, center.y + 160},
            {center.x + 200, center.y + 200},
            {center.x + 170, center.y + 100});
  makePoint({center.x - 200, center.y - 200},
            {center.x - 100, center.y - 160},
            {center.x - 170, center.y - 100});
  makePoint({center.x - 200, center.y + 200},
            {center.x - 100, center.y + 160},
            {center.x - 170, center.y + 100});
  makePoint({center.x + 100, center.y - 160},
            {center.x + 170, center.y - 100},
            {center.x + 200, center.y - 200});

  makeBody(center);

  makeEye({center.x + 45, center.y - 10});
  makeEye({center.x - 45, center.y - 10});


  drawCircle(renderer, {center.x, center.y - 285}, 35, ShineYellow);
  drawCircle(renderer, {center.x + 210, center.y - 210}, 35, ShineYellow);
  drawCircle(renderer, {center.x - 210, center.y - 210}, 35, ShineYellow);
}

void ShineSprite::makeBody(SDL_Point center) {
  drawCircle(renderer, center, 200, ShineBlack);
  drawCircle(renderer, center, 197, ShineYellow);
  drawCircle(renderer, center, 165, ShineBlack);
  drawCircle(renderer, center, 162, ShineYellow);
}

void ShineSprite::makeEye(SDL_Point center) {
  SDL_SetRenderDrawColor(renderer, ShineBlack.r, ShineBlack.g,
                         ShineBlack.b, ShineBlack.a);
  const int height = 55;
  const int width = 25;

  for(int y=-height; y<=height; y++) {
    for(int x=-width; x<=width; x++) {
        if(x*x*height*height+y*y*width*width <=
           height*height*width*width)
          SDL_RenderDrawPoint(renderer, center.x + x, center.y + y);
    }
  }
}

void ShineSprite::makePoint(SDL_Point left, SDL_Point right,
                            SDL_Point top) {
  SDL_SetRenderDrawColor(renderer, ShineYellow.r, ShineYellow.g,
                         ShineYellow.b, ShineYellow.a);
  double lx = static_cast<double>(left.x);
  double ly = static_cast<double>(left.y);
  double rx = static_cast<double>(right.x);
  double ry = static_cast<double>(right.y);
  double tx = static_cast<double>(top.x);
  double ty = static_cast<double>(top.y);

  double slope = (ly - ry) / (lx - rx);
  int x = left.x;
  double y = ly;
  while(x != right.x) {
    SDL_RenderDrawLine(renderer, x, static_cast<int>(y), top.x, top.y);
    (x < right.x) ? x++ : x--;
    y += slope;
  }

  slope = (ty - ry) / (tx - rx);
  x = top.x;
  y = ry;
  while(x != top.x) {
    SDL_RenderDrawLine(renderer, x, static_cast<int>(y), left.x, left.y);
    (x < top.x) ? x++ : x--;
    y += slope;
  }

  slope = (ly - ty) / (lx - tx);
  x = left.x;
  y = ly;
  while(x != top.x) {
    SDL_RenderDrawLine(renderer, x, static_cast<int>(y), right.x, right.y);
    (x < top.x) ? x++ : x--;
    y += slope;
  }
}

// End of class methods
std::ostream& operator<<(std::ostream& out, const SDL_Point& p) {
  out << "{ " << p.x << ", " << p.y << " }";
  return out;
}

void drawCircle(SDL_Renderer* renderer,
  SDL_Point center, int radius, SDL_Color color) {
  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
  for (int w = 0; w < radius * 2; w++) {
    for (int h = 0; h < radius * 2; h++) {
      int dx = radius - w; // horizontal offset
      int dy = radius - h; // vertical offset
      if ((dx*dx + dy*dy) <= (radius * radius)) {
        SDL_RenderDrawPoint(renderer, center.x + dx, center.y + dy);
      }
    }
  }
}
