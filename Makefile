#
#   Copyright (c) 2023-2024 | Mihai Zegheru | 312CAb
#

CC=gcc
CFLAGS=-Wall -Wextra -std=c99

BUILD_DIR=build
SRC_DIR=src

EXE=image_editor
SOURCES+=$(wildcard $(SRC_DIR)/*.c)
HEADERS+= $(addprefix -I,$(wildcard $(SRC_DIR)))

.PHONY: build
build:
	$(CC) $(CFLAGS) $(SOURCES) $(HEADERS) -o $(BUILD_DIR)/$(EXE)

pack:
	zip -FSr 312CA_ZegheruMihai_Tema3.zip $(SOURCES) $(HEADERS) $(EXTRAS)

clean:
	rm $(BUILD_DIR)/$(EXE)
