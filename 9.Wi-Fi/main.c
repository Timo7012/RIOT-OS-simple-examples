#include <stdio.h>

#include "board.h"
#include "periph/gpio.h"
#include "xtimer.h"

#include "lwip/tcp.h"

//#include "lwip.h"
//#include "lwip/init.h"
//#include "lwip/netif.h"
//#include "lwip/tcpip.h" 
//#include "lwip/err.h" 
//#include "lwip/sockets.h" 
//#include "lwip/sys.h" 
//#include "lwip/netdb.h"

#ifndef LED0_PIN_ESP32 
#define LED0_PIN_ESP32 GPIO_PIN(0, 39)
#endif


static struct tcp_pcb *testpcb;
err_t error;

uint32_t tcp_send_packet(void)
{
    char *string = "GET / HTTP/1.0\r\nHost: ya.ru\r\n\r\n ";
    uint32_t len = strlen(string);
    err_t error;

    /* push to buffer */    
    error = tcp_write(testpcb, string, len, TCP_WRITE_FLAG_COPY);

    if (error) {
        printf("ERROR: Code: %d (tcp_send_packet :: tcp_write)\n", error);
        return 1;
    }

    /* now send */
    error = tcp_output(testpcb);
    if (error) {
        printf("ERROR: Code: %d (tcp_send_packet :: tcp_output)\n", error);
        return 1;
    }
    return 0;
}

/* connection established callback, err is unused and only return 0 */
err_t connectCallback(void *arg, struct tcp_pcb *tpcb, err_t err)
{
    printf("Connection Established.\n");
    printf("Now sending a packet\n");
    tcp_send_packet();
    return 0;
}

err_t tcpRecvCallback(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err)
{
    printf("Data recieved.\n");
    if (p == NULL) {
        printf("The remote host closed the connection.\n");
        printf("Now I'm closing the connection.\n");
        tcp_close(tpcb);
        return ERR_ABRT;
    } else {
        printf("Number of pbufs %d\n", pbuf_clen(p));
        printf("Contents of pbuf %s\n", (char *)p->payload);
    }

    return 0;
}

void tcpErrorHandler (void *arg, err_t err){
    (void)arg;
    printf("TCP Error: %d", err);
}

void tcp_setup(void)
{
    uint32_t data = 0xdeadbeef;

    /* create an ip */
    ip_addr_t ip;
    IP_ADDR4(&ip, 77,88,55,242);    //IP of server (ya.ru - 77.88.55.242, it can be different)

    /* create the control block */
    testpcb = tcp_new();    //testpcb is a global struct tcp_pcb
                            // as defined by lwIP

    
    // error = tcp_bind(testpcb, IP_ANY_TYPE, 1234);
    // xtimer_sleep(1);
    // printf("TCP BIND status: %d\n", error);
    

    /* dummy data to pass to callbacks*/
    tcp_arg(testpcb, &data);

    error = tcp_bind(testpcb, IP_ANY_TYPE, 1234); // get local ip
    xtimer_sleep(1);
    printf("TCP BIND status: %d\n", error);

    /* register callbacks with the pcb */
    tcp_err(testpcb, tcpErrorHandler);
    tcp_recv(testpcb, tcpRecvCallback);
    //tcp_sent(testpcb, tcpSendCallback);

    /* now connect */
    error = tcp_connect(testpcb, &ip, 80, connectCallback);
    printf("TCP Connect status: %d\n", error);

    if (error) {

    }

}


int main(void) {
    xtimer_sleep(1);
    printf("MAIN START\n");
    xtimer_sleep(10);
    printf("Initializing TCP connection...\n");
    tcp_setup();

    while(1) {

    }

    return 0;
}
