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
    gpio_init(LED0_PIN_STM, GPIO_OUT);
    // You can also use gpio_init(GPIO_PIN(PORT_C, 13), GPIO_OUT);
    
    while(1) {
        gpio_set(LED0_PIN_STM); // Set the given pin to HIGH
        printf("LED 1\n"); // prints in UART_DEV(0)
        xtimer_msleep(1000); // Delay 1000 ms
        gpio_clear(LED0_PIN_STM); // Set the given pin to LOW
        printf("LED 0\n"); // prints in UART_DEV(0)
        xtimer_msleep(1000); // Delay 1000 ms
    }

    return 0;
}
