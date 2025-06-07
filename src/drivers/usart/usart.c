//
// Created by yingzhiteng on 25-6-5.
//

#include "usart.h"



void usart_init(void) {
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN;

    GPIOA->CRH |= GPIO_CRH_CNF9_1;
    GPIOA->CRH &= ~GPIO_CRH_CNF9_0;
    GPIOA->CRH |= GPIO_CRH_MODE9;

    GPIOA->CRH &= ~GPIO_CRH_CNF10_1;
    GPIOA->CRH |= GPIO_CRH_CNF10_0;
    GPIOA->CRH &= ~GPIO_CRH_MODE10;

    USART1->BRR = 0x271;

    USART1->CR1 |= USART_CR1_UE;
    USART1->CR1 &= ~USART_CR1_M;
    USART1->CR1 &= ~USART_CR1_PCE;
    USART1->CR1 |= USART_CR1_TE;
    USART1->CR1 |= USART_CR1_RE;

    USART1->CR2 &= ~USART_CR2_STOP;


    USART1->CR1 |= USART_CR1_RXNEIE;
    USART1->CR1 |= USART_CR1_IDLEIE;

    NVIC_SetPriorityGrouping(3);
    NVIC_SetPriority(USART1_IRQn, 2);
    NVIC_EnableIRQ(USART1_IRQn);

}

void usart_send(uint8_t c) {
    while (!(USART1->SR & USART_SR_TXE)) {

    }
    USART1->DR = c;
}



void usart_sendStr(char* str) {
    for (int i = 0; i < strlen(str); ++i) {
        usart_send(str[i]);
    }
}




uint8_t buffer[100]={0};
uint8_t len = 0;
uint8_t isToSend = 0;
void USART1_IRQHandler(void) {
    if (USART1->SR & USART_SR_RXNE) {
        buffer[len] = USART1->DR;
        len++;
    }else if (USART1->SR & USART_SR_IDLE) {
        USART1->SR;
        USART1->DR;
        isToSend=1;
    }
}

int fputc(int ch, FILE *f) {
    usart_send(ch);
    return ch;
}

int _write(int file, char *ptr, int len) {
    // 遍历 ptr 指向的缓冲区，逐个字符发送
    for (int i = 0; i < len; i++) {
        fputc(*(ptr + i), stdout); // 调用我们自己的 fputc
    }
    return len; // 返回实际写入的字节数
}