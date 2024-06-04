#include "main.h"
#include "usart.h"





int main(void) {


    ledinit();
    USART2_init();
	SystemCoreClockUpdate();

	USART2_send();
//	Set24MHz();
//	USART2_IRQHandler();
//	tim2init(1);
//	buttoninit();
//	EXTI_init();
//	EXTI0_IRQHandler();


    while (1) {

        if (USART2->SR & USART_SR_RXNE) {
            uint8_t data = USART2->DR;
            toggle_LED();

            USART2_send();
        }
    }
}
