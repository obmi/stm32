#include "usart.h"
#include "ringbuffer.h"

extern RingBuffer rx_ring_buf;


void USART2_init() {

    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    RCC->APB1ENR |= RCC_APB1ENR_USART2EN;


    GPIOA->MODER &= ~(GPIO_MODER_MODER2 | GPIO_MODER_MODER3);
    GPIOA->MODER |= GPIO_MODER_MODER2_1 | GPIO_MODER_MODER3_1;
    GPIOA->AFR[0] |= (7 << 12) | (7 << 8); // PA2 и PA3 в AF7 (USART2)


    USART2->BRR = 0x0683; // Настройка на 9600 бод при частоте шины 16 МГц
    USART2->CR1 |= USART_CR1_RE | USART_CR1_TE;
    USART2->CR1 |= USART_CR1_RXNEIE;

    USART2->CR1 |= USART_CR1_UE;

    NVIC_EnableIRQ(USART2_IRQn);
}


void USART2_IRQHandler(){

	if (USART2->SR & USART_SR_RXNE) {
		buffer_put_to_end(&rx_ring_buf, (uint8_t)USART2->DR);
	}

}
