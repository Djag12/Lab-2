CC = gcc
CFLAGS = -Wall -g -std=c99  # Added -std=c99 to enable C99 standard

# Target to create the executable 'my3proc'
my3proc: main3.o
	$(CC) $(CFLAGS) -o my3proc main3.o

# Compile main3.c
main3.o: main3.c
	$(CC) $(CFLAGS) -c main3.c

# Clean up object files and executable
clean:
	rm -f *.o my3proc
