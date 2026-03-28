CC = gcc

CFLAGS = -Wall -O2 -Iinclude
SRC = $(wildcard src/*.c) 
OBJ = $(patsubst %.c, build/obj/%.o, $(notdir $(SRC)))
BIN = build/pyNoteParser

all: $(BIN)

$(BIN): $(OBJ)
	mkdir -p build
	$(CC) $(CFLAGS) -o $@ $^

build/obj/%.o: src/%.c
	mkdir -p build/obj
	$(CC) $(CFLAGS) -c $< -o $@

run: $(BIN)
	@./$(BIN)

clean:
	rm -rf build
