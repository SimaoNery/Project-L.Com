CC = gcc
CFLAGS = -g -Wall
LIBS=-L/opt/homebrew/Cellar/mosquitto/2.0.18/lib -lmosquitto
INCLUDE_PATHI=-I/opt/homebrew/Cellar/mosquitto/2.0.18/include -I./Mosquitto -I./Socket


all: HOST

HOST: mosquitto.c
	$(CC) $(CFLAGS) $(INCLUDE_PATHI) -o $@ $< $(LIBS)

clean:
	rm -f HOST

