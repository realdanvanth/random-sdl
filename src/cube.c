#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#define HEIGHT 600
#define WIDTH 600
#define L 100
struct point {
  float x;
  float y;
  float z;
};
void drawLine(SDL_Renderer *r, struct point pointA, struct point pointB) {
  float x1 = pointA.x / (1 - pointA.z) + WIDTH / 2;
  float y1 = pointA.y / (1 - pointA.z) + HEIGHT / 2;
  float x2 = pointB.x / (1 - pointB.z) + WIDTH / 2;
  float y2 = pointB.y / (1 - pointB.z) + HEIGHT / 2;
  SDL_SetRenderDrawColor(r, 255, 255, 255, 255);
  printf("%f %f %f %f/n", x1, y1, x2, y2);
  SDL_RenderDrawLine(r, x1, y1, x2, y2);
}
void drawCube(SDL_Renderer *r) {
  drawLine(r, (struct point){0, 0, 0}, (struct point){0, L, 0})
      drawLine(r, (struct point){0, 0, 0}, (struct point){0, L, 0})
}
int main() {
  SDL_Init(SDL_INIT_VIDEO);
  SDL_Window *w = SDL_CreateWindow("", 0, 0, 600, 600, 0);
  SDL_Renderer *r = SDL_CreateRenderer(w, -1, 0);
  SDL_SetRenderDrawColor(r, 0, 0, 0, 255);
  SDL_RenderClear(r);
  drawCube(r, (struct point){0, 0, 0}, (struct point){100, 100, 0});
  SDL_RenderPresent(r);
  SDL_Event e;
  while (e.type != SDL_QUIT) {
    SDL_PollEvent(&e);
  }
}
