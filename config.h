// Vex Configuration

#ifndef VEX_CONFIG_H
#define VEX_CONFIG_H

#include "termbox-tomas/termbox.h"
#include "keyfuncs.h"

// Set up our colors
tb_color fg_color = TB_WHITE;
tb_color bg_color = TB_DEFAULT;
tb_color error_color = TB_RED;
tb_color mode_color = TB_BLUE;
tb_color pwd_color = TB_LIGHT_GREY;
tb_color status_color = TB_LIGHT_GREY;

// Managing colors
tb_color dir_color = TB_BLUE | TB_BOLD;
tb_color exec_color = TB_GREEN;
tb_color dev_color = TB_MAGENTA | TB_BOLD;
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
	{.keycode='f', .trigger=find_mode},
	{.keycode='w', .trigger=create_window},
	{.keycode='x', .trigger=delete_window}
};

const size_t keys_length = sizeof(keys)/sizeof(keys[0]);

#endif // VEX_CONFIG_H header guard
