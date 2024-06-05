#include "commands.h"
#include "ringbuffer.h"



void proccess(){

	uint8_t data;
	if (buffer_get_from_front(&rx_ring_buf, &data) == 0){
		if (data > 10) {
			toggle_LED();
		} else {

		}
	}

}
