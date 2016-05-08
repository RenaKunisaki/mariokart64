;Mario Kart 64 title screen menu hack
;Assemble this into a ROM, then press R at the title screen. You should see
;"hello world" appear. You can use this as a base to make menus.
.CPU R4300
.symfile "mk64.sym"
.loadmacro loadreg

.define program_rom_addr 0xC00000
.define program_ram_addr 0xA0400000
.define program_size 0x800

;======== patches ========
.seek 0x000688
NOP ;kill ROM checksum

.seek 0x0A0574
.word 0x24050000 ;set box xpos

.seek 0x0A0546
.hword 0x0000 ;set box ypos

.seek 0x0A057E
.hword 0x00F8 ;set box end xpos

.seek 0x0A052E
.hword 0x00F0 ;set box end ypos

.seek 0x0A0533
.byte 0xCF ;set box opacity

.seek 0xC80000
.byte 00 ;pad ROM


;======== menu program ========
.align 4
.seek program_rom_addr
.org program_ram_addr

;variables
dummy: .word 0 ;work around old emulator hack
old_ra: .word 0
text_xpos: .word 0
text_ypos: .word 0

;text
str_hello: .string "HELLO WORLD"

.define base $T9
.define x $A0
.define y $A1
.define str $A2

;code
main:
LOADREG base, program_ram_addr
SW $RA, ADDRLO(old_ra)(base)

;reset title timer to a huge negative value, telling the loader that we've
;loaded. also, load the debug font.
LUI base, ADDRHI(title_demo_counter)
JAL load_debug_font
SW base, ADDRLO(title_demo_counter)(base)
LOADREG base, program_ram_addr

;reset text pos
LOADREG $A0, 0x10
SW $A0, ADDRLO(text_xpos)(base)
LOADREG $A0, 0x20
SW $A0, ADDRLO(text_ypos)(base)

;print some text
ADDIU x, base, ADDRLO(text_xpos)
ADDIU y, base, ADDRLO(text_ypos)
JAL print_string
ADDIU str, base, ADDRLO(str_hello)
LOADREG base, program_ram_addr

;return
LOADREG x, 0x8009FB1C
JR x
LW $RA, ADDRLO(old_ra)(base)

.undef base
.undef x
.undef y
.undef str


;======== bootstrap: load code from ROM ========
.seek 0xA0584
.org 0x8009F984
load:

.define src $A1
.define dest $T9
.define count $A0
.define tmp $A2

;check if title timer is positive (=routine hasn't loaded yet)
LUI dest, ADDRHI(title_demo_counter)
LW tmp, ADDRLO(title_demo_counter)(dest)
AND tmp, tmp, dest
BNE tmp, $zero, .run
NOP

;load code from ROM
LOADREG dest, program_ram_addr
ADDIU count, $zero, program_size
LOADREG src, @(rom_base + program_rom_addr)

.loop:
LW tmp, 0(src)
SW tmp, 0(dest)
ADDIU src, src, 4
ADDIU count, count, -4
BNE count, $zero, .loop
ADDIU dest, dest, 4

;quick hack to make numbers print unsigned
ADDIU tmp, $zero, 0x1000
LOADREG dest, print_number_sign_check
SH tmp, 0(dest)

;run the routine we loaded
.run:
LOADREG $T8, main
JR $T8
NOP

J 0x8009FB1C
NOP

.undef src
.undef dest
.undef count
.undef tmp

.print "Main:"
.printlabel main
