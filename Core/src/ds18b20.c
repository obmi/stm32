#include "ds18b20.h"
#include "ringbuffer.h"

extern RingBuffer rx_ring_buf;


uint8_t store[6] = {0};


void OneWire_Init() {

	for (uint8_t i = 0; i < 6; i++) {
		if (buffer_get_from_front(&rx_ring_buf, &store[i]) == 0) {
			delay(10);
		} else {
			break; // if empty - break
		}
	}

	buffer_flush(&rx_ring_buf);

	if(store[0] > 0) {
		for (uint8_t i = 0; i < 6; i++) {
			USART2->DR = store[i];
		}
	}

	for(uint8_t i = 0; i < 6; i++) {
		store[i] = 0;
	}

}

uint8_t OneWire_readbit(void) {

	uint8_t bit = 0;

	GPIOA->ODR &= ~GPIO_ODR_OD2;//низкий уровень

	delay(2);

	GPIOA->ODR |= GPIO_ODR_OD2;//высокий уровень

	delay(2);

	bit = (GPIOB->IDR & GPIO_IDR_ID2 ? 1 : 0);//проверяем уровень

	delay(2);

	return bit;
}


uint8_t OneWire_readbyte(void) {

  uint8_t data = 0;

  for (uint8_t i = 0; i <= 7; i++)

  data += OneWire_readbit() << i;

  return data;

}


