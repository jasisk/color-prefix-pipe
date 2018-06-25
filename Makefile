CC = clang
CFLAGS = -Oz
TARGET = precolor
SRCS = $(TARGET).c

PANDOC = pandoc

.PHONY: all clean man

all: $(TARGET) man

$(TARGET): $(SRCS:.c=.o)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

man: $(TARGET).1

$(TARGET).1: README.md
	$(PANDOC) --standalone --to man $< -o $@

clean:
	$(RM) $(TARGET) $(TARGET).1 $(SRCS:.c=.o)
# DO NOT DELETE
