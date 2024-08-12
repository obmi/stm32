#include "ringbuffer.h"
#include "usart.h"
#include "commands.h"
#include "ds18b20.h"
#include "spi.h"
#include "main.h"

uint8_t rx_buffer[256];
RingBuffer rx_ring_buf;

uint8_t dt[4] = {0,0,0,0};		//ds18b20 raw received data
uint8_t first;
uint8_t second;

int main(void) {
	SystemInit();
	SystemCoreClockUpdate();
    ledinit();
//	USART1_init();
//  USART2_init();
    USART2_halfduplex_init();
	USART2_IRQHandler();
//	Port_AltFunc_Init();
	tim2init();
//	TIM2_IRQHandler();
    buffer_init(&rx_ring_buf, &rx_buffer, 256);
	Set32MHz();
//	buttoninit();
//	EXTI_init();
//	EXTI0_IRQHandler();
	ds18b20_init();
//	TIM3_init();
//	TIM3_IRQHandler();
	spi1_init();


    while(1){



/* =============== lab2 ============== */
    	ds18b20_measure();
    	delay(300);
    	ds18b20_readscratchpad(dt);
    	delay(1200);

//    	spi1_send(dt[1]);
//    	spi1_send(dt[0]);
    	spi1_send(0x02);
    	spi1_send(0xAD);
    	delay(1000);


/* =============== rk2 =============== */
//    	proccessrx();
//    	process_command();


    }

}
