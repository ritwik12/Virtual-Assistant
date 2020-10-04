CC = gcc
CFLAGS = -std=gnu11 -Isrc -Iutils
LIBS = -lssl -lcrypto -ljson-c `pkg-config --libs libcurl`

BUILD_DIR = ./build
DEPS = main.c src/init_config.c

$(BUILD_DIR)/virtual_assistant: $(DEPS)
	mkdir -p $(dir $@)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

clean:
	rm -rf $(BUILD_DIR)