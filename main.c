/*
 * Vex, a file manager inspired by NetRW in Vim
 * By Bowuigi
 * Licensed under the GNU GPLv3
*/

#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include <linux/limits.h>
#include "ui.h"

/* Define byte sizes */
#define KB 1000
#define MB 1000*KB
#define GB 1000*MB

char *getFileProperties(struct stat stats);

int main(int argc, char **arg) {
	char directory[PATH_MAX];
	if (argc>1) {
		strcpy(directory,arg[1]);
	} else {
		strcpy(directory,".");
	}
	strcat(directory,"/");
	struct dirent *de;  /* Pointer for directory entry */
	DIR *dir = opendir(directory);
	errno=0;

	if (dir == NULL) {
		if (errno==0) {
			errno=13; /* Default to permission denied */
		}
		printf("%s\n",strerror(errno));
		return 1;
	}
	int i=0;
	static char opt[PATH_MAX][MAX_OPTIONS];
	static char fprop[PATH_MAX][MAX_OPTIONS];

	while ((de = readdir(dir)) != NULL) {
		i++;
		static struct stat stats; /* Struct holding the stats of a file */
		char name[256]="";
		memcpy(name,de->d_name,sizeof(de->d_name));
		char path[PATH_MAX+256];
		strcpy(path,directory);
		strcat(path,name);
		if (strcmp(name,".")) {
			errno=0;
			if (stat(path,&stats)==0) {
				strcpy(fprop[i],getFileProperties(stats));
				strcpy(opt[i],name);
				printf("%s\n",fprop[i]);
			} else {
				if (errno==0) {
					errno=13; /* Default to permission denied */
				}
				printf("%s: %s\n",name,strerror(errno));
			}
		}
	}

	closedir(dir);

	/*-----------------------------*/
	/*ui(opt,disp);*/
	ui(opt,fprop);
}

/*
 * Heavily modified version of
 * https://codeforwin.org/2018/03/c-program-find-file-properties-using-stat-function.html
*/
char *getFileProperties(struct stat stats) {
	struct tm dt;
	char str[MAX_OPTIONS]="";
	static char tmp[MAX_OPTIONS]="";

	/* File permissions */
	if (stats.st_mode & S_IRUSR) {
		strcat(str,"r");
	} else {
		strcat(str,"-");
	}
	if (stats.st_mode & S_IWUSR) {
		strcat(str,"w");
	} else {
		strcat(str,"-");
	}
	if (stats.st_mode & S_IXUSR) {
		strcat(str,"x");
	} else {
		strcat(str,"-");
	}

	strcat(str," ");

	/* File type */
	if        (S_ISBLK(stats.st_mode)) {
		strcat(str,"block");
	} else if (S_ISCHR(stats.st_mode)) {
		strcat(str,"character");
	} else if (S_ISFIFO(stats.st_mode)) {
		strcat(str,"FIFO");
	} else if (S_ISREG(stats.st_mode)) {
		strcat(str,"file");
	} else if (S_ISDIR(stats.st_mode)) {
		strcat(str,"directory");
	} else if (S_ISLNK(stats.st_mode)) {
		strcat(str,"symlink");
	}

	strcat(str," ");
	/* Human readable file size */
	if (stats.st_size>=GB) {
		sprintf(tmp,"%lldGB",stats.st_size/GB);
		strcat(str,tmp);
	} else if (stats.st_size>=MB) {
		sprintf(tmp,"%lldMB",stats.st_size/MB);
		strcat(str,tmp);
	} else if (stats.st_size>=KB) {
		sprintf(tmp,"%lldkB",stats.st_size/KB);
		strcat(str,tmp);
	} else {
		sprintf(tmp,"%lldB",stats.st_size);
		strcat(str, tmp);
	}

	strcat(str," ");

	/* File modification time */
	dt = *(gmtime(&stats.st_mtime));
	sprintf(tmp,"mod: %d-%d-%d %d:%d:%d", dt.tm_year, dt.tm_mon, dt.tm_mday + 1900, dt.tm_hour, dt.tm_min, dt.tm_sec);
	strcat(str,tmp);

	strcat(str," ");

	strcpy(tmp,"");
	strcpy(tmp,str);
	strcpy(str,"");
	return tmp;
}
