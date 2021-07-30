# Makefile for Vex, the file manager inspired on NetRW from Vim

IN=$(shell find -iname '*.c')
OUT=vex
CFLAGS=-Og -std=c99 -Wall
CC=cc
PREFIX=/usr/local
DESKTOP_DIR=$(PREFIX)/share/applications
DESKTOP_FILE=vex.desktop

build:
	$(CC) $(IN) $(CFLAGS) $(LDFLAGS) -o $(OUT)

clean:
	rm $(OUT)

install: build
	mkdir -p $(PREFIX)/bin/
	cp $(OUT) $(PREFIX)/bin/

uninstall:
	rm -f $(PREFIX)/bin/$(OUT)

desktop: install
	echo "#!/usr/bin/env xdg-open" > $(DESKTOP_FILE)
	echo "Comment = A simple curses based terminal file manager." >> $(DESKTOP_FILE)
	echo "Type = Application" >> $(DESKTOP_FILE)
	echo "Exec = " $(PREFIX)/bin/$(OUT) >> $(DESKTOP_FILE)
	echo "Name = Vex" >> $(DESKTOP_FILE)
	cp $(DESKTOP_FILE) $(DESKTOP_DIR)
