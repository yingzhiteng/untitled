#include "stm32f103xb.h"
#include "drivers/usart/usart.h"
#include "drivers/usart2/Driver_USART.h"

int main(void) {
    /*usart_init();
    usart_send('a');
    while(1) {
        uint8_t result = usart_receive();
        usart_send(result);
    }*/
    Driver_USART1_Init();
    Driver_USART1_SendChar('a');
    while (1) {
        uint8_t driver_usart1_receive_char = Driver_USART1_ReceiveChar();
        Driver_USART1_SendChar(driver_usart1_receive_char);
    }

}







