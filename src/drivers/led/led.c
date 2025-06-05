//
// Created by yingzhiteng on 25-6-5.
//

#include "led.h"

void led_init(void) {

    GPIOA->CRL &= ~GPIO_CRL_CNF0;
    GPIOA->CRL |= GPIO_CRL_MODE0;
}

void toggle_gpio(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin) {
    GPIOx->ODR ^= GPIO_Pin;
}