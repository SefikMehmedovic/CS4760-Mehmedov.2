#
#compiler: gcc for C
CC = gcc

CFLAGS = -g -Wall

objects = master worker
all: $(objects)

$(objects): %: %.c
	$(CC) $(CFLAGS) -o $@ $< 

clean:
	rm $(objects)
