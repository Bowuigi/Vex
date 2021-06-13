# Makefile for Vex, the file manager inspired on NetRW from Vim

IN=main.c
VEX=vex
CFLAGS=-Og -ansi -Wall -g
LDFLAGS=-lncursesw
CC=gcc
STRIP=strip

build:
	$(CC) $(IN) $(CFLAGS) $(LDFLAGS) -o $(VEX)
#	$(STRIP) $(VEX)

clean:
	rm $(VEX)

install: build
	mkdir $(PREFIX)
	cp $(VEX) $(PREFIX)/bin/

uninstall:
	rm -f $(PREFIX)/bin/$(VEX)
