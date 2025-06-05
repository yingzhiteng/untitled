//
// Created by yingzhiteng on 25-6-5.
//

#include "exti.h"

void exti_init(void) {
    GPIOA->CRH &= ~GPIO_CRH_CNF10_0;
    GPIOA->CRH |= GPIO_CRH_CNF10_1;
    GPIOA->CRH |= GPIO_CRH_MODE10;
    GPIOA->ODR &= ~GPIO_ODR_ODR10;
    AFIO->EXTICR[2] &= ~AFIO_EXTICR3_EXTI10;
    AFIO->EXTICR[2] |= AFIO_EXTICR3_EXTI10_PA;

    EXTI->RTSR |= EXTI_RTSR_TR10;
    EXTI->IMR |= EXTI_IMR_MR10;
    NVIC_SetPriorityGrouping(3);
    NVIC_SetPriority(EXTI15_10_IRQn,3);
    NVIC_EnableIRQ(EXTI15_10_IRQn);
}