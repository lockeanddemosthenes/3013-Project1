CC=gcc
CFLAGS=-I

boring: boring.c
	$(CC) -o boring boring.o

custom: custom.c
	$(CC) -o custom custom.o
    
multi: multi.c
	$(CC) -o multi multi.o

all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean
