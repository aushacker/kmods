CC=gcc
CFLAGS=-Wall

LDIR=/usr/lib
LIBS=-lcomedi

cclient: cclient.c
	$(CC) $(CFLAGS) cclient.c -L$(LDIR) $(LIBS) -o cclient

clean:
	-rm -f *.o cclient
