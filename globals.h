// Vex globals
#ifndef VEX_GLOBALS_H
#define VEX_GLOBALS_H

#include "termbox-tomas/termbox.h"

typedef struct {
	int windows;
	char mode;
	int16_t w;
	int16_t h;
} state;

struct key {
	uint32_t keycode;
	void (*trigger)(state *s);
};

#endif // VEX_GLOBALS_H header guard
