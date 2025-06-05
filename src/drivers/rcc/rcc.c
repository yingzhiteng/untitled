//
// Created by yingzhiteng on 25-6-5.
//

#include "rcc.h"

void rcc_enable(void) {
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
    RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
}