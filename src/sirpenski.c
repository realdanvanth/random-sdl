#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#define WIDTH 1920
#define HEIGHT 1080
double pointx;
double pointy;
int vertex[3][2] = {{0, 1079}, {1919, 1079}, {960, 0}};
void plot(SDL_Renderer *render) {
  SDL_SetRenderDrawColor(render, pointx / pointy, 255, pointx, 0);
  SDL_RenderDrawPoint(render, pointx, pointy);
  int r = rand() % 3;
  pointx = (vertex[r][0] + pointx) / 2;
  pointy = (vertex[r][1] + pointy) / 2;
}
int main() {
  SDL_Init(SDL_INIT_VIDEO);
  SDL_Window *w = SDL_CreateWindow("", 0, 0, WIDTH, HEIGHT, 0);
  SDL_Renderer *r = SDL_CreateRenderer(w, -1, 0);
  SDL_Event e;
  srand(time(NULL));
  SDL_SetRenderDrawColor(r, 0, 0, 0, 255); // set color black
  SDL_RenderClear(r);
  SDL_RenderPresent(r);
  for (int i = 0; i < 100000; i++)
    plot(r);
  SDL_RenderPresent(r);
  while (e.type != SDL_QUIT) {
    SDL_PollEvent(&e);
    // SDL_SetRenderDrawColor(r, 0, 0, 0, 255); // set color black
    // SDL_RenderClear(r);
    plot(r);
    // SDL_RenderPresent(r);
    usleep(1000 * 2);
  }
}
