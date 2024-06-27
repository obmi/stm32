#include "ringbuffer.h"
#include "usart.h"
#include "commands.h"
#include "ds18b20.h"
#include "main.h"

uint16_t rx_buffer[256];
RingBuffer rx_ring_buf;


uint8_t status;
uint8_t dt[8];		//ds18b20 raw received data

int main(void) {
	SystemInit();
	SystemCoreClockUpdate();
    ledinit();
//    USART2_init();
    USART2_halfduplex_init();
//    port_init();
	USART2_IRQHandler();
	tim2init();
//	TIM2_IRQHandler();
    buffer_init(&rx_ring_buf, &rx_buffer, 256);
	Set42MHz();
//	buttoninit();
//	EXTI_init();
//	EXTI0_IRQHandler();
	ds18b20_init();


    while(1){

/* =============== lab2 ============== */
    	ds18b20_measure();
    	delay(150);
    	ds18b20_readscratchpad(dt);
    	ow_receive(dt, 8);

//    	for (uint8_t i = 0; i < 8; i++) {
//			USART2_send(dt[i]);
//			delay(2000);
//		}

    	delay(1000);
/* =============== rk2 =============== */
//    	proccessrx();
//    	process_command();


    }

}
