#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <unistd.h>
#define HEIGHT 600
#define WIDTH 600
#define NCIRC 1
#define BARL 200
#define BARW 10
struct circle {
  int x;
  int y;
  int r;
  float vx;
  float vy;
  float d;
};
int player = HEIGHT / 2;
struct circle circles[NCIRC] = {{300, 200, 10, 3, 2.3, 0.8}};
void drawcircle(SDL_Renderer *render, int x_centre, int y_centre,
                int r) { // code taken from GFG Midpoint cirle algorithm
  // SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
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
void drawbar(SDL_Renderer *render, int y) {
  // SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
  SDL_Rect l = {0, player, BARW, BARL};
  SDL_RenderFillRect(render, &l);
  SDL_Rect r = {WIDTH - BARW, y - BARL / 2, BARW, BARL};
  SDL_RenderFillRect(render, &r);
}
void draw(SDL_Renderer *r) {
  for (int i = 0; i < NCIRC; i++) {
    // circles[i].vx *= 1.01f;
    // circles[i].vy *= 1.01f;
    SDL_SetRenderDrawColor(r, 255, 255, 255, 255);
    circles[i].y += circles[i].vy;
    circles[i].x += circles[i].vx;
    drawcircle(r, circles[i].x, circles[i].y, circles[i].r);
    drawbar(r, circles[i].y);
    if (circles[i].y >= HEIGHT) {
      circles[i].y = HEIGHT - circles[i].r;
      circles[i].vy = -circles[i].vy;
    } else if (circles[i].y <= 0) {
      circles[i].y = circles[i].r;
      circles[i].vy = -circles[i].vy;
    }
    if (circles[i].x >= WIDTH - BARW) {
      circles[i].x = WIDTH - circles[i].r;
      circles[i].vx = -circles[i].vx;
      // circles[i].vx *= 1.05f;
    } else if (circles[i].x <= 0 + BARW) {
      if (circles[i].y <= player + BARL && circles[i].y >= player) {
        circles[i].x = circles[i].r;
        circles[i].vx = -circles[i].vx;
        // circles[i].vy *= 1.05f;
      } else {
        SDL_SetRenderDrawColor(r, 0, 0, 0, 255); // set color black
        SDL_RenderClear(r);
        SDL_SetRenderDrawColor(r, 255, 0, 0, 255);
        drawcircle(r, circles[i].x, circles[i].y, circles[i].r);
        SDL_SetRenderDrawColor(r, 255, 255, 255, 255);
        drawbar(r, circles[i].y);
        SDL_RenderPresent(r);
        usleep(1000 * 1000);
        exit(0);
        SDL_SetRenderDrawColor(r, 0, 255, 0, 255); // set color black
        SDL_RenderClear(r);
      }
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
    if (e.type == SDL_QUIT) {
      break;
    } else if (e.type == SDL_KEYDOWN) {
      SDL_Keycode key = e.key.keysym.sym;
      // printf("%d\n", key);
      if (key == 119 && player > 1) {
        player -= 10;
      } else if (key == 115 && player + BARL < HEIGHT - 2) {
        player += 10;
      }
    }
    SDL_SetRenderDrawColor(r, 0, 0, 0, 255); // set color black
    SDL_RenderClear(r);
    draw(r);
    SDL_RenderPresent(r);
    usleep(1000 * 10);
  }
}
