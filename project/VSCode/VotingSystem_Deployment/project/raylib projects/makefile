CC=gcc
CFLAGS=-Iinclude -Llib -lraylib -lopengl32 -lgdi32 -lwinmm -lkernel32 -luser32 -lshell32 -mwindows

SRC=src/vote.c
OUT=vote.exe   # <-- yahan name change kiya

all:
	$(CC) $(SRC) -o $(OUT) $(CFLAGS)
