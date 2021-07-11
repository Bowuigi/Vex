#include <stdlib.h>
#include "config.h"

/* --------------------------------------- Main Function ----------------------------------------- */
int main(int argc, char **arg) {
	files=malloc(sizeof(dir_info));
	if (argc>1) {
		strcpy(directory,arg[1]);
	} else {
		strcpy(directory,".");
	}

	dir(files,directory);

	/* Start Curses */
	w = initscr();

	if (w==NULL) {
		printf("Failed starting Curses");
	}

	/* Curses settings */
	noecho();
	cbreak();
	keypad(w,TRUE);
	halfdelay(3);
	curs_set(0); /* hide cursor */

	/* Init colors */
	if (has_colors()) {
		start_color();
		use_default_colors();
		init_pair(COLOR_BLUE ,   COLOR_BLUE ,   -1);
		init_pair(COLOR_GREEN,   COLOR_GREEN,   -1);
		init_pair(COLOR_RED  ,   COLOR_RED  ,   -1);
		init_pair(COLOR_WHITE,   COLOR_WHITE,   -1);
	}


	while (c!='q') {
		/* Update */
		c=getch();

		if ((int)cy>=(LINES-3)+(int)sy && sy<maxopt)
			sy++;

		if ((int)cy<=(int)sy+1 && sy>1)
			sy--;

		int k=0;
		for (k=0;k<KEY_AMOUNT;k++) {
			if (c==keys[k].keycode)
				keys[k].trigger();
		}

		/* Draw */
		erase();

		int i=1;
		for (i=1;i<LINES-2;i++) {
			if ((i+sy)>=MAX_OPTIONS) {
				break;
			}

			char so[MAX_FILENAME_LEN];
			strcpy(so,files->options[i+sy]);
			char sf[MAX_FPROP_LEN];
			strcpy(sf,files->fprop[i+sy]);

			if (strcmp(so,"")) {
				maxopt=i+sy;
			}

			/* Color Handling */

			/* Executables */
			if (strstr(sf,"x"))
				attron(COLOR_PAIR(COLOR_GREEN));

			/* Directories */
			if ((strstr(sf,"directory"))!=NULL)
				attron(COLOR_PAIR(COLOR_BLUE));

			/*--------------------------*/


			if ((i+sy)==cy)
				attron(A_REVERSE);

			mvprintw(i,1,"%s",strtrun(strfill(so,' ',COLS-1),COLS-1));

			attroff(A_REVERSE);

			/* Disable color*/
			if (strstr(sf,"x"))
				attroff(COLOR_PAIR(COLOR_GREEN));

			if ((strstr(sf,"directory"))!=NULL)
				attroff(COLOR_PAIR(COLOR_BLUE));

			/*----------------------------*/
		}

		attron(A_STANDOUT);
		mvprintw(LINES-2,0," Vex | %s",strtrun(strfill(files->fprop[cy],' ',COLS-1),COLS-1));
		attroff(A_STANDOUT);
		loginfo("normal",""); /* HACK: Clear the bottom part of the screen */

		refresh();
		/* End */
	}

	/* Revert settings */
	clear();
	curs_set(1);/* show cursor */
	keypad(w,FALSE);
	nocbreak();
	echo();

	/* Shut down Curses */
	endwin();

	/* Free the malloc'd variable files */
	free(files);

	return 0;
}
/* ------ End main function ------ */
