
/** @file
 *  Provides implementation for initialization and other management functions
 *  for ring buffer module.
 *
 */

/*******************************************************************************
*                          Include Files
*******************************************************************************/

#include <string.h>
#include "ring_buffer.h"

/*******************************************************************************
*                          Extern Data Declarations
*******************************************************************************/

/*******************************************************************************
*                          Extern Function Declarations
*******************************************************************************/

/*******************************************************************************
*                          Type & Macro Definitions
*******************************************************************************/
#define min(a, b)		((a < b) ? (a) : (b))

/*******************************************************************************
*                          Static Function Prototypes
*******************************************************************************/

/*******************************************************************************
*                          Static Data Definitions
*******************************************************************************/

/*******************************************************************************
*                          Extern/Exported Data Definitions
*******************************************************************************/

/*******************************************************************************
*                          Extern/Exported  Function Definitions
*******************************************************************************/

void ring_buffer_init(ring_buffer_t* ring_buffer, uint8_t* buffer, uint16_t size)
{
    ring_buffer->buffer     = buffer;
    ring_buffer->size       = size;
    ring_buffer->tail       = 0;
    ring_buffer->head       = 0;
}

void ring_buffer_deinit(ring_buffer_t* ring_buffer)
{
    (void)(ring_buffer);
}

uint16_t ring_buffer_write(ring_buffer_t* ring_buffer, const uint8_t* data, uint16_t data_length)
{
    uint16_t head_to_end = ring_buffer->size - ring_buffer->head;

    /* Calculate the maximum amount we can copy. "Minus one" below is to avoid having tail == head after filling up the buffer.  */
    uint16_t amount_to_copy = min(data_length, (ring_buffer->head == ring_buffer->tail) ? ring_buffer->size - 1: (head_to_end + ring_buffer->tail) % ring_buffer->size - 1);
	
    /* Copy as much as we can until we fall off the end of the buffer */
    memcpy(&ring_buffer->buffer[ring_buffer->head], data, min(amount_to_copy, head_to_end));

    /* Check if we have more to copy to the front of the buffer */
    if (head_to_end < amount_to_copy)
    {
        memcpy(&ring_buffer->buffer[0], data + head_to_end, amount_to_copy - head_to_end);
    }

    /* Update the head */
    ring_buffer->head = (ring_buffer->head + amount_to_copy) % ring_buffer->size;

    return amount_to_copy;
}

void ring_buffer_get_data(ring_buffer_t* ring_buffer, uint8_t** data, uint16_t* contiguous_bytes)
{
    uint32_t tail_to_end = ring_buffer->size - ring_buffer->tail;

    *data = &ring_buffer->buffer[ring_buffer->tail];
    *contiguous_bytes = min(tail_to_end, (tail_to_end + ring_buffer->head) % ring_buffer->size);
}

void ring_buffer_consume(ring_buffer_t* ring_buffer, uint16_t bytes_consumed)
{
    ring_buffer->tail = (ring_buffer->tail + bytes_consumed) % ring_buffer->size;
}

uint16_t ring_buffer_read_byte(ring_buffer_t* ring_buffer, uint8_t* data)
{
    if (ring_buffer->tail == ring_buffer->head) {
		return 0;
	}

	*data = ring_buffer->buffer[ring_buffer->tail++];
	ring_buffer->tail %= ring_buffer->size;
	return 1;
}

uint16_t ring_buffer_free_space(ring_buffer_t* ring_buffer)
{
    uint32_t head_to_end = ring_buffer->size - ring_buffer->head;
    return ((head_to_end + ring_buffer->tail) % ring_buffer->size - 1);
}

uint16_t ring_buffer_used_space(ring_buffer_t* ring_buffer)
{
    uint32_t tail_to_end = ring_buffer->size - ring_buffer->tail;
    return ((tail_to_end + ring_buffer->head) % ring_buffer->size);
}

uint8_t ring_buffer_is_empty(ring_buffer_t *ring_buffer)
{
	return (ring_buffer->tail == ring_buffer->head);
}

/*******************************************************************************
*                          Static Function Definitions
*******************************************************************************/

/*******************************************************************************
*                          End of File
*******************************************************************************/
