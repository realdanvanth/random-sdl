#include <SDL2/SDL.h>
#include <unistd.h>
#define HEIGHT 640
#define WIDTH 480
#define NCIRC 1
struct circle {
  int x;
  int y;
  int r;
  float vx;
  float vy;
  float d;
};
struct circle circles[NCIRC] = {{300, 200, 10, 2.39, 1.5, 0.99}};
void drawcircle(SDL_Renderer *render, int x_centre, int y_centre,
                int r) { // code taken from GFG Midpoint cirle algorithm
  SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
  int x = r, y = 0;
  SDL_RenderDrawPoint(render, x + x_centre, y + y_centre);
  SDL_RenderDrawLine(render, x_centre - x, y_centre, x + x_centre, y_centre);
  int P = 1 - r;
  while (x > y) {
    y++;
    if (P <= 0)
      P = P + 2 * y + 1;
    else {
      x--;
      P = P + 2 * y - 2 * x + 1;
    }

    if (x < y)
      break;

    SDL_RenderDrawLine(render, x + x_centre, y + y_centre, -x + x_centre,
                       y + y_centre);
    SDL_RenderDrawLine(render, x + x_centre, -y + y_centre, -x + x_centre,
                       -y + y_centre);
    if (x != y) {
      SDL_RenderDrawLine(render, y + x_centre, x + y_centre, -y + x_centre,
                         x + y_centre);
      SDL_RenderDrawLine(render, y + x_centre, -x + y_centre, -y + x_centre,
                         -x + y_centre);
    }
  }
}
void draw(SDL_Renderer *r) {
  for (int i = 0; i < NCIRC; i++) {
    // circles[i].vx += 0.3f;
    // circles[i].vy += 0.3f;
    circles[i].y += circles[i].vy;
    circles[i].x += circles[i].vx;
    drawcircle(r, circles[i].x, circles[i].y, circles[i].r);
    if (circles[i].y + circles[i].r >= HEIGHT) {
      circles[i].y = HEIGHT - circles[i].r;
      circles[i].vy = -circles[i].d * circles[i].vy;
    } else if (circles[i].y + circles[i].r <= 0) {
      circles[i].y = circles[i].r;
      circles[i].vy = -circles[i].d * circles[i].vy;
    }
    if (circles[i].x + circles[i].r >= WIDTH) {
      circles[i].x = WIDTH - circles[i].r;
      circles[i].vx = -circles[i].d * circles[i].vx;
    } else if (circles[i].x <= 0) {
      circles[i].x = circles[i].r;
      circles[i].vx = -circles[i].d * circles[i].vx;
    }
  }
}
int main() {
  SDL_Init(SDL_INIT_VIDEO);
  SDL_Window *w = SDL_CreateWindow("", 0, 0, WIDTH, HEIGHT, 0);
  SDL_Renderer *r = SDL_CreateRenderer(w, -1, 0);
  SDL_Event e;
  while (e.type != SDL_QUIT) {
    SDL_PollEvent(&e);
    SDL_SetRenderDrawColor(r, 0, 0, 0, 255); // set color black
    SDL_RenderClear(r);
    draw(r);
    SDL_RenderPresent(r);
    usleep(1000 * 10);
  }
}
