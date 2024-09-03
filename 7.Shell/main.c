#include <stdio.h>

#include "board.h"
#include "periph/gpio.h"
#include "xtimer.h"
#include "shell.h"

// Pin declarations
#ifndef LED0_PIN_STM
#define LED0_PIN_STM GPIO_PIN(PORT_C, 13) 
#endif

int led_on(int argc, char **argv){
    
    if (argc < 2) {
        printf("usage: %s [string]\n", argv[0]);
        return 1;
    }

    gpio_set(LED0_PIN_STM); // Set the given pin to HIGH
    return 0;
}

int led_off(int argc, char **argv) {
    
    if (argc < 2) {
        printf("usage: %s [string]\n", argv[0]);
        return 1;
    }

    gpio_clear(LED0_PIN_STM); // Set the given pin to LOW
    return 0;
}

static const shell_command_t shell_commands[] = {
    { "led_on", "Turns up the LED0", led_on},
    { "led_off", "Turns off the LED0", led_off},
    { NULL, NULL, NULL } 
};


int main(void) {

    // GPIO Init; Pin, Output
    gpio_init(LED0_PIN_STM, GPIO_OUT);
    // You can also use gpio_init(GPIO_PIN(PORT_C, 13), GPIO_OUT);

    char line_buff[SHELL_DEFAULT_BUFSIZE]; // Buffer of shell line command
    printf("Starting the shell...\n"); // prints in UART_DEV(0)
    shell_run(shell_commands, line_buff, SHELL_DEFAULT_BUFSIZE); // starting the shell
    

    /**/
    // while(1) {

    // }

    return 0;
}
