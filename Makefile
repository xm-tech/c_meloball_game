src = game.c main.c

MYCFLAGS = -std=c11
CFLAGS = -W -Wall -Wextra -pedantic -g -O2 $(MYCFLAGS)

build:
	gcc $(CFLAGS) -o main $(src) -lpthread -lSDL2 -lSDL2main
run:
	chmod +x main
	./main

.PHONLY : clean

clean:
	- rm -f ./main && rm -rf ./main.dSYM
