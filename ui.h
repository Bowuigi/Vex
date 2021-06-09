#include <curses.h>
#include <stdio.h>
#include <linux/limits.h>

#define MAX_OPTIONS 1024
#define LEN(arr) sizeof(arr)-sizeof(arr[0])

void ui(char options[PATH_MAX][MAX_OPTIONS], char fprop[PATH_MAX][MAX_OPTIONS]) {
	int c='a';

	/* Start Curses */
	WINDOW *w;
	w = initscr();

	if (w==NULL) {
		printf("Failed starting Curses");
	}

	/* Curses settings */
	noecho();
	cbreak();
	keypad(w,TRUE);
	halfdelay(3);
	curs_set(0); /* hidecursor */

	/* Init colors */
	if (has_colors()) {
		start_color();
		init_pair(COLOR_BLACK,   COLOR_BLACK,   COLOR_BLACK);
		init_pair(COLOR_GREEN,   COLOR_GREEN,   COLOR_BLACK);
		init_pair(COLOR_RED,     COLOR_RED,     COLOR_BLACK);
		init_pair(COLOR_CYAN,    COLOR_CYAN,    COLOR_BLACK);
		init_pair(COLOR_WHITE,   COLOR_WHITE,   COLOR_BLACK);
		init_pair(COLOR_MAGENTA, COLOR_MAGENTA, COLOR_BLACK);
		init_pair(COLOR_BLUE,    COLOR_BLUE,    COLOR_BLACK);
		init_pair(COLOR_YELLOW,  COLOR_YELLOW,  COLOR_BLACK);
	}

	unsigned int sy=1;
	unsigned int cy=2;
	unsigned int maxopt=MAX_OPTIONS;

	while (c!='q') {
		/* Update */
		c=getch();

		if (c==KEY_UP && cy>2)
			cy--;
		if (c==KEY_DOWN && cy<maxopt)
			cy++;

		if ((int)cy>=(LINES-2)+(int)sy && sy<maxopt)
			sy++;

		if ((int)cy<=(int)sy && sy>2)
			sy--;

		/* Draw */
		clear();
		attron(COLOR_PAIR(COLOR_BLUE));

		mvvline(1,COLS/2,0,LINES-2);

		int i=1;
		for (i=1;i<LINES-1;i++) {
			if (options[i+sy]==NULL || strcmp(options[i+sy],"")) {
				maxopt=i+sy;
				/*break;*/
			}
			if ((i+sy)==cy)
				attron(A_REVERSE);
			mvprintw(i,1,"%s",options[i+sy]);
			if ((i+sy)==cy)
				attroff(A_REVERSE);
		}

		mvprintw(LINES-1,0,"%s",fprop[cy]);
		attroff(COLOR_PAIR(COLOR_BLUE));
		refresh();
		/* End */
	}

	/* Revert settings */
	curs_set(1);/* showcursor */
	keypad(w,FALSE);
	nocbreak();
	echo();

	/* Shut down Curses */
	endwin();
}
