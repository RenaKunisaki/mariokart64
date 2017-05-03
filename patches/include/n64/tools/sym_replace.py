#!/usr/bin/env python3
# Read a symbol file and a source file.
# Replace symbol addresses with names in the source file.
# XXX does not handle addresses split into parts, like:
# lui $a0, xxxx
# ori $a0, xxxx
import sys

def readSyms(path):
    syms = {}
    with open(path) as file:
        while True:
            line = file.readline()
            if line == '': break
            line = line.split('=', 1)
            if len(line) != 2: continue
            name = line[0].strip()
            addr = line[1].strip()
            addr = addr.split(';')[0]
            syms[name] = addr
    return syms


def doReplace(syms, asmPath):
    with open(asmPath) as file:
        while True:
            line = file.readline()
            if line == '': break
            for name, addr in syms.items():
                line = line.replace(addr, name)
            print(line, end='')


def generateCodFile(syms):
    for name, addr in syms.items():
        print("0x%08X,%s" % (int(addr, 16), name))


def main(symPath, asmPath=None):
    syms = readSyms(symPath)
    #doReplace(syms, asmPath)
    generateCodFile(syms)


if __name__ == '__main__':
    sys.exit(main(*sys.argv[1:]))
