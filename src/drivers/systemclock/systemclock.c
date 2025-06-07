//
// Created by yingzhiteng on 25-6-6.
//

#include "systemclock.h"
void SystemClock_Config(void) {
    // 1. 使能 HSE（外部晶振）
    RCC->CR |= RCC_CR_HSEON;
    while (!(RCC->CR & RCC_CR_HSERDY));

    // 2. 配置 FLASH 等待周期（72MHz 需要 2 个周期）
    FLASH->ACR |= FLASH_ACR_PRFTBE;
    FLASH->ACR &= ~FLASH_ACR_LATENCY;
    FLASH->ACR |= FLASH_ACR_LATENCY_2;

    // 3. 配置 AHB/APB 分频
    RCC->CFGR &= ~RCC_CFGR_HPRE;   // HCLK = SYSCLK / 1
    RCC->CFGR &= ~RCC_CFGR_PPRE1;  // PPRE1 清零
    RCC->CFGR |= RCC_CFGR_PPRE1_2; // PCLK1 = HCLK / 2 (APB1 = 36MHz)
    RCC->CFGR &= ~RCC_CFGR_PPRE2;  // PCLK2 = HCLK / 1 (APB2 = 72MHz)

    // 4. 配置 PLL：HSE × 9 = 72MHz（假设 HSE = 8MHz）
    RCC->CFGR &= ~RCC_CFGR_PLLSRC;  // 清零 PLL 源选择位
    RCC->CFGR |= (1 << 16);         // PLL 源 = HSE（手动设置第 16 位）
    RCC->CFGR &= ~RCC_CFGR_PLLMULL; // 清零 PLL 倍频位
    RCC->CFGR |= RCC_CFGR_PLLMULL9; // PLL 倍频 ×9

    // 5. 使能 PLL 并等待锁定
    RCC->CR |= RCC_CR_PLLON;
    while (!(RCC->CR & RCC_CR_PLLRDY));

    // 6. 切换系统时钟源到 PLL
    RCC->CFGR &= ~RCC_CFGR_SW;
    RCC->CFGR |= RCC_CFGR_SW_PLL;
    while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);
}