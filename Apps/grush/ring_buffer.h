
/** @file
 *  Provides implementation for initialization and other management functions
 *  for ring buffer module.
 *
 */

#ifndef __RING_BUFFER__
#define __RING_BUFFER__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
*                          Include Files
*******************************************************************************/

/*******************************************************************************
*                          C++ Declaration Wrapper
*******************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
*                          Type & Macro Declarations
******************************************************************************/

/**
 *  Ring Buffer data structure
 */
typedef struct
{
    uint8_t*  buffer;
    uint16_t  size;
    uint16_t  head;
    uint16_t  tail;
} ring_buffer_t;

/*******************************************************************************
*                          Extern Data Declarations
*******************************************************************************/

/*******************************************************************************
*                          Extern Function Prototypes
*******************************************************************************/

void ring_buffer_init(ring_buffer_t* ring_buffer, uint8_t* buffer, uint16_t size);

void ring_buffer_deinit(ring_buffer_t* ring_buffer);

uint16_t ring_buffer_write(ring_buffer_t* ring_buffer, const uint8_t* data, uint16_t data_length);

uint16_t ring_buffer_used_space(ring_buffer_t* ring_buffer);

uint16_t ring_buffer_free_space(ring_buffer_t* ring_buffer);

void ring_buffer_get_data(ring_buffer_t* ring_buffer, uint8_t** data, uint16_t* contiguous_bytes);

void ring_buffer_consume(ring_buffer_t* ring_buffer, uint16_t bytes_consumed);

uint16_t ring_buffer_read_byte(ring_buffer_t *ring_buffer, uint8_t *data);

uint8_t ring_buffer_is_empty(ring_buffer_t *ring_buffer);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif

/*******************************************************************************
*                          End of File
*******************************************************************************/

