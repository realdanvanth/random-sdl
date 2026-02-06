#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <math.h>
#include <unistd.h>
#define HEIGHT 1080
#define WIDTH 1920
#define HOFF HEIGHT / 2
#define WOFF WIDTH / 2
#define N 3
struct body {
  float x;
  float y;
  int mass;
  float vx;
  float vy;
  float fx;
  float fy;
};
struct body bodies[N] = {
    {0, 0, 150, 0.0f, 0.0f, 0, 0},   // Sun (heavy, at center)
    {200, 0, 40, 0.0f, -1.5f, 0, 0}, // Planet
    {250, 0, 15, 0.0f, -2.2f, 0, 0}  // Moon
};
void drawcircle(SDL_Renderer *render, int x_centre, int y_centre, int r) {
  SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
  x_centre += WOFF;
  y_centre += HOFF;
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
void update(SDL_Renderer *r) {
  // DRAW BODIES
  for (int i = 0; i < N; i++) {
    drawcircle(r, bodies[i].x, bodies[i].y, bodies[i].mass);
    bodies[i].fx = 0;
    bodies[i].fy = 0;
  }
  // CALCULATE NEXT X,Y
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      if (j != i) {
        float r = sqrt(pow(bodies[j].x - bodies[i].x, 2) +
                       pow(bodies[j].y - bodies[i].y, 2));
        float force = 0.5 * (bodies[i].mass * bodies[j].mass) / pow(r, 2);
        bodies[i].fx += force * (bodies[j].x - bodies[i].x) / r;
        bodies[i].fy += force * (bodies[j].y - bodies[i].y) / r;
      }
    }
  }
  for (int i = 0; i < N; i++) {
    bodies[i].vx += bodies[i].fx / bodies[i].mass;
    bodies[i].vy += bodies[i].fy / bodies[i].mass;
    bodies[i].x += bodies[i].vx;
    bodies[i].y += bodies[i].vy;
  }
}
int main() {
  SDL_Init(SDL_INIT_VIDEO);
  SDL_Window *w = SDL_CreateWindow("", 0, 0, WIDTH, HEIGHT, 0);
  SDL_Renderer *r = SDL_CreateRenderer(w, -1, 0);
  SDL_SetRenderDrawColor(r, 0, 0, 0, 255);
  SDL_RenderClear(r);
  update(r);
  SDL_RenderPresent(r);
  SDL_Event e;
  while (e.type != SDL_QUIT) {
    SDL_PollEvent(&e);
    SDL_SetRenderDrawColor(r, 0, 0, 0, 255);
    SDL_RenderClear(r);
    update(r);
    SDL_RenderPresent(r);
    usleep(1000 * 10);
  }
}
