#include "ringbuffer.h"
#include "usart.h"
#include "commands.h"
#include "main.h"

uint8_t rx_buffer[64];
RingBuffer rx_ring_buf;


int main(void) {

	SystemCoreClockUpdate();
    ledinit();
    USART2_init();
	USART2_IRQHandler();
	tim2init(1);
    buffer_init(&rx_ring_buf, rx_buffer, 64);

//	Set24MHz();
//	buttoninit();
//	EXTI_init();
//	EXTI0_IRQHandler();


    while(1){
    	proccessrx();
    	process_command();


    }

}
