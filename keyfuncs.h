#include "globals.h"

void find_mode(state *s) {
	s->mode='f';
}

void normal_mode(state *s) {
	s->mode='n';
}

void create_window(state *s) {
	if (s->windows<s->h/5) {
		tb_clear_buffer();
		s->windows++;
	}
}

void delete_window(state *s) {
	if (s->windows>1) {
		tb_clear_buffer();
		s->windows--;
	}
}

void cursor_up(state *s) {
	if (s->cursor_y>1)
		s->cursor_y--;
}

void cursor_down(state *s) {
	if (s->cursor_y<10)
		s->cursor_y++;
}

void next_window(state *s) {
	tb_clear_buffer();
	s->cursor_window++;

	if (s->cursor_window>=s->windows)
		s->cursor_window=0;
}

void clear_screen(state *s) {
	tb_clear_screen();
	tb_clear_buffer();
	s->w=tb_width();
	s->h=tb_height();
}
