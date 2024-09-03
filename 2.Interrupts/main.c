#include <stdio.h>

#include "board.h"
#include "periph/gpio.h"
#include "xtimer.h"

// Pin declarations
#ifndef LED0_PIN_STM
#define LED0_PIN_STM GPIO_PIN(PORT_C, 13) 
#endif

#ifndef BTN0_PIN_STM
#define BTN0_PIN_STM GPIO_PIN(PORT_B, 1)
#endif

// Interrupt callback function
void btn0_handler(void *arg) {
    (void)arg;
    gpio_irq_disable(BTN0_PIN_STM); // Disable interrupt
    gpio_set(LED0_PIN_STM); // Set pin to HIGH
}


int main(void) {

    // GPIO Init; Pin, Output
    gpio_init(LED0_PIN_STM, GPIO_OUT);
    // You can also use gpio_init(GPIO_PIN(PORT_C, 13), GPIO_OUT);

    // GPIO Interrupt init; 
    // Pin, Input PULL-UP, Falling edge, Name of handler function, (optional) arg to callback
    gpio_init_int(BTN0_PIN_STM, GPIO_IN_PU, GPIO_FALLING, btn0_handler, NULL);
    
    while(1) {
        if (gpio_read(LED0_PIN_STM)) { // Read state of pin
            xtimer_msleep(1000); // Delay 1000 ms
            gpio_irq_enable(BTN0_PIN_STM); //Enabling Interrupt
            gpio_clear(LED0_PIN_STM); // Set pin to LOW
        }
    }

    return 0;
}
