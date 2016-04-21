;410C0 - ASM: MIO0Compress()?
;404C0 in RAM (0C010130 = JAL 404C0)
;Parameters:
;$a0 = source (not 100% sure)
;$a1 = data size
;$a2 = destination
;Returns:
;$v0 = size of compressed file

;--------------------------------------
;This section creates the header fields
;--------------------------------------

;This stores 'MIO0' at $a2, meaning $a2 is destination
lui $t0,'MI'
ori $t0,$t0,'O0'
sw $t0,0000($a2)

;This stores $a1 at ($a2 + 4), meaing $a1 is data size
lui $t0,8004
sw $a1,0004($a2)

addiu $t0,$t0,0170 ;$t0 = 80040170
lw $t3,0000($t0) ;Get $t3 from $t0 (0x80040170)

;This assigns $t8 to $a2 + 0x10, meaning $t8 is where
;the actual compressed data will be written
addi $t8,$a2,0010 ;$t8 = $a2 + 10

;Here, a few regs are ORed with 0
;ORing with 0 doesn't change the value
;so basically, 'or $xx,$yy,$zero' copies $yy into $xx
or $t4,$a0,$zero ;$t4 = $a0
or $t2,$zero,$zero ;$t2 = 0
or $t6,$zero,$zero ;$t6 = 0
or $a3,$t3,$zero ;$a3 = $t3
lbu $t0,0000($t4) ;Get byte to $t0 from $t4

410F4:
addi $t4,$t4,0001 ;$t4++
addi $t2,$t2,0001 ;$t2++
addi $t8,$t8,0001 ;$t8++
addiu $t1,$zero,0080 ;$t1 = 80

;This stores $t0 at ($t8 - 1)
;Since $t8 is the compression flags location plus one,
;this stores it at the first byte of the compression flags
sb $t0,FFFF($t8) ;Store byte to ($t8 - 1) from $t0
and $v0,$t0,$t1 ;$v0 = $t0 & $t1 ($t0 is a byte from $t4 (which is $a0 initially), $t1 is 0x80)

4110C:
beql $v0,$zero,41120 ;Go to 41120 if $v0 == 0
addi $$t6,$t6,0002 ;This is only executed if the above jump is taken
beq $zero,$zero,41124 ;Go to 41124

41118:
addi $t4,$t4,0001 ;$t4++
addi $t6,$t6,0002 ;$t6 += 2

41120:
addi $t4,$t4,0002 ;$t4 += 2 (This is only executed if ($t0 & $t1) != 0)

41124:
addi $t3,$t3,FFFF ;$t3--
beq $t3,$zero,41140 ;Go to 41140 if $t3 == 0 ($t3 is a word from 80040170, minus 1)
srl $t1,$1,01 ;$t1 = $t1 >> 1

;Now it compares a bit in $t0 with the current value of $t1
;$t1 starts at 0x80 and divides by 2, so this must be checking each bit
bnel $t1,$zero,4110C ;Go to 4110C if $t1 != 0
and $v0,$t0,$t1 ;$v0 = $t0 & $t1 (only if jump is taken)
;Notice that this is the same instruction as just before 4110C

;Or, if $t1 is 0...
beq $zero,$zero,410F4 ;Go back to here
lbu $t0,0000($t4) ;and get a byte from $t4 to $t0

;This occurrs when $t3 is 0
;$t3 is read from 80040170
;not sure what it does, but it seems to be used to determine the compressed data loc
41140:
addi $v0,$t2,0013 ;$v0 = $t2 + 13 ($t2 increments every time $t1 hits zero)
addiu $at,$zero,FFFC ;$at = -4
and $v0,$v0,$at ;Chop off the low 2 bits of $v0
sw $v0,0008($a2) ;Store at Compressed Data Loc field
add $v1,$a2,$v0 ;$v1 = Compressed data location in RAM
add $v0,$v0,$t6 ;$v0 += $t6
sw $v0,000C($a2) ;Store it at Raw Data Loc field
add $t9,$a2,$v0 ;$t9 = Raw data location in RAM

;$a0 = Source (Parameter)
;$a1 = Data size (Parameter)
;$a2 = Destination (Parameter)
;$v1 = Compressed data ptr
;$t8 = Compression flags ptr
;$t9 = Raw data ptr

41160:
lbu $t0,0000($a0) ;Get byte to $t0 from $a0

41164:
addi $a0,$a0,0001 ;$a0++
addiu $t1,$zero,0080 ;$t1 = 80
and $v0,$t0,$t1 ;See if this bit is set

41170:
beql $v0,$zero,41190 ;If not, go to 41190
lbu $v0,0001($a0) ;and get a byte from ($a0 + 1)
lbu $t5,0000($a0) ;Get the next byte
addi $a0,$a0,0001 ;$a0++
addi $t9,$t9,0001 ;(Raw data ptr)++
beq $zero,$zero,411A8 ;Go to 411A8
sb $t5,FFFF($t9) ;And store this byte in the raw data

4118C:
lbu $v0,0001($a0) ;Get byte to $v0 from ($a0 + 1)

41190:
lbu $t5,0000($a0) ;Get byte to $t5 from $a0
addi $v1,$v1,0002 ;Add 2 to compressed data ptr
sll $v0,$v0,8 ;Multiply $v0 by 0x100
or $v0,$v0,$t5 ;And add the other byte ($t5)
sh $v0,FFFE($v1) ;Store them 2 bytes before compressed data ptr
addi $a0,$a0,0002 ;$a0 += 2

411A8:
addi $a3,$a3,FFFF ;$a3-- (that byte from 80040170 again)
beq $a3,$zero,411C4 ;Go to 411C4 if $a3 == 0 (all done)
srl $t1,$t1,01 ;$t1 >> 1
bnel $t1,$zero,41170 ;Go to 41170 if $t1 != 0
and $v0,$t0,$t1 ;$v0 = $t0 & $t1 (check bits again)
beq $zero,$zero,41164 ;Go to 41164 (Next byte, reset $t1, check bits)
lbu $t0,0000($a0) ;And get a byte from $a0 to $t0

411C4:
jr $ra ;End of subroutine
sub $v0,$t9,$a2 ;$v0 = (raw data ptr) - (destination) ($v0 = total compressed file size)


;-------------------------------------
;This code calls the compress function
;Found at 51C4 in RAM
;Called from $9F3D0
;-------------------------------------

51C4:
lui $v0,8016
lh $v0,2D84($v0) ;Gets $v0 from somewhere
addiu $sp,$sp,FFE8 ;Subtract 0x18 from $sp
sw $ra,0014($sp) ;Push return address
beq $v0,$zero,521C ;Go to 521C if $v0 == 0
lui $a0,8016
sll $a1,$v0,02 ;$a1 = $v0 << 2
lui $a2,800E
lw $a2,C710($a2) ;Gets $a2 from somewhere
addiu $a1,$a1,0020 ;$a1 += 20
jal 40174 ;Call $40174
lw $a0,2D80($a0) ;Gets $a0 from somewhere

lui $a1,8016
lh $a1,2D84($a1) ;Gets $a1 from somewhere
lui $a0,800E
lui $a2,800E
sll $t6,$a1,02 ;$t6 = $a1 << 2
addiu $a1,$t6,0020 ;$a1 = $t6 + 20
lw $a2,C714($a2) ;Gets $a2 again
jal 404C0 ;Call MIO0Compress()
lw $a0,C710($a0) ;Gets $a0 again

addiu $v0,$v0,001E ;Add 0x1E (30) to compressed file size
lw $ra,0014($sp) ;Pull return address
addiu $sp,$sp,0018 ;Add 0x18 to $sp
jr $ra ;Return from subroutine
nop