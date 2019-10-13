#include "main.h"
#include "gpio.h"


// sets default states of each GPIO
void gpio_init(void)
{
    gpio_setAsOutput(21);
    gpio_write(21, true);
}


void gpio_setAsOutput(uint32_t gpio_num)
{
    uint32_t reg;
    uint32_t shadow;

    // Figure out which bank of registers this GPIO belongs to
    if (gpio_num >= 0 && gpio_num < 10)
    {
        reg = GPFSEL0;
    }
    else if (gpio_num >= 10 && gpio_num < 20)
    {
        reg = GPFSEL1;
    }
    else if (gpio_num >= 20 && gpio_num < 30)
    {
        reg = GPFSEL2;
    }
    else if (gpio_num >= 30 && gpio_num < 40)
    {
        reg = GPFSEL3;
    }
    else if (gpio_num >= 40 && gpio_num < 50)
    {
        reg = GPFSEL4;
    }
    else if (gpio_num >= 50 && gpio_num < 54)
    {
        reg = GPFSEL5;
    }
    else
    {
        return; // invalid GPIO number
    }

    // read regsiter, clear the 3 function select bits, set bit to indicate output. Write back
    shadow = mmio_read(reg);
    shadow &= (~(0x7 << ((gpio_num % 10) * 0x3))); 
    shadow |= (1 << (gpio_num * 3));
    mmio_write(reg, shadow);
}


void gpio_setAsInput(uint32_t gpio_num)
{
    uint32_t reg;
    uint32_t shadow;

    // Figure out which bank of registers this GPIO belongs to
    if (gpio_num >= 0 && gpio_num < 10)
    {
        reg = GPFSEL0;
    }
    else if (gpio_num >= 10 && gpio_num < 20)
    {
        reg = GPFSEL1;
    }
    else if (gpio_num >= 20 && gpio_num < 30)
    {
        reg = GPFSEL2;
    }
    else if (gpio_num >= 30 && gpio_num < 40)
    {
        reg = GPFSEL3;
    }
    else if (gpio_num >= 40 && gpio_num < 50)
    {
        reg = GPFSEL4;
    }
    else if (gpio_num >= 50 && gpio_num < 54)
    {
        reg = GPFSEL5;
    }
    else
    {
        return; // invalid GPIO number. Do nothing
    }

    // read regsiter, clear the 3 function select bits (b000 means input). Write back
    shadow = mmio_read(reg);
    shadow &= (~(0x7 << ((gpio_num % 10) * 0x3))); 
    mmio_write(reg, shadow);
}


void gpio_write(uint32_t gpio_num, bool value)
{
    uint32_t reg;
    uint32_t shadow;

    // choose which register specified gpio belongs to
    if (gpio_num >= 0 && gpio_num < 32)
    {
        reg = GPSET0;
    }
    else if (gpio_num >= 32 && gpio_num < 54)
    {
        reg = GPSET1;
    }
    else
    {
        return; //invalid GPIO number. Do nothing
    }

    // Read current value, set/clear bit. Each bit corresponds to value of a gpio and is 32 bits wide.
    // ex. gpio20 is bit 20 in the first register
    shadow = mmio_read(reg);
    if (value)
    {
        shadow |= (1 << (gpio_num % 32));
    }
    else
    {
        shadow &= ~(1 << (gpio_num % 32)); 
    }
    mmio_write(reg, shadow);
}


bool gpio_read(uint32_t gpio_num)
{
    uint32_t reg;
    uint32_t shadow;

    // choose which register specified gpio belongs to
    if (gpio_num >= 0 && gpio_num < 32)
    {
        reg = GPLEV0;
    }
    else if (gpio_num >= 32 && gpio_num < 54)
    {
        reg = GPLEV1;
    }
    else
    {
        return false; //invalid GPIO number. Return 0
    }

    shadow = mmio_read(reg);
    shadow &= (1 << (gpio_num % 32)); //clear all bits except gpio_num 

    return (bool) shadow;
}

void gpio_setPullUp(uint32_t gpio_num, bool pullup_on)
{
    //not implemented yet
}

void gpio_setPullDown(uint32_t gpio_num, bool pulldown_on)
{
    //not implemented yet
}