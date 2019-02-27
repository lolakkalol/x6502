CC=clang
COPTS=-o x6502 -O3 -lpthread -Wall -lncurses

all: release

release: *.c *.h
	$(CC) $(COPTS) *.c