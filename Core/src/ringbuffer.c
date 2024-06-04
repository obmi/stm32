#include "ringbuffer.h"



RingBuffer rx_ring_buf;

void buffer_init(RingBuffer* buf, uint8_t* buf_data, uint16_t size_buf)
{
	buf->buffer = buf_data;
	buf->size = size_buf;
	buf->tail = 0;
	buf->head = 0;
	buf->data_size = 0;
}

uint8_t buffer_put_to_end(RingBuffer* buf, uint8_t data)
{
	if(buf->data_size >= buf->size) return 1;

	buf->buffer[buf->tail] = data;
	++buf->tail;
	++buf->data_size;

	if(buf->data_size >= buf->size)
	{
		buf->tail = 0;
	}

	if(buf->tail >= buf->size)
	{
		buf->tail = 0;
	}

	return 0;
}


uint8_t buffer_get_from_front(RingBuffer* buf, uint8_t* data)
{
	if(buf->data_size <= 0)
	{
		return 1;
	}

	*data = buf->buffer[buf->head];
	++buf->head;

	if(buf->data_size > 0)
	{
		--buf->data_size;
	}

	if(buf->head >= buf->size)
	{
		buf->head = 0;
	}

	return 0;
}





