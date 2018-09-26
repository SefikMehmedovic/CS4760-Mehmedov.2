#
#compiler: gcc for C
CC = gcc

CFLAGS = -g -Wall -std=c99

objects = master worker
all: $(objects)

$(objects): %: %.c
	$(CC) $(CFLAGS) -o $@ $< 

clean:
	rm $(objects)
