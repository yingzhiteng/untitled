//
// Created by yingzhiteng on 25-6-5.
//

#include "delay.h"

void delay_us(uint32_t us) {
    SysTick->LOAD = SystemCoreClock / 1000000 * us - 1;
    SysTick->VAL = 0;
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
    while (!(SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk));
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
}

void delay_ms(uint32_t ms) {
    for (uint32_t i = 0; i < ms; i++) {
        SysTick->LOAD = (SystemCoreClock / 1000U) - 1U; // 1ms的周期数
        SysTick->VAL = 0U;
        SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
        while (!(SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk));
        SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
    }
}

void delay_s(uint32_t s) {
    while (s--) {
        delay_ms(1000);
    }
}