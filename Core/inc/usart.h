#include <stm32f4xx.h>
#include <stdint.h>


void USART2_init();
void USART2_halfduplex_init();
void USART2_IRQHandler();
void USART2_send(uint8_t data);
uint8_t USART2_read();

