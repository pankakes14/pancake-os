#ifndef MAIN_H
#define MAIN_H
#include <stdint.h>

//============    BUILD SWITCHES!! ========================
#define RPI_MAJOR_VERSION 1



//==============   HELPER FUNCTIONS =======================

// First set up some functions to write to memory
static inline void mmio_write(uint32_t reg, uint32_t data)
{
    *(volatile uint32_t *)reg = data;
}

static inline uint32_t mmio_read(uint32_t reg)
{
    return *(volatile uint32_t *)reg;
}


//trying to do this in a way that the compiler won't optimize away
static inline void delay_count(uint32_t count)
{
    volatile uint32_t temp = count;
    while (temp > 0)
    {
        temp--;
    }
}


#endif
