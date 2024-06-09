	#include "ringbuffer.h"


	void buffer_init(RingBuffer* buf, uint8_t* buffer_array, uint16_t size) {
		buf->buffer = buffer_array;
		buf->size = size;
		buf->head = 0;
		buf->tail = 0;
		buf->data_size = 0;
	}


	uint8_t buffer_put_to_end(RingBuffer* buf, uint8_t data) {
	    if (buf->data_size >= buf->size) {
	        return 1; //переполнен
	    }
	    buf->buffer[buf->tail] = data;
	    buf->tail = (buf->tail + 1) % buf->size;
	    buf->data_size++;
	    return 0;
	}

	uint8_t buffer_get_from_front(RingBuffer* buf, uint8_t* data) {
	    if (buf->data_size <= 0) {
	        return 1; // пуст
	    }
	    *data = buf->buffer[buf->head];
	    buf->head = (buf->head + 1) % buf->size;
	    buf->data_size--;
	    return 0;
	}

	void buffer_flush(RingBuffer* buf) {
	    buf->head = buf->tail = buf->data_size = 0;
	}
