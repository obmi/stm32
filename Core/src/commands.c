#include "commands.h"
#include "ringbuffer.h"
#include "stdbool.h"


	//	0xAB	0x01	T0		T1		#свет.	XOR		//freq, xor w/o t0t1 = A7
	// 	AB		01	 	03 		E8		0D 		4C		//1000ms
	//	AB		01		00		C8		0D		6F		//200ms
	//	AB		01		0B		B8		0D		14		//3000ms

	//	0xAB	0x02 	Сост.	X		#свет.	XOR
	// 	AB		02		0		X		0D		A4		//off
	// 	AB 		02		1		X		0D		A5		//on

extern RingBuffer rx_ring_buf;

uint8_t state;
uint32_t duration = 0;
uint8_t xor_sum = 0;
uint8_t command_data[6] = {0}; // array for command



void proccessrx(void) {

	for (int i = 0; i < 6; i++) {
		if (buffer_get_from_front(&rx_ring_buf, &command_data[i]) == 0) {
			delay(10);
		} else {
			break; // if empty - break
		}
	}

	buffer_flush(&rx_ring_buf);

}

void process_command() {

	if(command_data[0] > 0) {
		for (uint8_t var = 0; var < 6; var++) {

			while (!(USART2->SR & USART_SR_TXE));

			USART2->DR = command_data[var];

			while (!(USART2->SR & USART_SR_TC));
			delay(10);
		}

		//if xor = xor
		if(command_data[1] == 0x01) {
			uint8_t T0 = command_data[2];
			uint8_t T1 = command_data[3];
			xor_sum = 0;
			for (int var = 0; var < 5; var++) {
				xor_sum ^= command_data[var];
			}
			if (xor_sum == command_data[5]) {
				//body freq
				duration = 0;
				duration = (T0 << 8) | T1;


			}
		}
		if(command_data[1] == 0x02) {
			xor_sum = 0;
			uint8_t skip = 3;
			for (int var = 0; var < 5; var++) {
				if(var != skip) {
					xor_sum ^= command_data[var];
				}
			}
			if (xor_sum == command_data[5]) {
				if(command_data[2] == 0x01) {
					//body ledon
					state = 1;
				}
				if(command_data[2] == 0x00) {
					//body ledoff
					state = 0;
				}
			}

		}

		for (int var = 0; var < 6; var++) {
			command_data[var] = 0;
		}

	}

	if(state == 0){
		LED_OFF();
	}
	if(state == 1){
		toggle_LED();
		delay(duration);
	}


}
