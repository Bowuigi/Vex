#ifndef VEX_GLOBALS_H
#define VEX_GLOBALS_H

#include <stdio.h>
#include <string.h>
#include <curses.h>
#include <linux/limits.h>
#define MAX_OPTIONS 1024

/* Define byte sizes */
#define KB 1000
#define MB 1000*KB
#define GB 1000*MB

/* Way less than PATH_MAX, to avoid Stack overrun */
#define MAX_FILENAME_LEN 256

/* Small to avoid Stack overrun */
/* "rwx directory 99999GB" is the largest string it can handle */
#define MAX_FPROP_LEN 23

typedef struct {
	char options[MAX_OPTIONS][MAX_FILENAME_LEN];
	char fprop[MAX_OPTIONS][MAX_FPROP_LEN];
} dir_info;


unsigned int sy=2;
unsigned int cy=2;
unsigned int maxopt=MAX_OPTIONS;
int c='a';
char directory[PATH_MAX];
char tmpd[PATH_MAX+2];
dir_info *files;
WINDOW *w;

#endif /* VEX_GLOBALS_H */
