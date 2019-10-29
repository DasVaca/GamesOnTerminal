// classic snake game

#include "snake0.h"

int game = 1;

int main()
{
  uint snakelen = 3, aux_lastmove = LEFT; // initial length, initial direction
  uint * lastmove = &aux_lastmove;
  Position aux_cats;
  Position * cats = &aux_cats;
  Position snake[MAX_LENGTH];
  for(uint i = 0; i < MAX_LENGTH; i++) { snake[i].x = 0; snake[i].y = 0;}

  // Initialize ncurses
  initscr();
  cbreak();
  halfdelay( DELAY );
  keypad(stdscr, TRUE);
  noecho();

  int h, w;
  //getmaxyx(stdscr, h, w);
  h = LINES-1; w = COLS-1;
  srand(time(NULL));

  // Starting positions
  snake[0].y = h/2, snake[0].x = w/2; // center of screen
  snake[1].y = snake[0].y+1; snake[1].x = snake[0].x;
  snake[2].y = snake[1].y+1; snake[2].x = snake[0].x;
  UpdateCatPosition( cats, h, w); // some random position

  while ( RUALIVE(snake, &snakelen, &h, &w) ) // while you are alive
  {
    clear();
    ShowGame( snake, snakelen, cats, h , w);
    if ( EATED(snake, cats) ) // snake just eats a cat
    {
      UpdateCatPosition( cats, h, w); // create a new cat at a random position
      IncreaseSnake( snake, &snakelen );
    }
    MoveSnake(snake, snakelen, lastmove);
  }

  // Done
	mvaddstr(h/2, w/2, "Game Over, Press any key to quit");
	refresh();
	getch();
	endwin();
	exit(0);

  return 0;
}
