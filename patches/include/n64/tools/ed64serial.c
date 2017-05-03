//gcc -Wall -Wextra -lftdi1 ed64serial.c -o ed64serial
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#include <libftdi1/ftdi.h>

#define USB_VENDOR 0x0403
#define USB_DEVICE 0x6001
#define USB_READ_TIMEOUT 500
#define USB_WRITE_TIMEOUT 500


struct ftdi_context* init_ftdi() {
    struct ftdi_context *ftdi;
    if((ftdi = ftdi_new()) == 0) {
        fprintf(stderr, "ftdi_new failed\n");
        return NULL;
    }

    int err;
    if((err = ftdi_usb_open(ftdi, USB_VENDOR, USB_DEVICE)) < 0) {
        fprintf(stderr, "unable to open ftdi device: %d (%s)\n", err,
            ftdi_get_error_string(ftdi));
        ftdi_free(ftdi);
        return NULL;
    }

	//read/write timeout e.g. 500ms
    ftdi->usb_read_timeout = USB_READ_TIMEOUT;
	ftdi->usb_write_timeout = USB_WRITE_TIMEOUT;
    return ftdi;
}


int do_test(struct ftdi_context *ftdi) {
    unsigned char send_buff[512];
    unsigned char recv_buff[512];

    memset(send_buff, 0, 512);
    memset(recv_buff, 0, 512);

    send_buff[0]='C';
    send_buff[1]='M';
    send_buff[2]='D';
    send_buff[3]='T'; //test

    int r = ftdi_write_data(ftdi, send_buff, 512);
    printf("send: %d bytes\n", r);

    int retry_count = 0;
    r = ftdi_read_data(ftdi, recv_buff, 512);
    while(r < 512) {
        usleep(10*1000);
        r += ftdi_read_data(ftdi, recv_buff, 512 - r);
        if(++retry_count > 50) {
            printf("recv timeout (%d bytes)\n", r);
           return EXIT_FAILURE;
        }
    }
    printf("test reply: [%d] %s\n", r, recv_buff);
    return 0;
}


void hexdump(const unsigned char *data, int len) {
    for(int i=0; i<len; i += 16) {
        printf("%04X  ", i);
        for(int j=0; j<16; j++) {
            printf("%02X%s", data[i+j], ((j&3)==3) ? "  " : " ");
        }
        for(int j=0; j<16; j++) {
            char c = data[i+j];
            printf("%c%s",
                (c >= 0x20 && c <= 0x7E) ? c : '.',
                ((j&3)==3) ? " " : "");
        }
        printf("\n");
    }
}


void do_read(struct ftdi_context *ftdi) {
    unsigned char recv_buff[512];
    unsigned char send_buff[512];
    memset(recv_buff, 0, 512);
    memset(send_buff, 0, 512);
    send_buff[0] = 'O';
    send_buff[1] = 'K';

    int rxCount = 0;

    printf("Connected\n");
    while(1) {
        memset(recv_buff, 0, 512);
        int r = ftdi_read_data(ftdi, recv_buff, 512);
        if(r > 0) {
            *(int*)send_buff = rxCount + 1;
            ftdi_write_data(ftdi, send_buff, 512);
            //printf("%s\n", recv_buff);
            printf("recv #%d: %d\n", ++rxCount, r);
            hexdump(recv_buff, r);
        }
        else {
            usleep(1000);
        }
    }
}


int main(int argc, const char **argv) {
    struct ftdi_context *ftdi = init_ftdi();
    if(!ftdi) return EXIT_FAILURE;

    //ftdi_write_data(ftdi, "\x12\x34\x56\x78", 512);
    //do_test(ftdi);
    do_read(ftdi);

    printf("done\n");
    ftdi_usb_close(ftdi);
    ftdi_free(ftdi);
    return EXIT_SUCCESS;
}
