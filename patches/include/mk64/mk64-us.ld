INCLUDE include/n64/n64.ld

PATCH_ROM_ADDR = 0x3034;
PATCH_RAM_ADDR = 0x80002434;
LOADER_ROM_ADDR = 0xC00000;
LOADER_RAM_ADDR = 0x80400000;
LOADER_READ_ADDR = LOADER_ROM_ADDR | 0xB0000000;

PHDRS
{
    /* these have to be PT_SHLIB or else the VMA becomes zero
     * because reasons.
     * or PT_DYNAMIC but then readelf barfs since that's not
     * what PT_DYNAMIC is for.
     * it SHOULD be PT_LOAD (which might also kill the "not in segment"
     * warning) but that doesn't work.
     */
    bootstrap PT_SHLIB AT(PATCH_ROM_ADDR) ;
    text      PT_SHLIB AT(LOADER_ROM_ADDR) ;
}

SECTIONS
{
    . = PATCH_RAM_ADDR;
    .bootstrap . : { KEEP(*(.bootstrap)); } AT>RAM :bootstrap

    . = LOADER_RAM_ADDR;
    .text . : {
        _stext = .;
        *(.text);
        *(.*data*);
        _etext = .;
        _ltext = _etext - _stext;
    } AT>RAM :text

    /* .data . : { _sdata = . ; *(.*data); _edata = . ; } */

    .bss  . : {
        _sbss  = .;
        *(.bss);
         _ebss  = . ;
         _lbss = _ebss - _sbss;
    }

    /* get these out of the way */
    .junk . : {
        *(.reginfo) *(.gnu.*) *(.MIPS.*)
    } :NONE
}
