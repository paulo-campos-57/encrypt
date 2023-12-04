all: main.c
	gcc -o encrypt main.c library.c

clean:
	rm encrypt