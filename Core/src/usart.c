#include "usart.h"
#include "ringbuffer.h"

extern RingBuffer rx_ring_buf;


void USART2_halfinit() {

    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    RCC->APB1ENR |= RCC_APB1ENR_USART2EN;

    GPIOA->MODER &= ~(GPIO_MODER_MODER2);
    GPIOA->MODER &= ~(GPIO_MODER_MODER2);
    GPIOA->MODER |= GPIO_MODER_MODER2_1; // Альтернативная функция
    GPIOA->MODER |= GPIO_MODER_MODER3_1; // Альтернативная функция

    GPIOA->AFR[0] |= (7 << 12);
    GPIOA->AFR[0] |= (7 << 8);

    GPIOA->OTYPER |= GPIO_OTYPER_OT2;

    GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR2_1;

    USART2->BRR = 0x8B; //115200

    USART2->CR3 |= USART_CR3_HDSEL;

    USART2->CR1 |= USART_CR1_RE;

    USART2->CR1 |= USART_CR1_RXNEIE;

    USART2->CR1 |= USART_CR1_UE;

}
void USART2_init() {

    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    RCC->APB1ENR |= RCC_APB1ENR_USART2EN;


    GPIOA->MODER &= ~(GPIO_MODER_MODER2 | GPIO_MODER_MODER3);
    GPIOA->MODER |= GPIO_MODER_MODER2_1 | GPIO_MODER_MODER3_1;
    GPIOA->AFR[0] |= (7 << 12) | (7 << 8); // PA2 и PA3 в AF7 (USART2)


    USART2->BRR = 0x8B; // Настройка на 115200 бод при частоте шины 16 МГц
    USART2->CR1 |= USART_CR1_RE | USART_CR1_TE;
    USART2->CR1 |= USART_CR1_RXNEIE;

    USART2->CR1 |= USART_CR1_UE;

    NVIC_SetPriority(USART2_IRQn, 0);
    NVIC_EnableIRQ(USART2_IRQn);
}


void USART2_IRQHandler(){

	if (USART2->SR & USART_SR_RXNE) {
		while (!(USART2->SR & USART_SR_TC));
		buffer_put_to_end(&rx_ring_buf, (uint8_t)USART2->DR);
		while (!(USART2->SR & USART_SR_TC));

	}


}

void USART2_send(uint8_t data) {
    // Отключаем приём
    USART2->CR1 &= ~USART_CR1_RE;
    // Включаем передачу
    USART2->CR1 |= USART_CR1_TE;
    // Ждем, пока передатчик освободится
    while (!(USART2->SR & USART_SR_TXE));
    // Отправляем данные
    USART2->DR = data;
    // Ждем завершения передачи
    while (!(USART2->SR & USART_SR_TC));
    // Отключаем передачу
    USART2->CR1 &= ~USART_CR1_TE;
    // Включаем приём
    USART2->CR1 |= USART_CR1_RE;
}
