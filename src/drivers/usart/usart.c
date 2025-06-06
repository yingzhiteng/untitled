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


}

void usart_send(uint8_t c) {
    while ((USART1->SR & USART_SR_TXE) == 0) {

    }
    USART1->DR = c;
}

uint8_t usart_receive(void) {
    while ((USART1->SR & USART_SR_RXNE) == 0) {

    }
    return USART1->DR;
}
