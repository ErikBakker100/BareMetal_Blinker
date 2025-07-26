
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------

// Select the right version in the Makefile
#if defined (raspberry_zero_2w)
    #warning "using settings for raspberry_zero_2w"
    #define PERIPHERAL_BASE     0x3F000000
    #define GPIO_LED_PIN 29 // GPIO 29
#elif defined (raspberry_zero_1w)
    #warning "using settings for raspberry_zero_1w"
    #define PERIPHERAL_BASE   0x20000000
    #define GPIO_LED_PIN 47 // GPIO 47
#elif defined (raspberry_pi_4b)
    #warning "using settings for raspberry_pi_4b"
    #define PERIPHERAL_BASE   0xFE000000
    #define GPIO_LED_PIN 21 // GPIO 21, the ACT_LED cannot be used as a GPIO on a pi 4b
#endif

#define GPIO_BASE        (PERIPHERAL_BASE + 0x200000)
// Elke GPIO-pin wordt geconfigureerd met 3 bits in een van de GPFSELn-registers:
// Elke GPFSEL(n) regelt 10 GPIO-pinnen. Dus: GPFSEL0: GPIO 0–9, GPFSEL1: GPIO 10–19, ..., GPFSEL4: GPIO 40–49

#define GPFSEL_BASE     ((volatile unsigned int*)(GPIO_BASE + 0x00))
#define GPSET0          ((volatile unsigned int*)(GPIO_BASE + 0x1C))
#define GPCLR0          ((volatile unsigned int*)(GPIO_BASE + 0x28))


// Function to delay for a given number of cycles
void delay(unsigned int count) {
    for (volatile unsigned int i = 0; i < count; i++) {
        asm volatile("nop");
    }
}

//-------------------------------------------------------------------------

void main(void) {

    unsigned int reg_index = GPIO_LED_PIN / 10; // calculate the register index
    unsigned int bit = (GPIO_LED_PIN % 10) * 3; // calculate the bit position within the register
 
    volatile unsigned int* gpfsel = GPFSEL_BASE + reg_index; // get the address of the GPFSEL register for the LED pin
    unsigned int selector = *gpfsel; // read the address value of the calculated GPFSEL register 

    selector &= ~(7 << bit); // clear the bits for the LED pin, write 0b000
    selector |= 1 << bit;  // function select = 001 (output)
    *gpfsel = selector;

    volatile unsigned int* gpset = GPSET0 + (GPIO_LED_PIN / 32); // +0 voor 0–31, +1 voor 32–53
    volatile unsigned int* gpclr = GPCLR0 + (GPIO_LED_PIN / 32); // +0 voor 0–31, +1 voor 32–53

    while (1) {
        
        *gpset = (1 << (GPIO_LED_PIN % 32));
        delay(500000);
        *gpclr = (1 << (GPIO_LED_PIN % 32));
        delay(500000);
    }
}
// This code is intended to run on a Raspberry Zero 2(W).
