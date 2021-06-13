#include <ncurses.h>
#include <stdio.h>
#include <linux/limits.h>
#include <string.h>
#include "file.h"
#include <stdlib.h>

char *strtrun(char *str, unsigned int length) {
	static char tmp[PATH_MAX];
	if (strlen(str)>length) {
		strncpy(tmp,str,length-1);
		strcat(tmp,">");
	} else {
		strcpy(tmp,str);
	}
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

int dir(dir_info *result, char *directory) {
	memset(result,0,sizeof(dir_info));
	return ls(result,directory);
}

int main(int argc, char **arg) {
	dir_info *files = (dir_info*)malloc(sizeof(dir_info));

	int c='a';
	char directory[PATH_MAX];
	if (argc>1) {
		strcpy(directory,arg[1]);
	} else {
		strcpy(directory,".");
	}

	dir(files,directory);

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
			if (strstr(files->fprop[cy],"directory")) {
				strcat(directory,"/");
				strcat(directory,files->options[cy]);
				dir(files,directory);
				cy=2;
				sy=1;
				maxopt=MAX_OPTIONS;
			} else if (strstr(files->fprop[cy],"file")) {
				errno=0;
				char ef[PATH_MAX];
				strcpy(ef,editorcmd);
				strcat(ef," ");
				strcat(ef,directory);
				strcat(ef,"/");
				strcat(ef,files->options[cy]);
				system(ef);
				if (errno!=0) {
					printf("Editor execution failed, %s",strerror(errno));
				}
				keypad(w,TRUE);
			}
		}

		if (c==KEY_LEFT || c=='h') {
			strcat(directory,"../");
			dir(files,directory);
			cy=2;
			sy=1;
			maxopt=MAX_OPTIONS;
		}

		if (c=='d') {
			char ef[PATH_MAX];
			strcpy(ef,directory);
			strcat(ef,"/");
			strcat(ef,files->options[cy]);
			nocbreak();
			cbreak();
			if (getch()=='y') {
				remove(ef);
				dir(files,directory);
				cy=2;
				sy=1;
				maxopt=MAX_OPTIONS;
			}
			halfdelay(3);
		}

		if ((int)cy>=(LINES-2)+(int)sy && sy<maxopt)
			sy++;

		if ((int)cy<=(int)sy+1 && sy>1)
			sy--;

		/* Draw */
		clear();

		int i=1;
		for (i=1;i<LINES-1;i++) {

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
		mvprintw(LINES-1,0," Vex | %s",strtrun(strfill(files->fprop[cy],' ',COLS-1),COLS-1));
		attroff(A_STANDOUT);

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
