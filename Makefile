TARGET = build/example.out

CC = gcc
CFLAGS = -g -O0 -Wall -Wextra -std=c99

SOURCES = example.c
OBJECTS = $(patsubst %.c,build/%.o,$(SOURCES))

all: $(TARGET)

$(TARGET): $(OBJECTS) | build
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)

build/%.o: %.c | build
	$(CC) $(CFLAGS) -c $< -o $@

build:
	mkdir -p build

clean:
	rm -rf build

run:
	./$(TARGET)
