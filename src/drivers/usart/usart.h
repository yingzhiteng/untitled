//
// Created by yingzhiteng on 25-6-5.
//

#ifndef USART_H
#define USART_H
#include "stm32f103xb.h"
#include <stdint.h>
#include <string.h>
void usart_init(void);
void usart_send(uint8_t c);
void usart_sendStr(char* str);
void USART1_IRQHandler(void);
#endif //USART_H
