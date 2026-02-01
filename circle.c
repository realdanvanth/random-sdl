#include <SDL2/SDL.h>
#include <unistd.h>
#define HEIGHT 640
#define WIDTH 480
#define NCIRC 1
struct circle {
  int x;
  int y;
  int r;
};
struct circle circles[NCIRC] = {{100, 100, 10}};
void drawcircle(SDL_Renderer *render, int x_centre, int y_centre,
                int r) { // code taken from GFG Midpoint cirle algorithm
  SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
  int x = r, y = 0;
  // Printing the initial point on the axes
  // after translation
  SDL_RenderDrawPoint(render, x + x_centre, y + y_centre);
  SDL_RenderDrawLine(render, x_centre - x, y_centre, x + x_centre, y_centre);
  // When radius is zero only a single
  // point will be printed
  /*if (r > 0) {
    // printf("(%d, %d) ", x + x_centre, -y + y_centre);
    SDL_RenderDrawPoint(render, x + x_centre, -y + y_centre);
    // printf("(%d, %d) ", y + x_centre, x + y_centre);
    SDL_RenderDrawPoint(render, y + x_centre, y + y_centre);
    // printf("(%d, %d)\n", -y + x_centre, x + y_centre);
    SDL_RenderDrawPoint(render, -y + x_centre, x + y_centre);
  }*/

  // Initialising the value of P
  int P = 1 - r;
  while (x > y) {
    y++;

    // Mid-point is inside or on the perimeter
    if (P <= 0)
      P = P + 2 * y + 1;

    // Mid-point is outside the perimeter
    else {
      x--;
      P = P + 2 * y - 2 * x + 1;
    }

    // All the perimeter points have already been printed
    if (x < y)
      break;

    // Printing the generated point and its reflection
    // in the other octants after translation
    // printf("(%d, %d) ", x + x_centre, y + y_centre);
    // SDL_RenderDrawPoint(render, x + x_centre, y + y_centre);
    // printf("(%d, %d) ", -x + x_centre, y + y_centre);
    // SDL_RenderDrawPoint(render, -x + x_centre, y + y_centre);
    SDL_RenderDrawLine(render, x + x_centre, y + y_centre, -x + x_centre,
                       y + y_centre);
    // printf("(%d, %d) ", x + x_centre, -y + y_centre);
    // SDL_RenderDrawPoint(render, x + x_centre, -y + y_centre);
    // printf("(%d, %d)\n", -x + x_centre, -y + y_centre);
    // SDL_RenderDrawPoint(render, -x + x_centre, -y + y_centre);
    SDL_RenderDrawLine(render, x + x_centre, -y + y_centre, -x + x_centre,
                       -y + y_centre);
    // If the generated point is on the line x = y then
    // the perimeter points have already been printed
    if (x != y) {
      // printf("(%d, %d) ", y + x_centre, x + y_centre);
      // SDL_RenderDrawPoint(render, y + x_centre, x + y_centre);
      // printf("(%d, %d) ", -y + x_centre, x + y_centre);
      // SDL_RenderDrawPoint(render, -y + x_centre, x + y_centre);
      SDL_RenderDrawLine(render, y + x_centre, x + y_centre, -y + x_centre,
                         x + y_centre);
      // printf("(%d, %d) ", y + x_centre, -x + y_centre);
      // SDL_RenderDrawPoint(render, y + x_centre, -x + y_centre);
      // printf("(%d, %d)\n", -y + x_centre, -x + y_centre);
      // SDL_RenderDrawPoint(render, -y + x_centre, -x + y_centre);
      SDL_RenderDrawLine(render, y + x_centre, -x + y_centre, -y + x_centre,
                         -x + y_centre);
    }
  }
}
void draw(SDL_Renderer *r) {
  for (int i = 0; i < NCIRC; i++) {
    circles[i].y += 1;
    drawcircle(r, circles[i].x, circles[i].y, circles[i].r);
  }
}
int main() {
  SDL_Init(SDL_INIT_VIDEO);
  SDL_Window *w = SDL_CreateWindow("", 0, 0, HEIGHT, WIDTH, 0);
  SDL_Renderer *r = SDL_CreateRenderer(w, -1, 0);
  SDL_Event e;
  while (e.type != SDL_QUIT) {
    SDL_PollEvent(&e);
    SDL_SetRenderDrawColor(r, 0, 0, 0, 255); // set color black
    SDL_RenderClear(r);
    draw(r);
    SDL_RenderPresent(r);
    usleep(1000 * 2);
  }
}
