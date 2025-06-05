//
// Created by yingzhiteng on 25-6-5.
//

#include "exti_handlers.h"

void EXTI15_10_IRQHandler(void) {
    EXTI->PR = EXTI_PR_PR10;
    delay_ms(5);
    if ((GPIOA->IDR & GPIO_IDR_IDR10) !=0) {
        toggle_gpio(GPIOA,GPIO_ODR_ODR0);
    }
}