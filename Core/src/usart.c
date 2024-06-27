#include "usart.h"
#include "ringbuffer.h"

extern RingBuffer rx_ring_buf;



void USART2_halfduplex_init() {

    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    RCC->APB1ENR |= RCC_APB1ENR_USART2EN;

    GPIOA->MODER &= ~(GPIO_MODER_MODER2);

    GPIOA->MODER |= GPIO_MODER_MODER2_1; 	//alt.func

    GPIOA->OTYPER |= GPIO_OTYPER_OT2;		//opendrain

    GPIOA->AFR[0] |= (7 << 8);				//AF7 - usart2

    USART2->BRR = 0x116; //115200
//    USART2->BRR = 0xD05; //9600


    USART2->CR1 |= USART_CR1_RE;
    USART2->CR1 |= USART_CR1_TE;
    USART2->CR3 |= USART_CR3_HDSEL;			//half-duplex

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
    while (!(USART2->SR & USART_SR_TXE));
    USART2->DR = data;
}


uint8_t USART2_read() {
    while (!(USART2->SR & USART_SR_RXNE));
    return USART2->DR;
}

void USART2_setbaudrate(uint32_t mode){
	USART2->BRR = mode;
}
