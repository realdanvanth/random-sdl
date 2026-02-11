#include <SDL2/SDL.h>
#include <complex.h>
#include <unistd.h>
#define HEIGHT 400
#define WIDTH 600
#define N 255
double startx = -2;
double endx = 1;
double starty = 1;
double endy = -1;
double zoom = 1;
// double w = (startx - endx) / zoom;
// double h = (starty - endy) / zoom;
void calculatePoint(SDL_Renderer *r, int x, int y) {
  // min max scaling formula
  double w = (endx - startx);
  double h = (endy - starty);
  double x1 = startx + ((x)*w) / (WIDTH - 1);
  double y1 = starty + ((y)*h) / (HEIGHT - 1);
  double complex c = x1 + I * y1;
  double complex z = 0;
  int i = 0;
  while (i < N && abs(z) < 2) {
    z = z * z + c;
    i++;
  }
  if (i >= N) {
    // SDL_SetRenderDrawColor(r, 0, 0, 0, 255);
    SDL_SetRenderDrawColor(r, 255, 255, 255, 255);
    SDL_RenderDrawPoint(r, x, y);
  } else {
    c = c * c;
    z = z * z;
    // SDL_SetRenderDrawColor(r, 255, 255, 255, 255);
    SDL_SetRenderDrawColor(r, 0, 0, 0, 255);
    SDL_RenderDrawPoint(r, x, y);
  }
  return;
}
void draw(SDL_Renderer *r) {
  SDL_SetRenderDrawColor(r, 255, 255, 255, 255);
  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
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
