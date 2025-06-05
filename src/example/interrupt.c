//
// Created by yingzhiteng on 25-6-5.
//
#include "interrupt.h"

void interrupt_test(void) {
    rcc_enable();
    led_init();
    exti_init();
}