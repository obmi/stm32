#include "commands.h"
#include "ringbuffer.h"
#include "stdbool.h"

	//	0xAB	0x01	T0		T1		#свет.	XOR
	// 	0xAB 	0x01 	0x03 	0xE8 	0x0D 	0xAF

	//	0xAB	0x02 	Сост.	X		#свет.	XOR

extern RingBuffer rx_ring_buf;


uint8_t flag = 0;
uint8_t duration;
uint8_t xor_sum = 0;
uint8_t command_data[6] = {0}; // array for command



void proccessrx(void) {

	buffer_get_from_front(&rx_ring_buf, &command_data[0]);//если в буффере чтото есть то начинаем считывать
	buffer_get_from_front(&rx_ring_buf, &command_data[1]);


        if(command_data[0] > 3 && command_data[1] > 4){
        	flag = 1;
        }
        buffer_flush(&rx_ring_buf);

//        flag = 0;


//        xor_sum = 0;
//        for (int i = 0; i < 5; i++) {		//count xor
//            xor_sum ^= command_data[i];
//        }

        // Проверяем корректность команды
//        if (xor_sum == command_data[5]) {	//if xor = xor
//
//        	if (command_data[1] == 0x01) {
//        		toggle_LED();
//        		flag = 1;
//        		duration = (command_data[2] << 8) | command_data[3];
//        		duration *= 10; 				// 1bit = 10ms
//
//        	}
//
//        	if (command_data[1] == 0x02) {
//        		flag = 2;
//
//
//        	}
//
//            // Очищаем данные команды
//            for (int i = 0; i < 5; i++) {
//                command_data[i] = 0;
//            }
//            buffer_flush(&rx_ring_buf);
//
//        }

}

void process_command() {

//	if(flag == 1) {
//
//		delay(duration);
//		toggle_LED();
//
//	}
	if(flag > 0) {
		toggle_LED();
	}
}
