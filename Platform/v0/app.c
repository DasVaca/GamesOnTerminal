#include <stdio.h>
#include <ncurses.h>

#define FLOOR LINES-10
#define MC_HEIGHT 3
#define MC_WIDTH 5
#define LIFES_HEIGHT 1
#define LIFES_WIDTH 11

void draw_mc(WINDOW * W, char mc[MC_HEIGHT][MC_WIDTH], int y, int x) {
	wclear(W);
	mvwin(W, y, x);
	for (int body = 2; body >= 0; body--)
		wprintw(W, "%s\n", mc[2-body]);
	wrefresh(W);
}
int main() {
	// start ncurses
	initscr();
	cbreak();
	keypad(stdscr, TRUE);
	curs_set(0);
	noecho();
	// Lifes, Game and MC windows
	WINDOW * Lifes = newwin(LIFES_HEIGHT, LIFES_WIDTH, 1, 1); // lifes $ $ $
	WINDOW * Game = newwin(LINES, COLS, 2, 0);
	WINDOW * MC = newwin(MC_HEIGHT, MC_WIDTH, FLOOR-1, COLS/4);
	int mc_posx = COLS/4;
	int mc_posy = FLOOR-1;	
	// MC actions
	char mc[][MC_WIDTH] = {" 0\0", "()\0" , "LL\0"};
	char mc_right[][MC_WIDTH] = { " 0\0", "\\)\0", "|\\\0"};
	char mc_left[][MC_WIDTH] = {" 0\0", "(/\0", "/|\0"};
	char mc_up[][MC_WIDTH] = {" \\0/\0", "_()_\0", "\0"};
	char mc_down[][MC_WIDTH] = {"\0", " 0\0", "¬¬\0"};
	
	char floor[COLS];
	
	for(int i = 0; i < COLS; i++) {
		if (i > COLS*2/3 && i < COLS*2/3 + 5)
			floor[i] = ' ';
		else
			floor[i] = '*';
	}

	// draw life counter
	wprintw(Lifes, "LIFES");
	for(int life = 0; life < 3; life++)
		wprintw(Lifes, " $");
	wrefresh(Lifes);

	// draw floor
	for(int lines = FLOOR; lines < LINES; lines++)
		mvwprintw(Game, lines, 0, floor);
	wrefresh(Game);

	int c;
	do {
		// draw mc
		switch(c) {
			case 'w':
				draw_mc(MC, mc_up, mc_posy, mc_posx); break;
			case 's':
				draw_mc(MC, mc_down, mc_posy, mc_posx); break;
			case 'a':
				mc_posx--;
				draw_mc(MC, mc_left, mc_posy, mc_posx); break;
			case 'd':
				mc_posx++;
				draw_mc(MC, mc_right, mc_posy, mc_posx); break;
			default:
				draw_mc(MC, mc, mc_posy, mc_posx); break;
		}

		wrefresh(Game);
		c = wgetch(MC);
	} while( c != 'q');

	delwin(Game);
	delwin(MC);
	delwin(Lifes);
	endwin();
	return 0;
}
