/*
 * Vex, a file manager inspired by NetRW in Vim
 * By Bowuigi
* Licensed under the GNU GPLv3
*/

#ifndef VEX_FILE_H
#define VEX_FILE_H

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

typedef struct {
	char options[MAX_FILENAME_LEN][MAX_OPTIONS];
	char fprop[MAX_FPROP_LEN][MAX_OPTIONS];
} dir_info;

#endif /* VEX_FILE_H */
