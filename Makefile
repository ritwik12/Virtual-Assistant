CC = gcc
CFLAGS = -std=gnu11 -Isrc -Iutils
LIBS = -lssl -lcrypto -ljson-c `pkg-config --libs libcurl`

BUILD_DIR = ./build
SRC_DIR = ./src

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

# Target: remove build dir
clean:
	rm -rf $(BUILD_DIR)
