#
#   Copyright (c) 2023-2024 | Mihai Zegheru | 312CAb
#

CC=gcc
CFLAGS=-Wall -Wextra -std=c99

BUILD_DIR=build
SRC_DIR=src

SOURCES=$(SRC_DIR)/main.c\

EXE=image_editor

.PHONY: build
build:
	$(CC) $(CFLAG) $(SOURCES) -o $(BUILD_DIR)/$(EXE)

pack:
	zip -FSr 312CA_ZegheruMihai_Tema3.zip $(SOURCES) $(HEADERS) $(EXTRAS)

clean:
	rm $(BUILD_DIR)/$(EXE)
