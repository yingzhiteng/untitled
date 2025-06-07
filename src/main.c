#include <stdio.h>

#include "stm32f103xb.h"
#include "drivers/systemclock/systemclock.h"
#include "drivers/usart/usart.h"
#include "utils/delay/delay.h"
#include <stdint.h>

extern uint8_t isToSend;
extern uint8_t buffer[100];
extern uint8_t len;



int main(void) {
    SystemClock_Config();
    usart_init();
    usart_send(97);
    printf("hello,world\n");
    while (1) {
        if (isToSend) {
            usart_sendStr((char*)buffer);
            isToSend = 0;
            len = 0;
        }
    }
}
