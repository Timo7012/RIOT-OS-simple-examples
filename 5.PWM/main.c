#include <stdio.h>

#include "board.h"
#include "periph/gpio.h"
#include "periph/pwm.h"
#include "xtimer.h"

// Pin declarations
#ifndef LED0_PIN_STM
#define LED0_PIN_STM GPIO_PIN(PORT_C, 13) 
#endif

pwm_t pwm; // basic structure of pulse width modulation (PWM)

int main(void) {

    pwm_channels(pwm);
    printf("Initialising PWM...\n"); // prints in UART_DEV(0)
    pwm_init(pwm, PWM_LEFT, 50, 1024); //PWM Init Function


    // GPIO Init; Pin, Output
    gpio_init(LED0_PIN_STM, GPIO_OUT);
    // You can also use gpio_init(GPIO_PIN(PORT_C, 13), GPIO_OUT);
    
    while(1) {
        pwm_set(pwm,1,1024); // setting the value of pwm (0...resolution)
        xtimer_msleep(2000);
        pwm_set(pwm,1,512); // setting the value of pwm (0...resolution)
        xtimer_msleep(2000);
        pwm_set(pwm,1,0); // setting the value of pwm (0...resolution)
        xtimer_msleep(2000);

        /*Smooth increasing of LED brightness*/
        for (int i = 0; i < 1024; ++i ) {
            pwm_set(pwm,1,i); // setting the value of pwm (0...resolution)
        }

        /*Smooth decreasing of LED brightness*/
        for (int i = 1024; i > 0; --i ) {
            pwm_set(pwm,1,i); // setting the value of pwm (0...resolution)
        }
        xtimer_msleep(500);
    }

    return 0;
}
