#include <stm32f4xx.h>

void tim2init() {

	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	TIM2->PSC = ((SystemCoreClock / 1000000) - 1);
	TIM2->ARR = 2000 - 1;
	TIM2->CNT = 0;
	TIM2->CR1 |= TIM_CR1_CEN;
}


void toggle_LED() {
    GPIOC->ODR ^= (1 << 13);
}

void LED_OFF(){
	GPIOC->ODR |= (1 << 13);
}



void LED_ON(){
	GPIOC->ODR &= ~(1 << 13);
}

void delay(uint32_t ms) {
	for(uint32_t i = 0; i < ms; i++) {
		TIM2->SR &= ~TIM_SR_UIF;
		while (!(TIM2->SR & TIM_SR_UIF));
	}
}

void delay_us(uint32_t us){
	us *= (SystemCoreClock / 1000000) / 6;
	/* Wait till done */
	while (us--) ;
}


void port_init(){

	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;


	GPIOA->MODER &= ~(GPIO_MODER_MODER10);
	GPIOA->MODER |= (GPIO_MODER_MODER10_0); // Установка как выход
	GPIOA->OTYPER |= GPIO_OTYPER_OT10;

}

void takecontrol(){


	GPIOA->MODER &= ~(GPIO_MODER_MODER10);
	GPIOA->MODER |= (GPIO_MODER_MODER10_0); // Установка как выход
	GPIOA->OTYPER |= GPIO_OTYPER_OT10;


}

void returncontrol(){


	GPIOA->MODER &= ~(GPIO_MODER_MODER2);

	GPIOA->MODER |= GPIO_MODER_MODER2_1; 	//alt.func

	GPIOA->OTYPER |= GPIO_OTYPER_OT2;		//opendrain

	GPIOA->AFR[0] |= (7 << 8);				//AF7 - usart2


}


void Set42MHz() {

    RCC->CR |= RCC_CR_HSION;
    while ((RCC->CR & RCC_CR_HSIRDY) == 0);


    RCC->CR &= ~RCC_CR_PLLON;
    while ((RCC->CR & RCC_CR_PLLRDY) != 0);


    RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLSRC;
    RCC->PLLCFGR |= RCC_PLLCFGR_PLLSRC_HSI;



    RCC->PLLCFGR &= ~(RCC_PLLCFGR_PLLM | RCC_PLLCFGR_PLLN | RCC_PLLCFGR_PLLP);
    RCC->PLLCFGR |= (16 << 0);   // PLLM = 16
    RCC->PLLCFGR |= (192 << 6);  // PLLN = 192
    RCC->PLLCFGR |= (2 << 16);   // PLLP = 6



    RCC->CR |= RCC_CR_PLLON;
    while ((RCC->CR & RCC_CR_PLLRDY) == 0);


    RCC->CFGR &= ~RCC_CFGR_SW;
    RCC->CFGR |= RCC_CFGR_SW_PLL;
    while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);


    SystemCoreClockUpdate();
}




void ledinit(){

	    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;

	    GPIOC->MODER &= ~(GPIO_MODER_MODER13);
	    GPIOC->MODER |= GPIO_MODER_MODER13_0;

	    GPIOC->ODR |= (1 << 13);

}

void buttoninit(){
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	GPIOA->MODER |= 0b00;
}

void EXTI_init(){
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	GPIOA->OSPEEDR |= 0b11;

	EXTI->IMR |= EXTI_IMR_IM0;
	EXTI->RTSR|= EXTI_RTSR_TR0;
	EXTI->FTSR|= EXTI_FTSR_TR0;

	NVIC_EnableIRQ(EXTI0_IRQn);

}

void EXTI0_IRQHandler(){
	GPIOC->ODR ^= GPIO_ODR_OD13;
	EXTI->PR |= EXTI_PR_PR0;
}
