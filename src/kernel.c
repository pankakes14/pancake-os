#include <stddef.h>
#include <stdint.h>

#include "main.h"
#include "uart.h"


void kernel_main(uint32_t r0, uint32_t r1, uint32_t atags)
{
    (void) r0;
    (void) r1;
    (void) atags;

    UART_init();
    UART_writestring("yayyyy kernel boots!!\n");

    while(1)
    {
        //just echo the characters received to the terminal
        UART_putc(UART_getc());
    }

}





