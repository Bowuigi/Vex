#include "globals.h"

void find_mode(state *s) {
	s->mode='f';
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
