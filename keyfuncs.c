#ifndef VEX_KEYFUNCS_C
#define VEX_KEYFUNCS_C

#include "utils.c"

/* Helper functions */

/* Truncate strings */
char *strtrun(char *str, unsigned int length) {
	static char tmp[PATH_MAX];
	if (strlen(str) > length) {
		strcpy(tmp, str);
	} else {
		strncpy(tmp, str, length - 1);
		strcat(tmp, ">");
	}
	return tmp;
}

/* Fill strings */
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

/* A wrapper to ls() that empties the struct first */
int dir(dir_info *result, char *directory) {
	memset(result,(char)0,sizeof(dir_info));
	return ls(result,directory);
}

void loginfo(char *type,char *str) {
	if (strcmp(type,"error"))
		attron(COLOR_PAIR(COLOR_RED));
	mvprintw(LINES-1, 0, strtrun(strfill(str,' ', COLS-1),COLS-1));
	attroff(COLOR_PAIR(COLOR_RED));
	refresh();
}
/* End helper functions */

/* Key functions that modify global variables */
void moveup() {
	if (cy>2)
		cy--;
}

void movedown() {
	if (cy<maxopt)
		cy++;
}

void open() {
	if (strstr(files->fprop[cy],"directory")) {
		strcat(directory,"/");
		strcat(directory,files->options[cy]);
		strcpy(tmpd,"\"");
		strcat(tmpd,directory);
		strcat(tmpd,"\"");
		dir(files,directory);
		cy=2;
		sy=1;
		maxopt=MAX_OPTIONS;
	} else if (strstr(files->fprop[cy],"file")) {
		errno=0;
		char ef[PATH_MAX];
		strcpy(ef,editorcmd);
		strcat(ef," ");
		strcat(ef,"\"");
		strcat(ef,directory);
		strcat(ef,"/");
		strcat(ef,files->options[cy]);
		strcat(ef,"\"");
		int r=system(ef);
		if (r==-1 && errno!=0) {
			printf("Editor execution failed, %s",strerror(errno));
			loginfo("error","Editor execution failed");
		}
		keypad(w,TRUE);
		clear();
	}
}

void back() {
	strcat(directory,"../");
	dir(files,directory);
	cy=2;
	sy=1;
	maxopt=MAX_OPTIONS;
}

void del() {
	char ef[PATH_MAX];
	strcpy(ef,directory);
	strcat(ef,"/");
	strcat(ef,files->options[cy]);
	loginfo("error","Confirm deletion [y/n]");
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
/* End key functions */
#endif /* VEX_KEYFUNCS_H */
