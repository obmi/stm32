#include <stm32f4xx.h>


void tim2init(uint8_t psc) {

	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	TIM2->PSC = SystemCoreClock / 1000000 - 1;
	TIM2->ARR = 1000000*psc - 1;
	TIM2->CNT = 0;
	TIM2->CR1 |= TIM_CR1_CEN;
}

void toggle_LED() {
    GPIOC->ODR ^= (1 << 13);
}

void delay(uint32_t us) {
	uint32_t start = TIM2->CNT;
    while ((TIM2->CNT - start) < us);
}

void Set24MHz() {

    RCC->CR |= RCC_CR_HSION;
    while ((RCC->CR & RCC_CR_HSIRDY) == 0);


    RCC->CR &= ~RCC_CR_PLLON;
    while ((RCC->CR & RCC_CR_PLLRDY) != 0);


    RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLSRC;
    RCC->PLLCFGR |= RCC_PLLCFGR_PLLSRC_HSI;



    RCC->PLLCFGR &= ~(RCC_PLLCFGR_PLLM | RCC_PLLCFGR_PLLN | RCC_PLLCFGR_PLLP);
    RCC->PLLCFGR |= (16 << 0);   // PLLM = 16
    RCC->PLLCFGR |= (192 << 6);  // PLLN = 192
    RCC->PLLCFGR |= (3 << 16);   // PLLP = 8


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

	    GPIOC->ODR &= ~(1 << 13);

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
