
#ifndef GPIO_H
#define GPIO_H

// The GPIO registers base address.
#if (RPI_MAJOR_VERSION == 1)
 #define GPIO_BASE 0x20200000 // for raspi2 & 3 0x20200000 for raspi1
#else
 #define GPIO_BASE 0x3F200000 // for raspi2 & 3 0x20200000 for raspi1
#endif
 

#define GPPUD (GPIO_BASE + 0x94)
#define GPPUDCLK0 (GPIO_BASE + 0x98)

#endif