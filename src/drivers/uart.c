#include "main.h"
#include <stdint.h>
#include "uart.h"
#include "gpio.h"


// initialize the UART port to...err something
void UART_init(void)
{
    // Disable UART 0
    mmio_write(UART0_CR, 0x00000000);

    // disable pull up/down for all GPIO
    mmio_write(GPPUD, 0x00000000);
    delay_count(150);

    // Disable pull up down for GPIO 14/15 by pulsing 'clk' signal
    // This allows PU/PD changes to take effect 
    mmio_write(GPPUDCLK0, (1 << 14) | (1 << 15));
    delay_count(150);
    mmio_write(GPPUDCLK0, 0x00000000);

    // Cleanr UART interrupts
    mmio_write(UART0_ICR, 0x7FF);

    // Set integer & fractional part of baud rate.
	// Divider = UART_CLOCK/(16 * Baud)
	// Fraction part register = (Fractional part * 64) + 0.5
#if (RPI_MAJOR_VERSION == 1)
    // seem like formua is not right for rasberry pi 1. After experimentation, I finally got 115200 baud
    // by UART_CLK / (DIVIDER) or specifically 3e6 / 26.04 = 115200 verified baud rate w/ o-scope
    mmio_write(UART0_IBRD, 26);
    mmio_write(UART0_FBRD, 3);
#else
	// UART_CLOCK = 3000000; divisor = 1.6; Baud = 115200.
    mmio_write(UART0_IBRD, 1);
    mmio_write(UART0_FBRD, 40);
#endif

    // enable FIFO and set word length to 8 bits
    mmio_write(UART0_LCRH, (1 << 4) | (1 << 5) | (1 << 6));

    // mask all interrupts
    mmio_write(UART0_IMSC, (1 << 1) | (1 << 4) | (1 << 5) | (1 << 6) | \
                           (1 << 7) | (1 << 8) | (1 << 9) | (1 << 10));

    // Enable UART TX and RX
    mmio_write(UART0_CR, (1 << 0) | (1 << 8) | (1 << 9));

    UART_putc('!');
}



void UART_putc(char c)
{
    //wait for HW to be ready to send before writing new character
    while (mmio_read(UART0_FR) & (1 << 5));
    mmio_write(UART0_DR, (uint32_t)c);
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

