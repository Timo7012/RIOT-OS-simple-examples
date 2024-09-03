#include <stdio.h>

#include "board.h"
#include "periph/gpio.h"
#include "xtimer.h"

static char test_thread[THREAD_STACKSIZE_DEFAULT];

void *test_func(void *arg) {
    (void) arg;
    while (1) {
        printf("TestThread\n");
        xtimer_msleep(2000);
    }
    return NULL;

}

int main(void) {

    xtimer_sleep(1);

    thread_create(
        test_thread, 
        sizeof(test_thread),
        THREAD_PRIORITY_MAIN+1,
        THREAD_CREATE_STACKTEST,
        test_func,
        NULL,
        "TestThread"
    );

    while(1) {
        printf("MainThread\n");
        xtimer_msleep(10000);
    }

    return 0;
}
