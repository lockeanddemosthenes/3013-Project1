CC=gcc
CFLAGS=-I

boring: boring.o
    $(CC) -o boring boring.o

custom: custom.o
    $(CC) -o custom custom.o
    
multi: multi.o
    $(CC) -o multi multi.o