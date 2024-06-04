#include <stdio.h>
#include <stdint.h>

//		init				put_to_end (x4)				get_from_front (x1)
// [][][][][][][][]			[][][][][][][][]			[][][][][][][][]
// ^						^		^					  ^		^
// |head					|		|					  |		|
// |tail					head	tail				head   tail
//

typedef struct
{
	uint8_t* buffer;
	uint16_t size;
	uint16_t data_size;
	uint16_t tail;
	uint16_t head;
} RingBuffer;

void buffer_init(RingBuffer* buf, uint8_t* buf_data, uint16_t size_buf);
uint8_t buffer_put_to_end(RingBuffer* buf, uint8_t data);
uint8_t buffer_get_from_front(RingBuffer* buf, uint8_t* data);

