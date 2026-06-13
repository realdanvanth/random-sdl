#include <SDL2/SDL.h>
#include <complex.h>
#include <unistd.h>
#define HEIGHT 400
#define WIDTH 600
#define HOFF HEIGHT / 2
#define WOFF WIDTH / 2
#define N 255 * 3
void calculatePoint(SDL_Renderer *r, int x, int y) {
  // min max scaling formula
  double x1 = -2.0 + (x + WOFF * 1.0) / 200.0;
  double y1 = y / (HOFF * 1.0);
  double zx = 0;
  double complex zy = 0;
  int i = 0;
  while (i < N && abs(zx * zx + zy * zy) < 4) {
    double complex temp = zx * zx - zy * zy + x1;
    zy = abs(2 * zx * zy) + y1; // abs returns the absolute value
    zx = temp;
    i++;
  }
  if (i >= N) {
    // SDL_SetRenderDrawColor(r, 0, 0, 0, 255);
    SDL_SetRenderDrawColor(r, 255, 255, 255, 255);
    SDL_RenderDrawPoint(r, x + WOFF, y + HOFF);
  } else {
    // SDL_SetRenderDrawColor(r, 255, 255, 255, 255);
    SDL_SetRenderDrawColor(r, 0, 0, 0, 255);
    SDL_RenderDrawPoint(r, x + WOFF, y + HOFF);
  }
  return;
}
void draw(SDL_Renderer *r) {
  SDL_SetRenderDrawColor(r, 255, 255, 255, 255);
  for (int i = HEIGHT / 2; i >= -HEIGHT / 2; i--) {
    for (int j = -WIDTH / 2; j <= WIDTH / 2; j++) {
      calculatePoint(r, j, i);
    }
  }
}
int main() {
  SDL_Init(SDL_INIT_VIDEO);
  SDL_Window *w = SDL_CreateWindow("", 0, 0, WIDTH, HEIGHT, 0);
  SDL_Renderer *r = SDL_CreateRenderer(w, -1, 0);
  SDL_Event e;
  SDL_SetRenderDrawColor(r, 0, 0, 0, 255); // set color black
  SDL_RenderClear(r);
  draw(r);
  SDL_RenderPresent(r);
  while (e.type != SDL_QUIT) {
    SDL_PollEvent(&e);
    usleep(1000 * 2);
  }
}
