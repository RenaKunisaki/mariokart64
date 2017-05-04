PROJECT=mk64
INPUT=../../mk64.rom
OUTPUT=bin/patched.rom
VERSION=us
ASFLAGS ?= --defsym .text=0x80400000

# bootstrap.o has to come first so that bootstrap is at 0x80400000
OBJS=$(BUILDDIR)/bootstrap.o $(BUILDDIR)/lib.o $(BUILDDIR)/hooks.o
include include/n64/n64.mk
