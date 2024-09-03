#include <stdio.h>

#include "board.h"
#include "periph/gpio.h"
#include "xtimer.h"

// Pin declarations
#ifndef LED0_PIN_STM
#define LED0_PIN_STM GPIO_PIN(PORT_C, 13) 
#endif

int main(void) {

    // GPIO Init; Pin, Output
    gpio_init(LED0_PIN_STM, GPIO_OUT); // Initialize the given pin as general purpose input or output
    // You can also use gpio_init(GPIO_PIN(PORT_C, 13), GPIO_OUT);
    
    while(1) {
        
        gpio_read(LED0_PIN_STM); // Reading value of GPIO Pin
        xtimer_msleep(500); // Delay, time in milliseconds (ms)

        gpio_write(LED0_PIN_STM, 1); // Set the given pin to the given value
        xtimer_msleep(500);
        
        gpio_clear(LED0_PIN_STM); // Set the given pin to LOW
        xtimer_msleep(500);
        
        gpio_set(LED0_PIN_STM); // Set the given pin to HIGH
        xtimer_msleep(500);
        
        gpio_toggle(LED0_PIN_STM); // Toggle the value of the given pin (0 -> 1; 1 -> 0)
        xtimer_msleep(500);
    }

    return 0;
}
