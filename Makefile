IDIR =./
CC = gcc
CFLAGS = -I$(IDIR) -std=gnu11 `pkg-config --cflags libcurl`

ODIR = obj
LDIR = ../lib
LIBS = -lssl -lcrypto -ljson-c  `pkg-config --libs libcurl`

_DEPS = defines.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

all: virtual_assistant

$(ODIR)/%.o: %.c $(DEPS)
	$(MKDIR_P) $(dir $@)
	$(CC) -c -o $@ $< $(CFLAGS)

virtual_assistant: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 

MKDIR_P ?= mkdir -p
