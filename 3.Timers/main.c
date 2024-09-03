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

xtimer_t debounce_timer; // Declaration of timer

void debounce_timer_callback (void *arg) {
    (void)arg;
    gpio_clear(LED0_PIN_STM); // Set pin to LOW
    gpio_irq_enable(BTN0_PIN_STM); // Enable interrupt
}

// Interrupt callback function
void btn0_handler(void *arg) {
    (void)arg;
    gpio_irq_disable(BTN0_PIN_STM); // Disable interrupt
    gpio_set(LED0_PIN_STM); // Set pin to HIGH
    xtimer_set(&debounce_timer, 500 * 1000); // Turn on the timer, time in us (500 ms)
}


int main(void) {

    // GPIO Init; Pin, Output
    gpio_init(LED0_PIN_STM, GPIO_OUT);
    // You can also use gpio_init(GPIO_PIN(PORT_C, 13), GPIO_OUT);

    // GPIO Interrupt init; 
    // Pin, Input PULL-UP, Falling edge, Name of handler function, (optional) arg to callback
    gpio_init_int(BTN0_PIN_STM, GPIO_IN_PU, GPIO_FALLING, btn0_handler, NULL);

    // Creating callback function for timer overflow
    debounce_timer.callback = debounce_timer_callback;
    
    while(1) {

    }

    return 0;
}
