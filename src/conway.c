#include <SDL2/SDL.h>
#include <stdlib.h>
#include <time.h>
#define HEIGHT 640
#define WIDTH 480
int grid[HEIGHT][WIDTH] = {0};
int pos(int pos, int xy) {
  if (xy == 0) {
    return (pos >= HEIGHT - 1) ? 0 : pos + 1;
  } else {
    return (pos >= WIDTH - 1) ? 0 : pos + 1;
  }
}
int neg(int pos, int xy) {
  if (xy == 0) {
    return (pos <= 0) ? HEIGHT - 1 : pos - 1;
  } else {
    return (pos <= 0) ? WIDTH - 1 : pos - 1;
  }
}
void init() {
  srand(time(NULL));
  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      grid[i][j] = rand() % 4;
      if (grid[i][j] == 3) {
        grid[i][j] = 1;
      } else {
        grid[i][j] = 0;
      }
    }
  }
}
void life() {
  int newgrid[HEIGHT][WIDTH] = {0};
  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      int sum = grid[pos(i, 0)][pos(j, 1)] + grid[pos(i, 0)][neg(j, 1)] +
                grid[neg(i, 0)][pos(j, 1)] + grid[neg(i, 0)][neg(j, 1)] +
                grid[pos(i, 0)][j] + grid[i][pos(j, 1)] + grid[neg(i, 0)][j] +
                grid[i][neg(j, 1)];
      if (grid[i][j] == 1) {
        if (sum < 2) {
          newgrid[i][j] = 0;
        } else if (sum > 3) {
          newgrid[i][j] = 0;
        } else {
          newgrid[i][j] = 1;
        }
      } else if (sum == 3) {
        newgrid[i][j] = 1;
      }
    }
  }
  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      grid[i][j] = newgrid[i][j];
    }
  }
}
void display(SDL_Renderer *r) {
  SDL_SetRenderDrawColor(r, 255, 255, 255, 255);
  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      if (grid[i][j] == 1) {
        SDL_RenderDrawPoint(r, i, j);
      }
    }
  }
}
int main() {
  SDL_Init(SDL_INIT_VIDEO);
  SDL_Window *w = SDL_CreateWindow("", 0, 0, 640, 480, 0);
  SDL_Renderer *r = SDL_CreateRenderer(w, -1, 0);
  SDL_Event e;
  init();
  while (e.type != SDL_QUIT) {
    SDL_PollEvent(&e);
    if (e.type == SDL_KEYDOWN)
      printf("Key: %d\n", e.key.keysym.sym);

    SDL_SetRenderDrawColor(r, 0, 0, 0, 255); // set color black
    SDL_RenderClear(r);
    // SDL_SetRenderDrawColor(r, 255, 255, 255, 255); // set color white
    life();
    display(r);
    SDL_RenderPresent(r);
  }
}
