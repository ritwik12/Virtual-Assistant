CC=gcc
CFLAGS=$(pkg-config --libs --cflags libcurl) -lssl -lcrypto -ljson-c -std=gnu11
INCLUDE = -I/usr/local/include
LDFLAGS = -L/usr/local/lib
LDLIBS = -lcurl -lssl -lcrypto -ljson-c

DEPS = functions.h defines.h
OBJ = main.o \
	  analysis.o \
	  decode.o \
	  email.o \
	  init_config.o \
	  requests.o \
	  response.o \
	  ssl.o \
	  functions.o \

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

hellomake: $(OBJ)
	$(CC) -o $@ $^ $(INCLUDE) $(LDFLAGS) $(LDLIBS)
