#include <stddef.h>
#include <stdint.h>

#include "main.h"
#include "uart.h"
#include "gpio.h"


// void kernel_main(uint32_t r0, uint32_t r1, uint32_t atags)
void kernel_main(void)
{
    // volatile uint32_t i = 0;
    // (void) r0;
    // (void) r1;
    // (void) atags;

    // initialize peripherals
    UART_init();
    gpio_init();

    // indicate boot success w/ GPIO and UART message
    UART_writestring("yayyyy kernel boots!!\n");

    gpio_flashActivityLed(0x1);  //flash long, short, short, short

    while(1)
    {
        //just echo the characters received to the terminal
        UART_putc(UART_getc());
    }
}





