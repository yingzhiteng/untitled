#include "Driver_USART.h"



/**
 * @description: ��ʼ������1
 */
void Driver_USART1_Init(void)
{
    /* 1. ����ʱ�� */
    /* 1.1 ����1�����ʱ�� */
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
    /* 1.2 GPIOʱ�� */
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;

    /* 2. ����GPIO���ŵĹ���ģʽ  PA9=Tx(�������� CNF=10 MODE=11)  PA10=Rx(�������� CNF=01 MODE=00)*/
    GPIOA->CRH |= GPIO_CRH_CNF9_1;
    GPIOA->CRH &= ~GPIO_CRH_CNF9_0;
    GPIOA->CRH |= GPIO_CRH_MODE9;

    GPIOA->CRH &= ~GPIO_CRH_CNF10_1;
    GPIOA->CRH |= GPIO_CRH_CNF10_0;
    GPIOA->CRH &= ~GPIO_CRH_MODE10;

    /* 3. ���ڵĲ������� */
    /* 3.1 ���ò����� 115200 */
    USART1->BRR = 0x271;
    /* 3.2 ����һ���ֵĳ��� 8λ */
    USART1->CR1 &= ~USART_CR1_M;
    /* 3.3 ���ò���ҪУ��λ */
    USART1->CR1 &= ~USART_CR1_PCE;
    /* 3.4 ����ֹͣλ�ĳ��� */
    USART1->CR2 &= ~USART_CR2_STOP;
    /* 3.5 ʹ�ܽ��պͷ��� */
    USART1->CR1 |= USART_CR1_TE;
    USART1->CR1 |= USART_CR1_RE;

    /* 4. ʹ�ܴ��� */
    USART1->CR1 |= USART_CR1_UE;
}

/**
 * @description: ����һ���ֽ�
 * @param {uint8_t} byte Ҫ���͵��ֽ�
 */
void Driver_USART1_SendChar(uint8_t byte)
{
    /* 1. �ȴ����ͼĴ���Ϊ�� */
    while ((USART1->SR & USART_SR_TXE) == 0)
        ;

    /* 2. ����д�������ݼĴ��� */
    USART1->DR = byte;
}

/**
 * @description: ����һ���ַ���
 * @param {uint8_t} *str Ҫ���͵��ַ���
 * @param {uint16_t} len �ַ������ֽڵĳ���
 * @return {*}
 */
void Driver_USART1_SendString(uint8_t *str, uint16_t len)
{
    for (uint16_t i = 0; i < len; i++)
    {
        Driver_USART1_SendChar(str[i]);
    }
}


/**
 * @description: ����һ���ֽڵ�����
 * @return {*} ���յ����ֽ�
 */
uint8_t Driver_USART1_ReceiveChar(void)
{
    /* �ȴ����ݼĴ����ǿ� */
    while ((USART1->SR & USART_SR_RXNE) == 0)
        ;
    return USART1->DR;
}

/**
 * @description: ���ձ䳤����.���յ������ݴ��뵽buff��
 * @param {uint8_t} buff ��Ž��յ�������
 * @param {uint8_t} *len ����յ������ݵ��ֽڵĳ���
 */
void Driver_USART1_ReceiveString(uint8_t buff[], uint8_t *len)
{
    uint8_t i = 0;
    while (1)
    {
        // �ȴ����շǿ�
        while ((USART1->SR & USART_SR_RXNE) == 0)
        {
            // �ڵȴ��ڼ�, �ж��Ƿ��յ�����֡
            if (USART1->SR & USART_SR_IDLE)
            {
                *len = i;
                return;
            }
        }
        buff[i] = USART1->DR;
        i++;
        // printf("�й��ѧϰ\r\n");
    }
}
