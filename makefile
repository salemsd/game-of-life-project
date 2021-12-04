# Projet
.PHONY: all dist docs clean

CC = gcc
CFLAGS += -g -Wall
CPPFLAGS += -Iinclude -I/usr/include/cairo
LDFLAGS += -lcairo -lm -lX11

BIN_DIR = bin
TARGET = $(BIN_DIR)/main

vpath %.c src/
vpath %.h include/

OBJ_DIR = obj/
OBJ = $(patsubst ./src/%.c,%.o,$(wildcard ./src/*.c))

# Gestion du mode
MODE = GRAPHIQUE# Graphique par défaut
# Définit l'expression GRAPHIQUE ou TEXTE selon la valeur de la variable
MODEFLAGS = -D$(MODE)

all: $(TARGET) 

$(TARGET): $(addprefix $(OBJ_DIR),$(OBJ))
	mkdir -p $(BIN_DIR)
	$(CC) $(MODEFLAGS) $(CPPFLAGS) $(CFLAGS) -o $@ $^ $(LDFLAGS) 
	@echo "\nUsage: ./bin/main grilles/grille<num>.txt\n"
$(OBJ_DIR)%.o: %.c | $(OBJ_DIR)
	$(CC) $(MODEFLAGS) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<
$(OBJ_DIR):
	mkdir -p $@	
	
dist:
	mkdir -p $@
	tar -Jcvf dist/SaoudiSalem-GoL-4.0.tar.xz Doxyfile makefile src/ include/

docs:
	@doxygen ./Doxyfile

clean:
	$(RM) -r doc/ dist/ $(OBJ_DIR) $(BIN_DIR)/
