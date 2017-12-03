EXTRA_DIST=         \
	help.txt						\
	config						 	\
	README.md         	\
	LICENSE

bin_PROGRAMS=virtual_assistant
AM_CFLAGS= -std=gnu11 -Wall -I/usr/include/json-c -I/usr/include/json

virtual_assistant_SOURCES = main.c

virtual_assistant_LDFLAGS = -lcurl

PACKAGE = @PACKAGE@
VERSION = @VERSION@

ACLOCAL = true
AUTOCONF = true
AUTOHEADER = true
AUTOMAKE = true

# ACLOCAL_AMFLAGS = --install -I m4

distdir = $(PACKAGE)-$(VERSION)
