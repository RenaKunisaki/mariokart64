//PI (Peripheral Interface) registers
typedef struct {
    volatile void *ram_addr; //uncached RAM address of data
    volatile u32 pi_addr;    //peripheral address
    volatile u32 read_len;   //transfer length RAM -> periph
    volatile u32 write_len;  //transfer length RAM <- periph
    volatile u32 status;
} pi_regs_s; //at 0xA4600000
