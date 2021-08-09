// Vex Configuration

#ifndef VEX_CONFIG_H
#define VEX_CONFIG_H

#include <stdlib.h>
#include "termbox-tomas/termbox.h"
#include "keyfuncs.h"

// UI colors
tb_color fg_color = TB_WHITE;
tb_color bg_color = TB_DEFAULT;
tb_color error_color = TB_RED;
tb_color mode_color = TB_BLUE;
tb_color pwd_color = TB_LIGHT_GREY;
tb_color status_color = TB_LIGHT_GREY;
tb_color win_n_color = TB_RED;

// Filename colors
// Directories
tb_color dir_color = TB_BLUE | TB_BOLD;
// Executables
tb_color exec_color = TB_GREEN;
// Devices
tb_color dev_color = TB_MAGENTA | TB_BOLD;
// Normal files
tb_color file_color = TB_LIGHT_GREY;

// Filename decorations

// Directories
const char *dir_prefix = "";
const char *dir_suffix = "/";
// Executables
const char *exec_prefix = "*";
const char *exec_suffix = "*";
// Devices
const char *dev_prefix = "- ";
const char *dev_suffix = "";
// Normal files
const char *file_prefix = "";
const char *file_suffix = "";

struct key keys[] = {
	// Modes
	{.mod=0           , .special=0                , .key='f', .trigger=find_mode     },
	{.mod=0           , .special=TB_KEY_ESC       , .key=0  , .trigger=normal_mode   },
	// Window management
	{.mod=0           , .special=0                , .key='w', .trigger=create_window },
	{.mod=0           , .special=0                , .key='x', .trigger=delete_window },
	{.mod=0           , .special=0                , .key=' ', .trigger=next_window   },
	// Cursor
	{.mod=0           , .special=0                , .key='k', .trigger=cursor_up     },
	{.mod=0           , .special=0                , .key='j', .trigger=cursor_down   },
	{.mod=0           , .special=TB_KEY_ARROW_UP  , .key=0  , .trigger=cursor_up     },
	{.mod=0           , .special=TB_KEY_ARROW_DOWN, .key=0  , .trigger=cursor_down   },
	// Other
	{.mod=TB_META_ALT , .special=0                , .key='l', .trigger=create_window }
};

const size_t keys_length = sizeof(keys)/sizeof(keys[0]);

#endif // VEX_CONFIG_H header guard
