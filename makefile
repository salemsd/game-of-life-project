# Projet
.PHONY: all dist docs clean

# flags
CC = gcc
CFLAGS += -g -Wall
CPPFLAGS += -Iinclude -I/usr/include/cairo
LDFLAGS += -lcairo -lm -lX11

# executable
BIN_DIR = bin
TARGET = $(BIN_DIR)/main

# chemins
vpath %.c src/
vpath %.h include/

# .o
OBJ_DIR = obj/
OBJ = $(patsubst ./src/%.c,%.o,$(wildcard ./src/*.c))

# librairie
LIB_DIR = lib
LIB = $(LIB_DIR)/libjeu.a

# Gestion du mode
MODE = GRAPHIQUE# Graphique par défaut
# Définit l'expression GRAPHIQUE ou TEXTE selon la valeur de la variable
MODEFLAGS = -D$(MODE)

all: $(TARGET) 

$(LIB): $(OBJ_DIR)jeu.o $(OBJ_DIR)grille.o
	mkdir -p $(LIB_DIR)
	ar rcv $(LIB) $^
	ranlib $(LIB)
$(TARGET): $(OBJ_DIR)main.o $(OBJ_DIR)io.o $(LIB) 
	mkdir -p $(BIN_DIR)
	$(CC) $(MODEFLAGS) $(CPPFLAGS) $(CFLAGS) -o $@ $^ -ljeu -L$(LIB_DIR) $(LDFLAGS) 
	@echo "\nUsage: ./bin/main grilles/grille<num>.txt\n"
$(OBJ_DIR)%.o: %.c | $(OBJ_DIR)
	$(CC) $(MODEFLAGS) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<
$(OBJ_DIR):
	mkdir -p $@	
	
dist:
	mkdir -p $@
	tar -Jcvf dist/GoL-5.1.tar.xz Doxyfile makefile src/ include/ grilles/

docs:
	@doxygen ./Doxyfile

clean:
	$(RM) -r doc/ dist/ $(OBJ_DIR) $(BIN_DIR)/ $(LIB_DIR)/
