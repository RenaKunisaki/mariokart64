#!/usr/bin/env python3
# Program to correct N64 ROM header CRCs.
# ported from http://n64dev.org/n64crc.html
# original copyright notice follows:

# Mar 23, 2010: addition by spinout to actually fix CRC if it is incorrect
#
# Copyright notice for this file:
#  Copyright (C) 2005 Parasyte
#
# Based on uCON64's N64 checksum algorithm by Andreas Sterbenz
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

import argparse
import sys
import struct
from binascii import crc32


cic_checksums = { # bootcode checksum => CIC
    0x6170A4A1: 6101,
	0x90BB6CB5: 6102,
	0x0B050EE0: 6103,
    # there is no 6104 CIC
	0x98BC2C86: 6105,
	0xACC8580A: 6106,
}

cic_seeds = { # CIC => initial checksum seed
    6101: 0xF8CA4DDC,
    6102: 0xF8CA4DDC, # same as 6101
    6103: 0xA3886759,
    6105: 0xDF26F436,
    6106: 0x1FEA617A,
}

def ROL(i, b):
    x = (i << b) & 0xFFFFFFFF
    y = (i >> (32 - b)) & 0xFFFFFFFF
    return x | y


def printf(fmt, *args):
    print(fmt % args, end='')


verbose = 0
def printvf(vb, fmt, *args):
    if verbose >= vb: printf(fmt, *args)


def getArgs():
    parser = argparse.ArgumentParser(
        description="Verify and/or correct N64 ROM header CRC.",
        epilog="With -c, exit code is 0 if checksum is correct, 1 if not."
    )
    parser.add_argument('--verbose', '-v', action='count', default=0,
        help="Print more details.")
    parser.add_argument('--check', '-c', action='store_true',
        help="Only check, do not write to file.")
    parser.add_argument('file', type=str,
        help="ROM file in v64 format (ABCD byte order).")

    return parser.parse_args()


def readBootCode(file):
    file.seek(0x40, 0)
    bootcode = file.read(0x1000 - 0x40)
    bootchk  = crc32(bootcode)
    cic      = cic_checksums.get(bootchk, 'unknown')
    printvf(1, "CIC: %s (bootcode crc32: %08X)\n", cic, bootchk)
    return cic


def readCRC(file):
    file.seek(0x10)
    rom_crc = struct.unpack('>II', file.read(8))
    printvf(1, "ROM: %08X %08X\n", *rom_crc)
    return rom_crc


def writeCRC(file, crc):
    file.seek(0x10)
    file.write(struct.pack('>II', crc[0], crc[1]))


def computeCRC(file, cic):
    file.seek(0x1000, 0)
    data = file.read(0x100000)
    seed = cic_seeds.get(cic, 1)

    t1, t2, t3, t4, t5, t6 = seed, seed, seed, seed, seed, seed
    for word in struct.iter_unpack('>I', data):
        # ick, decompiled code
        word = word[0]
        if ((t6 + word) & 0xFFFFFFFF) < t6: t4 += 1
        t6 = (t6 + word) & 0xFFFFFFFF
        t3 ^= word
        r = ROL(word, word & 0x1F)
        t5 = (t5 + r) & 0xFFFFFFFF
        if t2 > word: t2 ^= r
        else: t2 ^= t6 ^ word
        if cic == 6105:
            raise NotImplementedError # XXX
        else:
            t1 = (t1 + (t5 ^ word)) & 0xFFFFFFFF
    if cic == 6103:
        crc = (
            ((t6 ^ t4) + t3) & 0xFFFFFFFF,
            ((t5 ^ t2) + t1) & 0xFFFFFFFF,
        )
    elif cic == 6016:
        crc = (
            ((t6 * t4) + t3) & 0xFFFFFFFF,
            ((t5 * t2) + t1) & 0xFFFFFFFF,
        )
    else:
        crc = (
            t6 ^ t4 ^ t3,
            t5 ^ t2 ^ t1,
        )
    printvf(1, "CRC: %08X %08X\n", *crc)
    return crc


def main():
    global verbose
    args = getArgs()
    verbose = args.verbose
    onlyCheck = args.check

    if onlyCheck: mode = 'rb'
    else: mode = 'r+b'
    with open(args.file, mode) as file:
        cic = readBootCode(file)
        crc = computeCRC(file, cic)
        rom_crc = readCRC(file)

        if rom_crc[0] != crc[0] or rom_crc[1] != crc[1]:
            if onlyCheck:
                printvf(1, "Checksum: FAIL\n")
                return 1
            else:
                writeCRC(file, crc)
                printvf(1, "Corrected checksum in header.\n")
                return 0
        else:
            printvf(1, "Checksum: OK\n")
            return 0


if __name__ == '__main__':
    sys.exit(main())
