MEMORY
{
    /* null: used for segments we don't need */
    null       (rwx) : ORIGIN = 0x00000000, LENGTH = 1M

    /* ROMFILE: used to refer to offsets in the ROM file itself */
    ROMFILE    (rwx) : ORIGIN = 0x00000000, LENGTH = 128M

    /* PATCH: same as ROMFILE, but our scripts read this section */
    PATCH      (rwx) : ORIGIN = 0x00000000, LENGTH = 128M

    /* rest are N64 memory space */
    RDRAM      (rwx) : ORIGIN = 0x00000000, LENGTH = 8M /* actual physical RAM */
    RDRAM_REGS (rw)  : ORIGIN = 0x03F00000, LENGTH = 1M /* RAM control registers */
    SP         (rw)  : ORIGIN = 0x04000000, LENGTH = 1M
    DPCMD      (rw)  : ORIGIN = 0x04100000, LENGTH = 1M
    DPSPAN     (rw)  : ORIGIN = 0x04200000, LENGTH = 1M
    MI         (rw)  : ORIGIN = 0x04300000, LENGTH = 1M
    VI         (rw)  : ORIGIN = 0x04400000, LENGTH = 1M
    AI         (rw)  : ORIGIN = 0x04500000, LENGTH = 1M
    PI         (rw)  : ORIGIN = 0x04600000, LENGTH = 1M
    RI         (rw)  : ORIGIN = 0x04700000, LENGTH = 1M
    SI         (rw)  : ORIGIN = 0x04800000, LENGTH = 1M
    N64DD      (rwx) : ORIGIN = 0x05000000, LENGTH = 48M
    CART       (rwx) : ORIGIN = 0x10000000, LENGTH = 252M
    PIFROM     (rw)  : ORIGIN = 0x1FC00000, LENGTH = 0x7C0
    PIFRAM     (rw)  : ORIGIN = 0x1FC007C0, LENGTH = 0x40
    RAM        (rwx) : ORIGIN = 0x80000000, LENGTH = 8M /* most games map RAM here */
    KSEG0      (rwx) : ORIGIN = 0x80000000, LENGTH = 8M
    KSEG1      (rwx) : ORIGIN = 0xA0000000, LENGTH = 8M /* uncached RAM mirror */
    ROM        (rwx) : ORIGIN = 0xB0000000, LENGTH = 256M /* games map ROM here */
    KSSEG      (rwx) : ORIGIN = 0xC0000000, LENGTH = 8M
    KSEG3      (rwx) : ORIGIN = 0xE0000000, LENGTH = 8M
}
