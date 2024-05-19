#include "main.h"



int main(void){


	SystemCoreClockUpdate();
	Set24MHz();
	tim2init();
	ledinit();
	buttoninit();
	EXTI_init();
	EXTI0_IRQHandler();


	while(1){

		//GPIOC->ODR ^= GPIO_ODR_OD13;
		//delay(1000000);

	}



}
