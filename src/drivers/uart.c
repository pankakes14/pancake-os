#include "main.h"
#include <stdint.h>
#include "uart.h"
#include "gpio.h"


// initialize the UART port to 
void UART_init(void)
{
    mmio_write(UART0_CR, 0x00000000);

    mmio_write(GPPUD, 0x00000000);
    delay_count(1500);

    mmio_write(GPPUDCLK0, (1 << 14) | (1 << 15));
    delay_count(1500);

    mmio_write(GPPUDCLK0, 0x00000000);

    mmio_write(UART0_ICR, 0x7FF);

    mmio_write(UART0_IBRD, 1);
    mmio_write(UART0_FBRD, 40);

    mmio_write(UART0_LCRH, (1 << 4) | (1 << 5) | (1 << 6));

    mmio_write(UART0_IMSC, (1 << 1) | (1 << 4) | (1 << 5) | (1 << 6) | \
                           (1 << 7) | (1 << 8) | (1 << 9) | (1 << 10));

    mmio_write(UART0_CR, (1 << 0) | (1 << 8) | (1 << 9));
}



void UART_putc(char c)
{
    //wait for HW to be ready to send before writing new character
    while (mmio_read(UART0_FR) & (1 << 5));
    mmio_write(UART0_DR, c);
}


char UART_getc(void)
{
    while (mmio_read(UART0_FR) & (1 << 4));
    return mmio_read(UART0_DR);
}


void UART_writestring(char *str)
{
    uint32_t i;

    for (i = 0; str[i] != '\0'; i++)
    {
        UART_putc(str[i]);
    }

}

