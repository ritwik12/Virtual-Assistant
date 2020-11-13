CC = gcc
CFLAGS = -std=gnu11 -Isrc -Iutils `pkg-config --cflags libcurl`
LIBS = -lssl -lcrypto -ljson-c `pkg-config --libs libcurl`

ROOT_DIR = $(shell pwd)
BUILD_DIR = ./build
SRC_DIR = ./src
USR_BIN = /usr/bin

# Header file dependencies
DEPS = src/init_config.h utils/b64.h utils/defines.h

# Source file dependencies
SRCS_DEPS = $(shell find $(SRC_DIR) -name "*.c")

# Main Target: ./build/virtual_assistant
$(BUILD_DIR)/virtual_assistant: $(BUILD_DIR)/main.o $(BUILD_DIR)/init_config.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

# Rule: building main.o
$(BUILD_DIR)/main.o: main.c $(DEPS) $(SRCS_DEPS)
	mkdir -p $(dir $@)
	$(CC) -c -o $@ $< $(CFLAGS)

# Rule: building any build/*.o file from src/*.c file
$(BUILD_DIR)/%.o : $(SRC_DIR)/%.c $(DEPS) $(SRCS_DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: clean
# Install the binary
install:
	ln -sf $(ROOT_DIR)/$(BUILD_DIR)/virtual_assistant $(USR_BIN)/virtual_assistant
	ln -sf $(ROOT_DIR)/events.dat $(USR_BIN)/events.dat
	ln -sf $(ROOT_DIR)/config		$(USR_BIN)/config
	@echo "Installation Complete: run using virtual_assistant"

# Target: remove build dir
clean:
	rm -rf $(BUILD_DIR)
uninstall:	
	rm -rf $(USR_BIN)/virtual_assistant $(USR_BIN)/virtual_assistant $(USR_BIN)/config
