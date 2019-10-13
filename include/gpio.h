
#ifndef GPIO_H
#define GPIO_H

// The GPIO registers base address.
#if (RPI_MAJOR_VERSION == 1)
 #define GPIO_BASE 0x20200000 // for raspi2 & 3 0x20200000 for raspi1
#else
 #define GPIO_BASE 0x3F200000 // for raspi2 & 3 0x20200000 for raspi1
#endif

// REGISTER DEFINITIONS

#define GPFSEL0 (GPIO_BASE + 0x00) // GPIO Function Select
#define GPFSEL0 (GPIO_BASE + 0x00) // GPIO Function Select
#define GPFSEL1 (GPIO_BASE + 0x04) // GPIO Function Select
#define GPFSEL2 (GPIO_BASE + 0x08) // GPIO Function Select
#define GPFSEL3 (GPIO_BASE + 0x0C) // GPIO Function Select
#define GPFSEL4 (GPIO_BASE + 0x10) // GPIO Function Select
#define GPFSEL5 (GPIO_BASE + 0x14) // GPIO Function Select
#define GPSET0  (GPIO_BASE + 0x1C)  // GPIO Pin Output Set 0
#define GPSET1  (GPIO_BASE + 0x20)  // GPIO Pin Output Set 1
#define GPCLR0  (GPIO_BASE + 0x28)  // GPIO Pin Output Clear
#define GPCLR1  (GPIO_BASE + 0x2C)  // GPIO Pin Output Clear
#define GPLEV0  (GPIO_BASE + 0x34)  // GPIO Pin Level 0 32 R
#define GPLEV1  (GPIO_BASE + 0x38)  // GPIO Pin Level 1 32 R
#define GPEDS0  (GPIO_BASE + 0x40)  // GPIO Pin Event Detect
#define GPEDS1  (GPIO_BASE + 0x44)  // GPIO Pin Event Detect
#define GPREN0  (GPIO_BASE + 0x4C)  // GPIO Pin Rising Edge
#define GPREN1  (GPIO_BASE + 0x50)  // GPIO Pin Rising Edge
#define GPFEN0  (GPIO_BASE + 0x58)  // GPIO Pin Falling Edge
#define GPFEN1  (GPIO_BASE + 0x5C)  // GPIO Pin Falling Edge

#define GPHEN0  (GPIO_BASE + 0x64)    // GPIO Pin High Detect Enable 0 32 R/W
#define GPHEN1  (GPIO_BASE + 0x68)    // GPIO Pin High Detect Enable 1 32 R/W
#define GPLEN0  (GPIO_BASE + 0x70)    // GPIO Pin Low Detect Enable 0 32 R/W
#define GPLEN1  (GPIO_BASE + 0x74)    // GPIO Pin Low Detect Enable 1 32 R/W
#define GPAREN0 (GPIO_BASE + 0x7C)   // GPIO Pin Async. Rising Edge Detect 0 32 R/W
#define GPAREN1 (GPIO_BASE + 0x80)   // GPIO Pin Async. Rising Edge Detect 1 32 R/W
#define GPAFEN0 (GPIO_BASE + 0x88)   // GPIO Pin Async. Falling Edge Detect 0 32 R/W
#define GPAFEN1 (GPIO_BASE + 0x8C)   // GPIO Pin Async. Falling Edge Detect 1 32 R/W
#define GPPUD   (GPIO_BASE + 0x94)     // GPIO Pin Pull-up/down Enable 32 R/W
#define GPPUDCLK0 (GPIO_BASE + 0x98) // GPIO Pin Pull-up/down Enable Clock 0 32 R/W
#define GPPUDCLK1 (GPIO_BASE + 0x9C) // GPIO Pin Pull-up/down Enable Clock 1 32 R/W


// OTHER Defines

#define NUM_GPIOS 54


// FUNCTION DECLARATIONS

void gpio_init(void);
void gpio_setAsOutput(uint32_t gpio_num);
void gpio_setAsInput(uint32_t gpio_num);
void gpio_write(uint32_t gpio_num, bool value);
bool gpio_read(uint32_t gpio_num);

void gpio_setPullUp(uint32_t gpio_num, bool pullup_on);
void gpio_setPullDown(uint32_t gpio_num, bool pulldown_on);



#endif