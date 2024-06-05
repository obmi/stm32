#include "usart.h"
#include "ringbuffer.h"
#include "commands.h"
#include "main.h"

uint8_t rx_buffer[64];


int main(void) {

	SystemCoreClockUpdate();
    ledinit();
    USART2_init();
    buffer_init(&rx_ring_buf, rx_buffer, 64);


//	Set24MHz();
//	USART2_IRQHandler();
//	tim2init(1);
//	buttoninit();
//	EXTI_init();
//	EXTI0_IRQHandler();


    while(1){
    	proccess();


    }

}
