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

#define KB 1000
#define MB 1000*KB
#define GB 1000*MB

void printFileProperties(struct stat stats,char *filename);

int main(int argc, char **arg) {
	char directory[PATH_MAX];
	strcpy(directory,arg[1]);
	strcat(directory,"/");
	struct dirent *de;  /* Pointer for directory entry */
	struct stat stats; /* Struct holding the stats of a file */
	DIR *dir = opendir(directory);
	errno=0;

	if (dir == NULL) {
		printf("%s\n",strerror(errno));
		return 1;
	}
	while ((de = readdir(dir)) != NULL) {
		char name[256]="";
		memcpy(name,de->d_name,sizeof(de->d_name));
		char path[PATH_MAX+256]="";
		strcat(path,directory);
		strcat(path,name);
		if (strcmp(name,".")) {
			errno=0;
			if (stat(path,&stats)==0) {
				printFileProperties(stats,name);
				printf("\n");
			} else {
				printf("%s\n",strerror(errno));
			}
		}
	}

	closedir(dir);
}

/*
 * Heavily modified version of
 * https://codeforwin.org/2018/03/c-program-find-file-properties-using-stat-function.html
*/
void printFileProperties(struct stat stats, char *filename) {
	struct tm dt;

	/* File permissions */
	if (stats.st_mode & S_IRUSR) {
		printf("r");
	} else {
		printf("-");
	}
	if (stats.st_mode & S_IWUSR) {
		printf("w");
	} else {
		printf("-");
	}
	if (stats.st_mode & S_IXUSR) {
		printf("x");
	} else {
		printf("-");
	}

	printf(" ");

	/* File type */
	if        (S_ISBLK(stats.st_mode)) {
		printf("block");
	} else if (S_ISCHR(stats.st_mode)) {
		printf("character");
	} else if (S_ISFIFO(stats.st_mode)) {
		printf("FIFO");
	} else if (S_ISREG(stats.st_mode)) {
		printf("file");
	} else if (S_ISDIR(stats.st_mode)) {
		printf("directory");
	} else if (S_ISLNK(stats.st_mode)) {
		printf("symlink");
	}

	printf(" ");
	/* Human readable file size */
	if (stats.st_size>GB) {printf("%ldGB",stats.st_size/GB);} else
	if (stats.st_size>MB) {printf("%ldMB",stats.st_size/MB);} else
	if (stats.st_size>KB) {printf("%ldkB",stats.st_size/KB);} else
	                      {printf("%ldB" ,stats.st_size)   ;}

	printf(" ");

	/* File modification time */
	dt = *(gmtime(&stats.st_mtime));
	printf("mod: %d-%d-%d %d:%d:%d", dt.tm_mday, dt.tm_mon, dt.tm_year + 1900, dt.tm_hour, dt.tm_min, dt.tm_sec);

	printf(" ");

	printf("%s",filename);
}
