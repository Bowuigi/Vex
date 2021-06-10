#include <curses.h>
#include <stdio.h>
#include <linux/limits.h>

#define MAX_OPTIONS 1024
#define LEN(arr) sizeof(arr)-sizeof(arr[0])
#define MAX_WIN_WIDTH COLS-1

char *strtrun(char *str, int length) {
	static char tmp[PATH_MAX];
	strncpy(tmp,str,length);
	return tmp;
}

char *strfill(char *str, char fill, int finallength) {
	static char tmp[PATH_MAX];
	strcpy(tmp,str);
	int len=strlen(str);
	int f=len;
	for (f=len;f<finallength;f++) {
		tmp[f]=fill;
	}
	tmp[finallength]='\0';
	return tmp;
}

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

		if ((c==KEY_UP || c=='k') && cy>2)
			cy--;
		if ((c==KEY_DOWN || c=='j') && cy<maxopt)
			cy++;

		if (c==KEY_RIGHT || c=='l') {
			break;
		}

		if ((int)cy>=(LINES-2)+(int)sy && sy<maxopt)
			sy++;

		if ((int)cy<=(int)sy+1 && sy>1)
			sy--;

		/* Draw */
		clear();

		int i=1;
		for (i=1;i<LINES-1;i++) {
			if (options[i+sy]==NULL || strcmp(options[i+sy],"")) {
				maxopt=i+sy;
			}

			/* Color Handling */

			/* Executables */
			if (strstr(fprop[i+sy],"x"))
				attron(COLOR_PAIR(COLOR_GREEN));

			/* Directories */
			if ((strstr(fprop[i+sy],"directory"))!=NULL)
				attron(COLOR_PAIR(COLOR_BLUE));

			/*--------------------------*/

			if ((i+sy)==cy)
				attron(A_REVERSE);
			mvprintw(i,1,"%s",strtrun(strfill(options[i+sy],' ',MAX_WIN_WIDTH),MAX_WIN_WIDTH));
			if ((i+sy)==cy)
				attroff(A_REVERSE);

			/* Disable color*/
			if (strstr(fprop[i+sy],"x"))
				attroff(COLOR_PAIR(COLOR_GREEN));

			if ((strstr(fprop[i+sy],"directory"))!=NULL)
				attroff(COLOR_PAIR(COLOR_BLUE));

			/*----------------------------*/

		}

		mvprintw(LINES-1,0,"%s",fprop[cy]);

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
