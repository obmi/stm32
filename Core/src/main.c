#include "main.h"
#include "usart.h"




int main(void){

	SystemCoreClockUpdate();
	Set24MHz();
	usart2_init();
	USART2_IRQHandler();
//	tim2init();
//	ledinit();
//	buttoninit();
//	EXTI_init();
//	EXTI0_IRQHandler();


	while(1){
//		GPIOC->ODR |= GPIO_ODR_OD13;
//		delay(1000000);

		usart2_send(0x43);


	}



}
