# Projet
.PHONY: all dist docs clean

CC = gcc
CFLAGS += -g -Wall
CPPFLAGS += -I include

BIN_DIR = bin
TARGET = $(BIN_DIR)/main

vpath %.c src/
vpath %.h include/

OBJ_DIR = obj/
OBJ = $(patsubst ./src/%.c,%.o,$(wildcard ./src/*.c))


all: $(TARGET) 

$(TARGET): $(addprefix $(OBJ_DIR),$(OBJ))
	mkdir $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^
$(OBJ_DIR)%.o: %.c | $(OBJ_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<
$(OBJ_DIR):
	mkdir $@	
	
dist:
	tar -Jcvf SaoudiSalem-GoL-3.0.tar.xz Doxyfile makefile src/ include/

docs:
	@doxygen ./Doxyfile

clean:
	$(RM) -r doc/ $(OBJ_DIR) bin/
