CC = gcc
CCFLAGS = -O2 -g
SOURCES := $(wildcard *.c)
TARGET = $(SOURCES:.c=.bin)

all: $(TARGET)

%.bin:%.c
	$(CC) $(CCFLAGS) $< -o $@

clean:
	$(RM) -r *.bin


