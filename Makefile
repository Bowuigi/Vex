# Makefile for Vex, the file manager inspired on NetRW from Vim

IN=main.c
VEX=vex
CFLAGS=-Og -ansi -Wall
LDFLAGS=-lncursesw
CC=cc
PREFIX=/usr/local

build:
	$(CC) $(IN) $(CFLAGS) $(LDFLAGS) -o $(VEX)

clean:
	rm $(VEX)

install: build
	mkdir $(PREFIX)
	cp $(VEX) $(PREFIX)/bin/

uninstall:
	rm -f $(PREFIX)/bin/$(VEX)
