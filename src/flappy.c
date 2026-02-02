#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <stdlib.h>
#include <unistd.h>
#define HEIGHT 600
#define WIDTH 600
#define NCIRC 1
#define SPACE 150
#define BARW 85
#define QMAX 6
struct circle {
  int x;
  int y;
  int r;
  float vx;
  float vy;
};
struct bars {
  int x;
  int y;
};
struct queue {
  int front;
  int end;
  int size;
  struct bars queue[QMAX];
};
struct queue bars;
struct circle flappy = {50, 300, 10, 0, 2};
void init() {
  bars.front = -1;
  bars.end = -1;
}
void delete() {
  if (bars.front == bars.end) {
    bars.front = bars.end = -1;
    return;
  }
  bars.size--;
  bars.front = (bars.front + 1) % QMAX;
}
void insert(int x, int y) {
  // printf("hellooooo\n");
  if (bars.front == -1 && bars.end == -1) {
    bars.front = 0;
    bars.end = 0;
    bars.queue[bars.front].x = x;
    bars.queue[bars.front].y = y;
  } else {
    bars.end = (bars.end + 1) % QMAX;
    bars.queue[bars.end].x = x;
    bars.queue[bars.end].y = y;
    // printf("hello\n");
  }
  bars.size++;
}
// struct bars bar[4] = {{0, 300}, {150, 250}, {300, 300}, {450, 200}};
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
void drawbar(SDL_Renderer *render) {
  SDL_SetRenderDrawColor(render, 20, 186, 43, 255);
  // SDL_Rect l = {0, player, BARW, BARL};
  // SDL_RenderFillRect(render, &l);
  if (bars.front <= bars.end)
    for (int i = bars.front; i <= bars.end; i++) {
      SDL_Rect bh = {bars.queue[i].x, 0, BARW, bars.queue[i].y};
      SDL_RenderFillRect(render, &bh);
      SDL_Rect bl = {bars.queue[i].x, bars.queue[i].y + SPACE, BARW,
                     HEIGHT - (bars.queue[i].y + SPACE)};
      SDL_RenderFillRect(render, &bl);
    }
  else {
    for (int i = bars.front; i < QMAX; i++) {
      SDL_Rect bh = {bars.queue[i].x, 0, BARW, bars.queue[i].y};
      SDL_RenderFillRect(render, &bh);
      SDL_Rect bl = {bars.queue[i].x, bars.queue[i].y + SPACE, BARW,
                     HEIGHT - (bars.queue[i].y + SPACE)};
      SDL_RenderFillRect(render, &bl);
    }
    for (int i = 0; i <= bars.end; i++) {
      SDL_Rect bh = {bars.queue[i].x, 0, BARW, bars.queue[i].y};
      SDL_RenderFillRect(render, &bh);
      SDL_Rect bl = {bars.queue[i].x, bars.queue[i].y + SPACE, BARW,
                     HEIGHT - (bars.queue[i].y + SPACE)};
      SDL_RenderFillRect(render, &bl);
    }
  }
}
void update(SDL_Renderer *r) {
  // drawcircle(r, flappy.x, flappy.y, flappy.r);
  // printf("update\n");
  drawbar(r);
  if (bars.front <= bars.end) {
    for (int i = bars.front; i <= bars.end; i++) {
      bars.queue[i].x--;
    }
  } else {
    for (int i = bars.front; i < QMAX; i++) {
      bars.queue[i].x--;
    }
    for (int i = 0; i <= bars.end; i++) {
      bars.queue[i].x--;
    }
  }
  if (bars.queue[bars.front].x + BARW <= 0) {
    delete ();
    // printf("deleted front %d end %d next %d\n", bars.front, bars.end,
    //(bars.end + 1) % QMAX);
  }
  if (bars.queue[bars.end].x + 150 < WIDTH) {
    insert(bars.queue[bars.end].x + 150, rand() % (HEIGHT - SPACE));
    // printf("front %d end %d\n", bars.front, bars.end);
    // printf("inserted front %d end %d next %d\n", bars.front, bars.end,
    //(bars.end + 1) % QMAX);
  }
  // printf("front %d end %d", bars.front, bars.end);
}
int main() {
  SDL_Init(SDL_INIT_VIDEO);
  SDL_Window *w = SDL_CreateWindow("", 0, 0, WIDTH, HEIGHT, 0);
  SDL_Renderer *r = SDL_CreateRenderer(w, -1, 0);
  SDL_Event e;
  // initbar();
  while (e.type != SDL_QUIT) {
    SDL_PollEvent(&e);
    if (e.type == SDL_QUIT) {
      break;
    } else if (e.type == SDL_KEYDOWN) {
      SDL_Keycode key = e.key.keysym.sym;
      // printf("%d\n", key);
    }
    SDL_SetRenderDrawColor(r, 111, 223, 232, 255); // set color black
    SDL_RenderClear(r);
    update(r);
    SDL_RenderPresent(r);
    usleep(1000 * 10);
  }
}
