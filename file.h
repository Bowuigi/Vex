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
#include <string.h>
#include "config.h"

/* Define byte sizes */
#define KB 1000
#define MB 1000*KB
#define GB 1000*MB

/* Way less than PATH_MAX, to avoid Stack overrun */
#define MAX_FILENAME_LEN 256

/* Small to avoid Stack overrun */
/* "rwx directory 99999GB" is the largest string it can handle */
#define MAX_FPROP_LEN 23

char *getFileProperties(struct stat stats);

typedef struct {
	char options[MAX_FILENAME_LEN][MAX_OPTIONS];
	char fprop[MAX_FPROP_LEN][MAX_OPTIONS];
} dir_info;

/* 
 * Accepts a Malloc'd typedef'd struct defined in the same file
 * Then returns the contents and some file properties of the directory specified on the second argument
*/
int ls(dir_info *result, char *directory) {
	strcat(directory,"/");
	struct dirent *de;  /* Pointer for directory entry */
	DIR *dir = opendir(directory);

	memset(result,0,sizeof(dir_info));

	errno=0;

	if (dir == NULL) {
		if (errno==0) {
			errno=13; /* Default to permission denied */
		}
		printf("%s\n",strerror(errno));
		return 1;
	}
	int i=0;

	while ((de = readdir(dir)) != NULL && i<MAX_OPTIONS) {
		i++;
		static struct stat stats; /* Struct holding the stats of a file */
		char name[MAX_FILENAME_LEN]="";
		memcpy(name,de->d_name,sizeof(de->d_name));
		char path[PATH_MAX];
		strcpy(path,directory);
		strcat(path,name);
		if (strcmp(name,".")) {
			errno=0;
			if (stat(path,&stats)==0) {
				char *fp=getFileProperties(stats);
				if (strlen(fp)>MAX_FPROP_LEN) {
					printf("Attempted to get a file so big, that I have to truncate the size so the file manager doesn't crash, please make it smaller");
					strncpy(result->fprop[i],fp,sizeof(char)*MAX_FPROP_LEN-1);
					strcat(result->fprop[i],">");
				} else {
					strcpy(result->fprop[i],fp);
				}
				if (strlen(name)>MAX_FILENAME_LEN) {
					printf("Attempted to read a filename longer than 256 characters, why is the filename so long? Anyway, I will just truncate it");
					strncpy(result->options[i],name,sizeof(char)*MAX_FILENAME_LEN-1);
					strcat(result->options[i],">");
				} else {
					strcpy(result->options[i],name);
				}
			} else {
				if (errno==0) {
					errno=13; /* Default to permission denied */
				}
				printf("%s: %s\n",name,strerror(errno));
			}
		}
	}

	closedir(dir);

	return 0;
}

/*
 * Heavily modified version of
 * https://codeforwin.org/2018/03/c-program-find-file-properties-using-stat-function.html
*/
char *getFileProperties(struct stat stats) {
	char str[MAX_FPROP_LEN]="";
	static char tmp[MAX_FPROP_LEN]="";

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
	if        (S_ISLNK(stats.st_mode)) {
		strcat(str,"symlink");
	} else if (S_ISBLK(stats.st_mode)) {
		strcat(str,"block");
	} else if (S_ISCHR(stats.st_mode)) {
		strcat(str,"character");
	} else if (S_ISFIFO(stats.st_mode)) {
		strcat(str,"FIFO");
	} else if (S_ISREG(stats.st_mode)) {
		strcat(str,"file");
	} else if (S_ISDIR(stats.st_mode)) {
		strcat(str,"directory");
	}

	strcat(str," ");
	/* Human readable file size */
	/* Replace ld with lld if you get a warning*/
	if (stats.st_size>=GB) {
		sprintf(tmp,"%ldGB",stats.st_size/GB);
		strcat(str,tmp);
	} else if (stats.st_size>=MB) {
		sprintf(tmp,"%ldMB",stats.st_size/MB);
		strcat(str,tmp);
	} else if (stats.st_size>=KB) {
		sprintf(tmp,"%ldkB",stats.st_size/KB);
		strcat(str,tmp);
	} else {
		sprintf(tmp,"%ldB",stats.st_size);
		strcat(str, tmp);
	}


	strcpy(tmp,"");
	strcpy(tmp,str);
	strcpy(str,"");
	return tmp;
}
