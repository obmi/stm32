#include "ringbuffer.h"
#include "usart.h"
#include "commands.h"
#include "ds18b20.h"
#include "main.h"

uint16_t rx_buffer[256];
RingBuffer rx_ring_buf;


uint8_t status;
uint8_t dt[16];		//ds18b20 raw received data

int main(void) {
	SystemInit();
	SystemCoreClockUpdate();
    ledinit();
//    USART2_init();
    USART2_halfduplex_init();
	USART2_IRQHandler();
	Port_AltFunc_Init();
//	tim2init();
//	TIM2_IRQHandler();
    buffer_init(&rx_ring_buf, &rx_buffer, 256);
	Set42MHz();
//	buttoninit();
//	EXTI_init();
//	EXTI0_IRQHandler();
//	ds18b20_init();

	TIM3_init();

	TIM3_IRQHandler();

    while(1){
    	// Изменение яркости светодиода
    	        for (uint32_t i = 0; i <= 1000; i++) {
    	            TIM3->CCR1 = i;  // Установка коэффициента заполнения
    	            for (uint32_t j = 0; j < 1000; j++);  // Небольшая задержка

    	            // Копирование состояния PA6 на PC13
    	            if (GPIOA->IDR & GPIO_IDR_ID6) {
    	                GPIOC->BSRR = GPIO_BSRR_BS13;
    	            } else {
    	                GPIOC->BSRR = GPIO_BSRR_BR13;
    	            }
    	        }
    	        for (uint32_t i = 1000; i > 0; i--) {
    	            TIM3->CCR1 = i;  // Установка коэффициента заполнения
    	            for (uint32_t j = 0; j < 1000; j++);  // Небольшая задержка

    	            // Копирование состояния PA6 на PC13
    	            if (GPIOA->IDR & GPIO_IDR_ID6) {
    	                GPIOC->BSRR = GPIO_BSRR_BS13;
    	            } else {
    	                GPIOC->BSRR = GPIO_BSRR_BR13;
    	            }
    	        }


/* =============== lab2 ============== */
//    	ds18b20_measure();
//    	delay(150);
//    	ds18b20_readscratchpad(dt);
//
//
//
//    	delay(1000);
/* =============== rk2 =============== */
//    	proccessrx();
//    	process_command();


    }

}
