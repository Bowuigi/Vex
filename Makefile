# Makefile for Vex, the file manager inspired on NetRW from Vim

IN=main.c
VEX=vex
CFLAGS=-Os -ansi
CC=cc

build:
	$(CC) $(IN) $(CFLAGS) -o $(VEX)

clean:
	rm *.o $(VEX)

install: build
	mkdir $(PREFIX)
	cp $(VEX) $(PREFIX)/bin/

uninstall:
	rm -f $(PREFIX)/bin/$(VEX)
