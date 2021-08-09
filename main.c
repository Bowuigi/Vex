#include <stdio.h>
#include "config.h"

// Vex Globals
state s;

#define MAX_COLOR_VALUE 255

void draw_hline(int startx, int endx, int y, tb_color bg, tb_color fg, char line) {
	int i=0;
	for (i=0; i<endx; i++) {
		tb_char(startx+i,y,bg,fg,line);
	}
}

void draw_vline(int x,int starty, int endy, tb_color bg, tb_color fg, char line) {
	int i=0;
	for (i=0; i<endy; i++) {
		tb_char(x,starty+i,bg,fg,line);
	}
}

void draw(int w, int h) {
	if (s.cursor_window>=s.windows)
		s.cursor_window=s.windows-1;

	tb_stringf(0, 0, pwd_color|TB_REVERSE, bg_color, " %s/ ","~/C/projects");
	tb_string(w-5, 0, fg_color, mode_color, " Vex ");
	draw_hline(0,w,h-2,fg_color, bg_color,' ');
	tb_string(0, h-2, status_color|TB_REVERSE, bg_color, " 4MB file - rwx ");
	tb_stringf(w-10, h-2, fg_color, win_n_color, "[%i/%i]",s.cursor_window+1,s.windows);
	tb_stringf(w-3, h-2, fg_color, mode_color, " %c ",s.mode);
	tb_string(1, h-1, error_color, bg_color, "Permission denied");

	// Sample text
	int sep=w/s.windows;
	int i=0;
	for (i=0;i<s.windows;i++) {
		tb_stringf((i*sep)+1, 1, dir_color, bg_color, "%s%s%s",dir_prefix,"Directory1",dir_suffix);
		tb_stringf((i*sep)+1, 2, dir_color, bg_color, "%s%s%s",dir_prefix,"Directory2",dir_suffix);
		tb_stringf((i*sep)+1, 3, exec_color, bg_color,"%s%s%s",exec_prefix,"executable1",exec_suffix);
		tb_stringf((i*sep)+1, 4, exec_color, bg_color,"%s%s%s",exec_prefix,"executable2",exec_suffix);
		tb_stringf((i*sep)+1, 5, dev_color, bg_color,"%s%s%s",dev_prefix,"device",dev_suffix);
		tb_stringf((i*sep)+1, 6, dev_color, bg_color,"%s%s%s",dev_prefix,"device2",dev_suffix);
		tb_stringf((i*sep)+1, 7, file_color, bg_color,"%s%s%s",file_prefix,"file",file_suffix);

		if (i==s.cursor_window) {
			tb_string((i*sep)+1, 8, fg_color|TB_REVERSE, bg_color, "C");
		}

		if ((i*sep)-1 > 0)
			draw_vline((i*sep)-1, 1, h-3, mode_color, bg_color, '|');
	}

	tb_render();
}

int main(void) {
	if (tb_init() != 0) {
		return 1; // couldn't initialize our screen
	}

	tb_set_title("Vex ~/C/projects/");

	// Current mode
	s.mode='n';

	// Amount of open windows
	s.windows=1;

	// get the screen size
	s.w = tb_width();
	s.h = tb_height();

	draw(s.w,s.h);

	// now, wait for keyboard or input
	struct tb_event ev;

	while (tb_poll_event(&ev) != -1) {
		switch (ev.type) {
		case TB_EVENT_RESIZE:
			s.w = ev.w;
			s.h = ev.h;

			if (s.windows>s.h/5) {
				s.windows=s.h/5;
			}

			tb_clear_buffer();
			break;

		case TB_EVENT_KEY:
			if (ev.ch=='q')
				goto done;

			size_t k=0;
			for (k=0;k<keys_length;k++) {
				if (ev.meta== keys[k].mod      &&
				    ev.key == keys[k].special  &&
				    ev.ch  == keys[k].key
				    ) {
					keys[k].trigger(&s);
				}
			}
		}

		draw(s.w,s.h);

		// flush the output
		tb_render();
	}

	done:
	// make sure to shutdown
	tb_shutdown();
	return 0;
}
