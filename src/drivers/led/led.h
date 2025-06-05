//
// Created by yingzhiteng on 25-6-5.
//

#ifndef LED_H
#define LED_H
#include "stm32f103xb.h"
void led_init(void);
void toggle_gpio(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin);
#endif //LED_H
