CFLAGS = --std=c99 -Wall -pedantic $(shell pkg-config --cflags gtk+-3.0)
LIBS = $(shell pkg-config --libs gtk+-3.0)
TARGET = minesweeper-gtk
SRCS= src/minesweeper-gtk.c

all: $(TARGET)

$(TARGET):$(SRCS) libminesweeper/libminesweeper.a
	$(CC) $(CFLAGS) -o $@ $(SRCS) $(LIBS)

libminesweeper/libminesweeper.a:
	$(MAKE) -C libminesweeper

clean:
	$(MAKE) -C libminesweeper clean
	rm $(TARGET)

