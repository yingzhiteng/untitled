//
// Created by yingzhiteng on 25-6-5.
//

#include "systick.h"

void SysTick_Init(void) {
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk; // 禁用SysTick
    SysTick->VAL   = 0U;                       // 清零当前值
    SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk; // 使用HCLK作为时钟源
    SysTick->CTRL &= ~SysTick_CTRL_TICKINT_Msk;  // 禁用SysTick中断 (查询模式延时不需要)
}
