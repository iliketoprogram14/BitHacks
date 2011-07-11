#
# Makefile
#
# Randy Miller
# Bit Hacks
#

CC = gcc
CFLAGS = -ggdb -std=c99 -Wall -Werror
SOURCES = main.c abs.c binary_search.c bits_set.c highest_pow2.c log10.c log2.c minmax.c mod_div.c negate.c next_highest_pow2.c opp.c parity.c pow2.c rev_seq.c setclear.c sign.c swap.c test_range.c trailing.c
DEPS = main.h
OBJECTS = $(SOURCES:.c = .o)
EXECUTABLES = bit_hacks

all: $(SOURCES) $(EXECUTABLES)
bit_hacks: $(SOURCES)

$(EXECUTABLES): $(OBJECTS)
	$(CC) $(CFLAGS) $(DEPS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f *.o a.out *.exe *\~

