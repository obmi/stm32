#include "ds18b20.h"
#include "ringbuffer.h"

#define RESOLUTION_9BIT 0x1F

#define RESOLUTION_10BIT 0x3F

#define RESOLUTION_11BIT 0x5F

#define RESOLUTION_12BIT 0x7F

#define RESET_BAUDRATE 	0xD05	//9600
#define LIVE_BAUDRATE 	0x116	//115200

extern RingBuffer rx_ring_buf;

uint8_t store[6] = {0};



void ds18b20_pin_output() {
    GPIOA->MODER &= ~(GPIO_MODER_MODER2);
    GPIOA->MODER |= (GPIO_MODER_MODER2_0);
}

void ds18b20_pin_input() {
    GPIOA->MODER &= ~(GPIO_MODER_MODER2);
}

void ds18b20_write_low() {
    GPIOA->ODR &= ~GPIO_ODR_OD2;
}

void ds18b20_write_high() {
    GPIOA->ODR |= GPIO_ODR_OD2;
}




uint8_t ds18b20_reset() {


//	uint16_t presence = 13;
//
//	ds18b20_pin_output();
//	ds18b20_write_low();
//	delay_us(480); //530us
//	ds18b20_pin_input();
//	delay_us(50);
//
//
//	presence = GPIOA->IDR & GPIO_IDR_ID2;
//	delay(1);
//
//	if(presence == 0){
//		toggle_LED();
//	}
//
//
//	return (presence ? 1 : 0);

	USART2_setbaudrate(0xD05);				//9600
	delay_us(500);
	USART2_send(0xF0);						//reset condition timing
	delay_us(500);
	USART2_setbaudrate(0x116);				//115200

}



uint8_t ds18b20_readbit(){

	delay(1);

	uint8_t bit;
//
//	ds18b20_pin_output();
//	ds18b20_write_low();
//
//	delay_us(3); //5
//
//	ds18b20_pin_input();
//
//	delay_us(7); //9.5
//
//	bit = (GPIOA->IDR & GPIO_IDR_ID2 ? 1 : 0);
//
//
//	delay_us(40); //45

	ds18b20_writebit(0xFF); //low for 8us , then master read
	bit = USART2_read();


	return bit;
}



void ow_receive(void *buf, unsigned int size)
{
    uint8_t *p=(uint8_t *)buf;
    for(unsigned int i=0; i<size; i++, p++)
        *p=ds18b20_readbit();
}


uint8_t ds18b20_readbyte(){
	uint8_t data = 0;
	for (uint8_t i = 0; i <= 7; i++){
		data += ds18b20_readbit() << i;
	}

	return data;
}


void ds18b20_writebit(uint8_t bit){

//	ds18b20_pin_output();
//	ds18b20_write_low();
//
//	delay_us(bit ? 1 : 65); // 3:67
//
//	ds18b20_pin_input();
//
//	delay_us(bit ? 65 : 1);



	USART2_send(bit ? 0xFF : 0x00);				//ff - send1 timing : 00 - send0 timing
	while (!(USART2->SR & USART_SR_TC));

}

void ds18b20_writebyte(uint8_t dt){

	delay(1);

	for (uint8_t i = 0; i < 8; i++) {
		ds18b20_writebit((dt >> i) & 0x01);
	}

}

uint8_t ds18b20_init(){

	ds18b20_reset();
	ds18b20_writebyte(0xCC); // skip rom
	ds18b20_writebyte(0x4E); // write scratchpad
	ds18b20_writebyte(0x64); //	th = 100
	ds18b20_writebyte(0x9E); // tl = -30

	ds18b20_writebyte(RESOLUTION_12BIT);

	return 0;
}


void ds18b20_measure(){

	ds18b20_reset();

	ds18b20_writebyte(0xCC); //skiprom
	ds18b20_writebyte(0x44); //convert t

}


void ds18b20_readscratchpad(uint8_t *data){

	ds18b20_reset();
	ds18b20_writebyte(0xCC); //skiprom
	ds18b20_writebyte(0xBE); //read scratchpad

	uint8_t *p=(uint8_t *)data;
	for (uint8_t i = 0; i < 8; i++, p++) {
		data[i] = ds18b20_readbyte();
		*p=ds18b20_readbit();

	}





}




