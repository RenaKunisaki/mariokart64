/*
Function at 800400D0 is void DecompressMIO0(void* Data, void* Buffer) - Data points to MIO0 data, Buffer points to

address to decompress to.

Called from 802AA8E8. $A0 = 80280460, $A1 = 801CCB00
At 80280460 is an MIO0 file found at 872A00 in ROM - Rainbow Road's RSP file.

800400D0:
00F0: BNEL $A2, $zero, 80040108
00F4: SLT $T1, $T0, $zero
00F8: LW $T0, 0000($A0)
00FC: ADDIU $A2, $zero, 0020
0100: ADDI $A0, $A0, 0004
0104: SLT $T1, $T0, $zero

0108: BEQL $T1, $zero, 80040128
010C: LHU $T2, 0000($A3)
0110: LB $T2, 0000($T9) ;get byte from file
0114: ADDI $T9, $T9, 0001
0118: ADDI $A1, $A1, 0001
011C: BEQ $zero, $zero, 80040154
0120: SB $T2, FFFF($A1)

0124: LHU $T2, 0000($A3)

0128: ADDI $A3, $A3, 0002
012C: SRL $T3, $T2, 000C
0130: ANDI $T2, $T2, 0FFF
0134: SUB $T1, $A1, $T2
0138: ADDI $T3, $T3, 0003
013C: LB $T2, FFFF($T1)
0140: ADDI $T3, $T3, FFFF
0144: ADDI $T1, $T1, 0001
0148: ADDI $A1, $A1, 0001
014C: BNEZ $T3, 8004013C
0150: SB $T2, FFFF($A1) ;store byte read from file

0154: SLL $T0, $T0, 0001
0158: BNE $A1, $T8, 800400F0
015C: ADDI $A2, $A2, FFFF
0160: JR $RA
0164: NOP

ID
OutputSize
CompLoc
RawLoc
*/

/*
Decompiled from Mario Kart 64 (800400D0 in RAM)
Decompresses an MIO0 file.
Inputs:
	-Data: Pointer to compressed data.
	-Buffer: Pointer to buffer to place decompressed data in.
Notes:
	-Code may not actually compile due to treating pointers as integers, should
	 be easily fixed though if you need it. Also in some cases things like this
	 happen:
	 Data++;
	 something = Data[-1];
	 This is what the game does, but if the compiler rejects it, you can just
	 switch the order of these instructions and access Data[0].
	-This is not optimized, it's chewed-and-spewed code decompiled by hand.
*/
void DecompressMIO0(u8* Data, u8* Buffer)
{
	u16* CompData; //$A3
	u8* RawData; //$T9
	u32 OutputSize; //$T8
	u32 BitCount; //$A2
	u32 Flag, Temp, T2, Count; //$T0, $T1, $T2, $T3

	//Read MIO0 header.
	//Note: game doesn't care about "MIO0" string at all.
	CompData = Data[8];
	RawData = Data[0xC];
	OutputSize = Data[4];

	//Adjust pointers to be absolute
	CompData += Data;
	RawData += Data;

	BitCount = 0;
	Data += 0x10; //move past the header
	OutputSize += Buffer;

	while(Buffer != OutputSize)
	{
		if(!BitCount)
		{
			Flag = (u32*)Data[0];
			BitCount += 32;
			Data += 4;
		}
		Temp = (Flag < 0); //Test high bit

		if(Temp) //Raw data
		{
			T2 = RawData[0];
			RawData++;
			Buffer++;
			Buffer[-1] = T2; //if this is even valid
		}
		//Redundant instruction never executed? T2 = CompData[0];
		else //Compressed data
		{
			T2 = CompData[0];
			CompData++; //+2 bytes, but it's u16* so only +1 here
			Count = T2 >> 0xC; //bytes to copy
			T2 &= 0xFFF; //offset to copy from
			Temp = Buffer - T2;
			Count += 3;

			while(Count != 0)
			{
				T2 = (u8*)Temp[-1];
				Count -= 1;
				Temp++;
				Buffer++;
				Buffer[-1] = T2;
			}
		} //if compressed

		Flag <<= 1;
		BitCount--;
	} //while
}