;CD64 memory test program
.CPU R4300
.symfile "mk64.sym"
.loadmacro loadreg
.loadmacro print
.loadmacro printnum
.loadmacro printconstnum

.define program_rom_addr 0xC00000
.define program_ram_addr 0xA0400000
.define program_size 0x800
.define cd64_enable_reg 0xB780000C
.define cd64_mode_reg 0xB7800000

;input
.define btn_c_right	0x0001
.define btn_c_left	0x0002
.define btn_c_down	0x0004
.define btn_c_up	0x0008
.define btn_r		0x0010
.define btn_l		0x0020
.define btn_right	0x0100
.define btn_left	0x0200
.define btn_down	0x0400
.define btn_up		0x0800
.define btn_start	0x1000
.define btn_z		0x2000
.define btn_b		0x4000
.define btn_a		0xa000

;======== patches ========
.seek 0x000688
NOP ;kill ROM checksum

.seek 0x20
.string "WTFHAX64"

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

.seek 0xC7FFFF
.byte 00 ;pad ROM


;======== menu program ========
.seek program_rom_addr
.org program_ram_addr

;text
dummy: .word 0 ;work around old emulator hack
str_title: .string "MEMORY TEST PROGRAM"
str_label: .string "ADDRESS\x20 DATA\x20\x20\x20\x20 LOOPNUM\x20"
str_buttons: .string "CU BYTE\x20 CR HWORD\x20  CD WORD"
str_read: .string "READ [CL]"
str_write: .string "WRITE"
str_cd64: .string "[Z] CD64 MODE"
str_cursor: .string "*"

;variables
.align 4
old_ra: .word 0
old_ra2: .word 0
text_xpos: .word 0
text_ypos: .word 0
frame_count: .word 0
cursor_pos: .word 0
mode: .word 0
cd64_mode: .word 0xFF
address: .word 0xB1000000
data: .word 0xFFFFFFFF
num_cycles: .word 1000000 ;how many times to read/write per button press
.word 0 ;not used yet, but cursor will scroll to this address

.define cursor_max 31
.define base $T9
.define x $A0
.define y $A1
.define str $A2

;code
print_at: ;(A0=X, A1=Y, A2=str)
SW $RA, ADDRLO(old_ra2)(base)
ADDIU x, x, -12 ;yeah I dunno
ADDIU y, y, -12
SW x, ADDRLO(text_xpos)(base)
SW y, ADDRLO(text_ypos)(base)
.store:
ADDIU x, base, ADDRLO(text_xpos)
JAL print_string
ADDIU y, base, ADDRLO(text_ypos)

LOADREG base, program_ram_addr
LW $RA, ADDRLO(old_ra2)(base)
JR $RA
NOP

print_num_at: ;(A0=X, A1=Y, A2=num, A3=base)
SW $RA, ADDRLO(old_ra2)(base)
SW x, ADDRLO(text_xpos)(base)
SW y, ADDRLO(text_ypos)(base)
.store:
ADDIU x, base, ADDRLO(text_xpos)
JAL print_number
ADDIU y, base, ADDRLO(text_ypos)

LOADREG base, program_ram_addr
LW $RA, ADDRLO(old_ra2)(base)
JR $RA
NOP



main:
LOADREG base, program_ram_addr
SW $RA, ADDRLO(old_ra)(base)

;reset title timer to a huge negative value, telling the loader that we've
;loaded. also, load the debug font.
LUI base, ADDRHI(title_demo_counter)
JAL load_debug_font
SW base, ADDRLO(title_demo_counter)(base)
LOADREG base, program_ram_addr

;enable CD64
ADDIU $A1, $zero, 0xFF
LW $A0, ADDRLO(cd64_mode)(base)
BNE $A0, $A1, .print

ADDIU $A1, $zero, 0x0A
LUI $A0, ADDRHI(cd64_enable_reg)
SW $A1, ADDRLO(cd64_enable_reg)($A0)
ADDIU $A1, $zero, 5
SW $A1, ADDRLO(cd64_mode)(base)

;print static text
.print:
print(8, 0, str_title)
print(8, 16, str_label)
print(8, 40, str_buttons)
print(24, 56, str_read)
print(24, 64, str_write)

;print mode cursor
LW y, ADDRLO(mode)(base)
SLL y, y, 3
ADDIU y, y, 56
ADDIU x, $zero, 16
JAL print_at
ADDIU str, base, ADDRLO(str_cursor)

;print CD64 mode
ADDIU x, $zero, 0
ADDIU y, $zero, 72
ADDIU str, base, ADDRLO(str_cd64)
JAL print_str_num
LW $A3, ADDRLO(cd64_mode)(base)
LOADREG base, program_ram_addr

;print address
LW $A2, ADDRLO(address)(base)
printnum(8, 40, 16)

;print data
LW $A2, ADDRLO(data)(base)
printnum(80, 40, 16)

;print loop count
LW $A2, ADDRLO(num_cycles)(base)
printnum(152, 40, 16)

;print cursor
LW x, ADDRLO(cursor_pos)(base)
SLL y, x, 3 ;mult by 8 (# pixels per digit)
;SRL x, x, 3 ;divide by 8 (# digits per var)
;SLL x, x, 3 ;mult by 8 (# pixels gap per var)
ANDI x, x, 0xFFF8
ADD y, y, x ;add that to xpos
ADDIU x, y, 8 ;add base xpos
ADDIU y, $zero, 24 ;set ypos
JAL print_at
ADDIU str, base, ADDRLO(str_cursor)


;read input
LW $A0, ADDRLO(frame_count)(base)
XORI $A0, $A0, 1
BEQ $A0, $zero, .process_input ;skip read to slow down
SW $A0, ADDRLO(frame_count)(base)

LUI $A0, ADDRHI(player1_buttons)
LH $A0, ADDRLO(player1_buttons)($A0)

.process_input:
ANDI $A1, $A0, btn_left
BNEL $A1, $zero, .left
LW $A0, ADDRLO(cursor_pos)(base)

ANDI $A1, $A0, btn_right
BNEL $A1, $zero, .right
LW $A0, ADDRLO(cursor_pos)(base)

ANDI $A1, $A0, btn_up
BNEL $A1, $zero, .up
LW $A0, ADDRLO(cursor_pos)(base)

ANDI $A1, $A0, btn_down
BNEL $A1, $zero, .down
LW $A0, ADDRLO(cursor_pos)(base)

ANDI $A1, $A0, btn_c_left
BNEL $A1, $zero, .mode
LW $A0, ADDRLO(mode)(base)

ANDI $A1, $A0, btn_c_up
BNEL $A1, $zero, .do_byte
LW $A0, ADDRLO(address)(base)

ANDI $A1, $A0, btn_c_right
BNEL $A1, $zero, .do_hword
LW $A0, ADDRLO(address)(base)

ANDI $A1, $A0, btn_c_down
BNEL $A1, $zero, .do_word
LW $A0, ADDRLO(address)(base)

ANDI $A1, $A0, btn_z
BNEL $A1, $zero, .set_cd64_mode
LW $A0, ADDRLO(cd64_mode)(base)


BEQ $zero, $zero, .end
NOP

.mode:
XORI $A0, $A0, 1
BEQ $zero, $zero, .end
SW $A0, ADDRLO(mode)(base)


.left:
ADDIU $A0, $A0, -1
ANDI $A0, $A0, cursor_max
BEQ $zero, $zero, .end
SW $A0, ADDRLO(cursor_pos)(base)

.right:
ADDIU $A0, $A0, 1
ANDI $A0, $A0, cursor_max
BEQ $zero, $zero, .end
SW $A0, ADDRLO(cursor_pos)(base)


.down:
BEQ $zero, $zero, .edit
ADDIU $AT, $zero, -1

.up:
ADDIU $AT, $zero, 1

.edit:
LOADREG $A1, address
SRL $A2, $A0, 1
ADDU $A1, $A1, $A2
LB $A3, 0000($A1)

;high nybble
ANDI $A2, $A0, 1
BEQL $A2, $zero, .write
SLL $AT, $AT, 4

.write:
ADD $A3, $A3, $AT
BEQ $zero, $zero, .end
SB $A3, 0000($A1)


.do_byte:
LW $A1, ADDRLO(mode)(base)
BNE $A1, $zero, .write_byte
LW $A3, ADDRLO(num_cycles)(base)

.read_byte_loop:
ADDIU $A3, $A3, -1
BNE $A3, $zero, .read_byte_loop
LB $AT, 0($A0)

BEQ $zero, $zero, .end
SB $AT, ADDRLO(data)(base)

.write_byte:
LB $AT, ADDRLO(data)(base)

.write_byte_loop:
ADDIU $A3, $A3, -1
BNE $A3, $zero, .write_byte_loop
SB $AT, 0($A0)

BEQ $zero, $zero, .end
NOP


.do_hword:
LW $A1, ADDRLO(mode)(base)
BNE $A1, $zero, .write_hword
LW $A3, ADDRLO(num_cycles)(base)

.read_hword_loop:
ADDIU $A3, $A3, -1
BNE $A3, $zero, .read_hword_loop
LH $AT, 0($A0)

BEQ $zero, $zero, .end
SH $AT, ADDRLO(data)(base)

.write_hword:
LH $AT, ADDRLO(data)(base)

.write_hword_loop:
ADDIU $A3, $A3, -1
BNE $A3, $zero, .write_hword_loop
SH $AT, 0($A0)

BEQ $zero, $zero, .end
NOP


.do_word:
LW $A1, ADDRLO(mode)(base)
BNE $A1, $zero, .write_word
LW $A3, ADDRLO(num_cycles)(base)

.read_word_loop:
ADDIU $A3, $A3, -1
BNE $A3, $zero, .read_word_loop
LW $AT, 0($A0)

BEQ $zero, $zero, .end
SW $AT, ADDRLO(data)(base)

.write_word:
LW $AT, ADDRLO(data)(base)

.write_word_loop:
ADDIU $A3, $A3, -1
BNE $A3, $zero, .write_word_loop
SW $AT, 0($A0)

BEQ $zero, $zero, .end
NOP


.set_cd64_mode:
ADDIU $A0, $A0, 1
ANDI $A0, $A0, 7
SW $A0, ADDRLO(cd64_mode)(base)

LOADREG $A1, cd64_mode_reg
ADDIU $A2, $zero, 0x0A
;don't do this here, it breaks shit. do it once at program start.
;SW $A2, 0xC($A1) ;CD64 enable
SW $A0, 0($A1) ;CD64 mode
;SW $A2, ADDRLO(address)(base)
;SW $A0, ADDRLO(data)(base) ;debug


;return
.end:
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

.printlabel main
