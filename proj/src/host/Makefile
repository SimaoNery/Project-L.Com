CC = gcc
CFLAGS = -g -Wall
LDFLAGS = -lmosquitto

all: HOST

HOST: mosquitto.c
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

clean:
	rm -f HOST
