#include "dma.h"

void dma1_init(){

	RCC->AHB1ENR |= RCC_AHB1ENR_DMA1EN;

	DMA1_Stream4->CR |= DMA_SxCR_CHSEL_1 | DMA_SxCR_CHSEL_2;

}
