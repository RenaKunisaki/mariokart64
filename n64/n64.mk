TOOL=mips64-elf-
SRCDIR ?= src
BUILDDIR ?= build
BINDIR ?= bin
LINKSCRIPT ?= $(PROJECT)/$(PROJECT)-$(VERSION).ld

CC=$(TOOL)g++
AS=$(TOOL)as
AR=$(TOOL)ar
LD=$(TOOL)g++
NM=$(TOOL)nm
OBJCOPY=$(TOOL)objcopy
OBJDUMP=$(TOOL)objdump
READELF=$(TOOL)readelf
SIZE=$(TOOL)size
DELETE=rm -rf
MKDIR=mkdir -p

CFLAGS += -mips3 -mabi=32 -mlong32 -mxgot -mhard-float -G0 -O3  -I./n64/ -I./n64/ultra64/
ASFLAGS += -mips3 -mabi=32 -mhard-float -G0 -O3
LDFLAGS += -nostdlib -T$(LINKSCRIPT) -Wl,--nmagic -Wl,--no-gc-sections -Wl,--just-symbols=$(PROJECT)/$(PROJECT)-$(VERSION).sym

# function COMPILE(infile, outfile)
COMPILE=$(CC) $(CFLAGS) -c $1 -o $2

# function ASSEMBLE(infile, outfile)
ASSEMBLE=$(AS) $(ASFLAGS) $1 -o $2

# function LINK(infile, outfile)
LINK=$(CC) $1 $(LDFLAGS) -o $2

ELF=$(BINDIR)/$(PROJECT).elf
HEX=$(BINDIR)/$(PROJECT).hex
BIN=$(BINDIR)/$(PROJECT).bin
DIRS=$(BINDIR) $(BUILDDIR)

OBJS += n64/lib/64drive/64drive.o \
	n64/lib/libc/libc.o \
	n64/lib/rawio/rawio.o


.PHONY: all dirs clean patch run-emu run-ed64 run-64drive

all: $(ELF)
	@echo done

clean:
	$(DELETE) $(DIRS)
	$(shell find n64 -name *.o -delete)

patch: $(ELF)
	#$(OBJCOPY) -O binary -j PATCH $(ELF) $(BINDIR)/patches.bin
	#$(NM) -n $(ELF) | grep _patch_ > $(BINDIR)/patches.txt
	#$(NM) -S $(ELF) > $(BINDIR)/symbols.txt
	#$(OBJDUMP) -hw $(ELF) > $(BINDIR)/sections.txt
	cp $(INPUT) $(OUTPUT)
	#./patch.py bin/patched.rom bin $(ELF)
	n64/tools/patch.py $(ELF) $(OUTPUT)
	n64/tools/crc.py -v $(OUTPUT)

run-emu: patch
	mupen64plus --corelib ~/projects/emus/mupen64plus/mupen64plus-core/projects/unix/libmupen64plus.so.2 --emumode 0 $(OUTPUT)

run-ed64: patch
	n64/tools/loader64 -w -f bin/patched.rom
	n64/tools/loader64 -p

run-64drive: patch
	64drive -vvl bin/patched.rom

dirs:
	$(MKDIR) $(DIRS) $(dir $(OBJS))

#$(BIN): dirs $(ELF)
#	$(OBJCOPY) -O binary -j .text -j .data $(ELF) $@

$(ELF): dirs $(OBJS)
	$(call LINK, $(OBJS), $(ELF))

$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	$(call COMPILE, $<, $@)

$(BUILDDIR)/%.o: $(SRCDIR)/%.s
	$(call ASSEMBLE, $<, $@)

$(BUILDDIR)/lib/%.o: n64/lib/%.c
	$(call COMPILE, $<, $@)
