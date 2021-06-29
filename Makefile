# Makefile for Vex, the file manager inspired on NetRW from Vim

IN=main.c
VEX=vex
CFLAGS=-Og -ansi -Wall
LDFLAGS=-lncursesw
CC=cc
PREFIX=/usr/local
DESKTOP_DIR=${HOME}/Desktop
DESKTOP_FILE=Vex.desktop
INTEGRATION_DIR=/usr/share/applications
BIN_DIR=/usr/bin

build:
	$(CC) $(IN) $(CFLAGS) $(LDFLAGS) -o $(VEX)

clean:
	rm $(VEX)

install: build
	mkdir $(PREFIX)
	cp $(VEX) $(PREFIX)/bin/

uninstall:
	rm -f $(PREFIX)/bin/$(VEX)

desktop:
	touch $(DESKTOP_FILE)
	echo "#!/usr/bin/env xdg-open" >> $(DESKTOP_FILE)
	echo "Comment=A simple terminal based file manager." >> $(DESKTOP_FILE)
	echo "Type=Application" >> $(DESKTOP_FILE)
	echo "Exec=/usr/local/vex" >> $(DESKTOP_FILE)
	echo "Name=Vex" >> $(DESKTOP_FILE)
	cp $(DESKTOP_FILE) $(DESKTOP_DIR)
	
integrate:
	cp $(DESKTOP_FILE) $(INTEGRATION_DIR)
	cp $(DESKTOP_FILE) $(BIN_DIR)
	
