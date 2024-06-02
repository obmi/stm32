#include "usart.h"

static uint8_t data_to_send;

void usart2_init(){

	RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

	GPIOA->MODER |= GPIO_MODER_MODE2_1;						//TX, Alternate function mode
	GPIOA->MODER |= GPIO_MODER_MODE3_1;						//RX, Alternate function mode

	GPIOA->AFR[0] |= (1 << 10) | (1 << 9) | (1 << 8);		//	USART2_TX is AF07
	GPIOA->AFR[0] |= (1 << 14) | (1 << 13) | (1 << 12);		//	USART2_RX is AF07

	USART2->BRR = 0x9C4; 									//	24MHz, baud rate = 9600


//	USART2->CR1 |= USART_CR1_RXNEIE							//RXNE interrupt enable. Interrupt is generated if RXNE = 1 (Received data is ready to be read)
//				| USART_CR1_TXEIE;							//TXE interrupt enable.	 Interrupt is generated if TXE = 1 	(Data is transferred to the shift register)

	USART2->CR1 |= USART_CR1_UE								//USART enable
				| USART_CR1_RE 								//Receiver enable
				| USART_CR1_TE;								//Transmitter enable





	NVIC_EnableIRQ(USART2_IRQn);


}

void usart2_send(uint8_t data){
	data_to_send = data;
	USART2->CR1 |= USART_CR1_TXEIE;
}

void usart2_read(){

}

void USART2_IRQHandler(){

	if(USART2->SR & USART_SR_TXE){
		USART2->DR = data_to_send;
		USART2->CR1 &= ~USART_CR1_TXEIE;
	}


	if(USART2->SR & USART_SR_RXNE){


	}

}







