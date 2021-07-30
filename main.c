#include <stdio.h>
#include "termbox-tomas/termbox.h"

// set up our colors
tb_color fg_color = TB_WHITE;
tb_color bg_color = TB_DEFAULT;
tb_color error_color = TB_RED;
tb_color mode_color = TB_BLUE;
tb_color pwd_color = TB_LIGHT_GREY;
tb_color status_color = TB_LIGHT_GREY;

// Managing colors
tb_color dir_color = TB_BLUE;
tb_color exec_color = TB_GREEN;
tb_color dev_color = TB_MAGENTA;
tb_color file_color = TB_LIGHT_GREY;

// Vex Globals
char mode='n';

#define MAX_COLOR_VALUE 255

void draw_line(int startx, int endx, int y, tb_color bg, tb_color fg, char line) {
	int i=0;
	for (i=0; i<endx; i++) {
		tb_char(startx+i,y,bg,fg,line);
	}
}

void draw(int w, int h) {
	tb_stringf(0, 0, pwd_color|TB_REVERSE, bg_color, " %s/ ","~/C/projects");
	tb_string(w-5, 0, fg_color, mode_color, " Vex ");
	draw_line(0,w,h-2,fg_color, bg_color,' ');
	tb_string(0, h-2, status_color|TB_REVERSE, bg_color, " 4MB file - rwx ");
	tb_stringf(w-3, h-2, fg_color, mode_color, " %c ",mode);
	tb_string(1, h-1, error_color, bg_color, "Permission denied");

	// Sample text
	tb_string(1, 1, dir_color, bg_color, "Directory/");
	tb_string(1, 2, dir_color, bg_color, "Directory2/");
	tb_string(1, 3, exec_color, bg_color, "* executable");
	tb_string(1, 4, exec_color, bg_color, "* executable2");
	tb_string(1, 5, dev_color, bg_color, "- device");
	tb_string(1, 6, dev_color, bg_color, "- device2");
	tb_string(1, 7, file_color, bg_color, "file");
	tb_string(1, 8, file_color, bg_color, "file2");

	tb_render();
}

int main(void) {
	if (tb_init() != 0) {
		return 1; // couldn't initialize our screen
	}

	// get the screen resolution
	int w = tb_width();
	int h = tb_height();

	draw(w,h);

	// now, wait for keyboard or input
	struct tb_event ev;

	while (tb_poll_event(&ev) != -1) {
		switch (ev.type) {
		case TB_EVENT_RESIZE:
			w = ev.w;
			h = ev.h;
			tb_clear_buffer();
			break;

		case TB_EVENT_KEY:
			if (ev.ch == 'q')
				goto done;

			if (ev.ch == 'f')
				mode='f';

			if (ev.key==TB_KEY_ESC)
				mode='n';

			break;
		}

		draw(w,h);

		// flush the output
		tb_render();
	}

	done:
	// make sure to shutdown
	tb_shutdown();
	return 0;
}
