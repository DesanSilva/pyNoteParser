CC = gcc

SRC = main.c $(wildcard src/*.c) 
OBJ = $(patsubst %.c, build/%.o, $(notdir $(SRC)))
TARGET = build/pyNoteParser

all: build $(TARGET)

build:
	mkdir -p build

# main.c object file
build/%.o: %.c
	$(CC) -c $< -o $@

# src/ directory files
build/%.o: src/%.c
	$(CC) -c $< -o $@

$(TARGET): $(OBJ)
	$(CC) $^ -o $@

run: $(TARGET)
	@./$(TARGET)

clean:
	rm -rf build
