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


void TIM3_init()
{

//	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
//
//	TIM3->PSC = 31;  // Предделитель таймера (84 MHz / (83 + 1) = 1 MHz)
//	TIM3->ARR = 1000;
//
//	TIM3->CCMR1 |= (6 << 4);
//	TIM3->CCMR1 |=	TIM_CCMR1_OC1PE;
//
//	TIM3->CCER |= TIM_CCER_CC1E;
//
//	TIM3->CCR1 = 0;
//
//	TIM3->CR1 |= TIM_CR1_CEN;
	RCC->APB1ENR |=RCC_APB1ENR_TIM3EN; //тактироване TIM3

//	    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;//включаем тактирование System configuration controller
	    TIM3->CR1 &= ~TIM_CR1_UDIS; // событие update?
	    TIM3->CR1 &= ~TIM_CR1_URS; // генерировать прерывания только при переполнении счетчика таймера
	    TIM3->CR1 &= ~TIM_CR1_OPM; //one plus mode?
	    TIM3->CR1 &= ~TIM_CR1_DIR; // upcounter
	    TIM3->CR1 &= ~TIM_CR1_CMS_Msk; //выравнивание по краю
	    TIM3->CR1 |= TIM_CR1_ARPE; //автоматическая перезагрузка
	    TIM3->CR1 &= ~TIM_CR1_CKD_Msk; // prescaler off
	    TIM3->DIER |= TIM_DIER_UIE; // Update interrupt enable





	        TIM3->CCER |= TIM_CCER_CC1E; // включение 3-го канала в режиме захвт-сравнение
	        TIM3->CR1 |= TIM_CR1_ARPE; //зачем то нужно
	        TIM3->CCMR1 &= ~TIM_CCMR1_OC1M_Msk;
	        TIM3->CCMR1 |= TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2; // mode PWM1
	        TIM3->CCMR1 |= TIM_CCMR1_OC1PE; // preload ARR

	        TIM3->PSC = 32-1; //10kHz
	        TIM3->ARR = 1000-1;
//	        TIM3->CCR2 = 10;

	    NVIC_EnableIRQ(TIM3_IRQn); // разрешаем прерывания по таймеру 3
	    TIM3->EGR |= TIM_EGR_UG; //генерация событий?
	    TIM3->CR1 |= TIM_CR1_CEN; //включение счетчика таймера

}

void Port_AltFunc_Init()
    {

	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

	GPIOA->MODER &= ~(GPIO_MODER_MODER6);
	GPIOA->MODER |= GPIO_MODER_MODER6_1;

	GPIOA->AFR[0] &= ~(0xF << (6 * 4));

	GPIOA->AFR[0] |= (2 << (6 * 4));

    }

void TIM3_IRQHandler(){
    if(READ_BIT(TIM3->SR, TIM_SR_UIF))
    {
        TIM3->SR &= ~TIM_SR_UIF_Msk; // сброс флага прерывания
    }


}
