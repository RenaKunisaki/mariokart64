TOOL=mips64-elf-
SRCDIR ?= src
BUILDDIR ?= build
BINDIR ?= bin
LINKSCRIPT ?= include/$(PROJECT)/$(PROJECT)-$(VERSION).ld

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

N64BASE=include/n64
PROJBASE=include/$(PROJECT)

CFLAGS += -mips3 -mabi=32 -mlong32 -mxgot -mhard-float -G0 -O3  -I$(N64BASE) -I$(N64BASE)/ultra64/
ASFLAGS += -mips3 -mabi=32 -mhard-float -G0 -O3
LDFLAGS += -nostdlib -T$(LINKSCRIPT) -Wl,--nmagic -Wl,--no-gc-sections -Wl,--just-symbols=$(PROJBASE)/$(PROJECT)-$(VERSION).sym

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

OBJS += $(N64BASE)/lib/64drive/64drive.o \
	$(N64BASE)/lib/libc/libc.o \
	$(N64BASE)/lib/rawio/rawio.o


.PHONY: all dirs clean patch run-emu run-ed64 run-64drive

all: $(ELF)
	@echo done

clean:
	$(DELETE) $(DIRS)
	$(shell find $(N64BASE) -name *.o -delete)

patch: $(ELF)
	#$(OBJCOPY) -O binary -j PATCH $(ELF) $(BINDIR)/patches.bin
	#$(NM) -n $(ELF) | grep _patch_ > $(BINDIR)/patches.txt
	#$(NM) -S $(ELF) > $(BINDIR)/symbols.txt
	#$(OBJDUMP) -hw $(ELF) > $(BINDIR)/sections.txt
	cp $(INPUT) $(OUTPUT)
	#./patch.py bin/patched.rom bin $(ELF)
	$(N64BASE)/tools/patch.py $(ELF) $(OUTPUT)
	$(N64BASE)/tools/crc.py -v $(OUTPUT)

run-emu: patch
	mupen64plus --corelib ~/projects/emus/mupen64plus/mupen64plus-core/projects/unix/libmupen64plus.so.2 --emumode 0 $(OUTPUT)

run-ed64: patch
	$(N64BASE)/tools/loader64 -w -f bin/patched.rom
	$(N64BASE)/tools/loader64 -p

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
