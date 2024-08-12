#include "spi.h"



void spi1_init() {

	RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

	GPIOA->MODER &= ~(GPIO_MODER_MODER5 | GPIO_MODER_MODER7);
	GPIOA->MODER |= GPIO_MODER_MODER5_1 | GPIO_MODER_MODER7_1;

	GPIOA->AFR[0] |= (5 << 20) | (5 << 28);	// PA5 и PA7 в AF05 (SPI1_SCK и SPI1_MOSI)

	SPI1->CR1 |= SPI_CR1_BIDIMODE;	// 1-line mode (halfduplex)
	SPI1->CR1 |= SPI_CR1_BIDIOE;	// transmit-only mode

	SPI1->CR1 &= ~SPI_CR1_DFF;		// 16-bit data frame format
	SPI1->CR1 |= SPI_CR1_SSM; 		// вкл программное управление слэйвами
	SPI1->CR1 |= SPI_CR1_SSI;
	SPI1->CR1 &= ~SPI_CR1_LSBFIRST;	// MSB first

	SPI1->CR1 |= SPI_CR1_BR_2 | SPI_CR1_BR_1 | SPI_CR1_BR_0;	// 111 - (freq / 256), freq = 32MHz
	SPI1->CR1 |= SPI_CR1_MSTR;		// iammaster

	//cpol, cpha...

	SPI1->CR1 |= SPI_CR1_SPE;		//spi en



}


void spi1_send(uint8_t data) {
	while(!(SPI1->SR & SPI_SR_TXE));	//пока tx не пуст
	SPI1->DR = data;

	while (SPI1->SR & SPI_SR_BSY);
}
