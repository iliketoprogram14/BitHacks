#
# Makefile
#
# Randy Miller
# Bit Hacks
#

CC = gcc
CFLAGS = -ggdb -std=c99 -Wall -Werror
SOURCES = main.c abs.c binary_search.c highest_pow2.c log10.c log2.c minmax.c negate.c opp.c parity.c pow2.c setclear.c sign.c swap.c main.h
OBJECTS = $(SOURCES:.c = .o)
EXECUTABLES = bit_hacks

all: $(SOURCES) $(EXECUTABLES)
#bit_hacks: $(SOURCES)

#$(OBJECTS) : main.h

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f *.o a.out *.exe *\~

