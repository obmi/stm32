#include "ringbuffer.h"
#include "usart.h"
#include "commands.h"
#include "ds18b20.h"
#include "main.h"

uint16_t rx_buffer[256];
RingBuffer rx_ring_buf;


int main(void) {
	SystemInit();
	SystemCoreClockUpdate();
    ledinit();
//    USART2_init();
    USART2_halfinit();
	USART2_IRQHandler();
	tim2init(1);
    buffer_init(&rx_ring_buf, &rx_buffer, 256);

//	Set24MHz();
//	buttoninit();
//	EXTI_init();
//	EXTI0_IRQHandler();


    while(1){

//    	OneWire_Init();

/* =============== rk2 =============== */
//    	proccessrx();
//    	process_command();


    }

}
