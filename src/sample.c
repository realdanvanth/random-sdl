#include <stdio.h>
#define QMAX 10
struct bars {
  int x;
  int y;
};
struct queue {
  int front;
  int end;
  struct bars queue[QMAX];
};
struct queue bars;
void init() {
  bars.front = -1;
  bars.end = -1;
}
void delete() {
  if (bars.front == bars.end) {
    bars.front = bars.end = -1;
    return;
  }
  bars.front = (bars.front + 1) % QMAX;
}
void insert(int x, int y) {
  if (bars.front == -1 && bars.end == -1) {
    bars.front = 0;
    bars.end = 0;
    bars.queue[bars.front].x = x;
    bars.queue[bars.front].y = y;
  } else {
    bars.end = (bars.end + 1) % QMAX;
    bars.queue[bars.end].x = x;
    bars.queue[bars.end].y = y;
  }
}
int main() {
  init();

  for (int i = 0; i < QMAX; i++)
    insert(i, i);

  for (int i = 0; i < QMAX; i++)
    delete ();

  insert(99, 99);
  printf("%d %d\n ", bars.queue[bars.end].x, bars.queue[bars.end].y);
  return 0;
}
