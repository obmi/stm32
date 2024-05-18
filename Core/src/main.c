#include "F:\CubeMX\workspace\test\Core\inc\main.h"



int main(void){


	SystemCoreClockUpdate();
	Set24MHz();
	tim2init();
	ledinit();

	while(1){

		GPIOC->ODR ^= GPIO_ODR_OD13;
		delay(1000000);

	}



}
