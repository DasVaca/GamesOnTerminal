#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define MAX_LENGTH 30
#define DELAY 1
#define UP KEY_UP
#define DOWN KEY_DOWN
#define RIGHT KEY_RIGHT
#define LEFT KEY_LEFT

typedef unsigned int uint;
typedef struct { int x, y; } Position;

int WallCollission(Position * snake, int * y, int * x)
{
  return (snake[0].x == *x || snake[0].y == *y) || (snake[0].x == 0 || snake[0].y == 0);
}
int SelfCollission(Position * snake, uint * snakelen)
{
  if (*snakelen < 4) return 0; // impossible to self-collide

  for (int i = 4; i <= *snakelen; i++)
  {
    if ( snake[0].x == snake[i].x  && snake[0].y == snake[i].y)
      return 1;
  }
  return 0;
}
int RUALIVE(Position * snake, uint * snakelen, int * h, int * w)
{
  return !(WallCollission(snake, h, w) || SelfCollission(snake, snakelen));
}

int EATED(Position * snake, Position * cats)
{
  return (snake[0].x == cats->x && snake[0].y == cats->y);
}

void UpdateCatPosition(Position * cats, int h, int w)
{
  cats->x = (rand() % (w-2))+1; cats->y = (rand() % (h-2))+1;
}

int WhereAddTail(Position * snake, uint snakelen)
{
  snakelen -= 1;
  switch (snake[snakelen].x - snake[snakelen-1].x)
  {
    case -1: return LEFT; break;
    case 1: return RIGHT; break;
  }
  switch (snake[snakelen].y - snake[snakelen-1].y)
  {
    case -1: return DOWN; break;
    case 1: return UP; break;
  }
  return 0;
}
void AddTail(Position * snake, uint * snakelen, char coordinate, int direction)
{
  switch ( coordinate )
  {
    case 'x': snake[*snakelen].x = snake[*snakelen-1].x + direction; break;
    case 'y': snake[*snakelen].y = snake[*snakelen-1].y + direction; break;
  }
}
void IncreaseSnake(Position * snake, uint * snakelen)
{
  *snakelen += 1;
  if ( *snakelen < 30 )
  {
    switch ( WhereAddTail( snake, *snakelen) )
    {
      case 0    : break;
      case UP   : AddTail( snake, snakelen, 'y', 1); break;
      case DOWN : AddTail( snake, snakelen, 'y', -1); break;
      case RIGHT: AddTail( snake, snakelen, 'x', 1); break;
      case LEFT : AddTail( snake, snakelen, 'x', -1); break;
    }
  }
}

void MoveSnake(Position * snake, uint snakelen, uint * lastmove)
{
  int key = 0, aux = snake[0].x, auy = snake[0].y;
  key = getch();

  if( key <= 0 ) key = *lastmove;
  else *lastmove = key;
  switch ( key )
  {
    case 'w': key = UP; break;
    case 's': key = DOWN; break;
    case 'a': key = LEFT; break;
    case 'd': key = RIGHT; break;
    default: break;
  }
  switch ( key )
  {
    case UP   : snake[0].y -= 1; break;
    case DOWN : snake[0].y += 1; break;
    case RIGHT: snake[0].x += 1; break;
    case LEFT : snake[0].x -= 1; break;
    default: break;
  }

  for (uint i = 1; i <= snakelen; i++)
  {
    int tmp;
    tmp = snake[i].x;
    snake[i].x = aux; aux = tmp;

    tmp = snake[i].y;
    snake[i].y = auy; auy = tmp;
  }
}

void ShowGame(Position * snake, uint snakelen, Position * cats, int h, int w)
{
  for (uint i = 0; i <= w; i++)
  {
    mvaddch(0, i, '-');
    mvaddch(h, i, '-');
  }
  for (uint i = 0; i <= h; i++)
  {
    mvaddch(i, 0, '|');
    mvaddch(i, w, '|');
  }

  for (uint i = 0; i <= snakelen; i++)
  {
    if ( i == 0 ) mvaddch(snake[i].y, snake[i].x, 'O');
    else mvaddch(snake[i].y, snake[i].x, 'o');
  }
  mvaddch(cats->y, cats->x, '#');
}
