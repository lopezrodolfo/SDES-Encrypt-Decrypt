CC=gcc
CFLAGS=-g -Wall -Wextra -std=c11

TARGETS=sdes-encrypt sdes-decrypt 
SDES_LIB=simplified_des.o

all: $(TARGETS)

sdes-encrypt: sdes-encrypt.c $(SDES_LIB)
	$(CC) $(CFLAGS) -o $@ $^

sdes-decrypt: sdes-decrypt.c $(SDES_LIB)
	$(CC) $(CFLAGS) -o $@ $^

$(SDES_LIB): simplified_des.c simplified_des.h
	$(CC) -c $(CFLAGS) $<

clean:
	$(RM) $(TARGETS) $(SDES_LIB)
