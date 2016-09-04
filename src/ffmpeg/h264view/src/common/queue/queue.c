#include <stdlib.h>
#include "queue.h"

Queue_Header Queue_Header_malloc(int size)
{
	Queue_Header m_Queue_Header;
	
	m_Queue_Header.queue = malloc(sizeof(Queue) * size);
	m_Queue_Header.size = size;
	m_Queue_Header.head = 0;
	m_Queue_Header.tail = 0;
	
	return m_Queue_Header;
}

unsigned char Queue_check_empty(Queue_Header *queue_Header)
{
	return queue_Header->tail == queue_Header->head;
}

unsigned char Queue_check_full(Queue_Header *queue_Header)
{
	return ( (queue_Header->tail + 1) % queue_Header->size) == queue_Header->head;
}

unsigned char Queue_put(Queue_Header *queue_Header, void *data)
{
	if (Queue_check_full(queue_Header)) {
		return 1;
	}
	
	queue_Header->queue[queue_Header->tail].data = data;
	queue_Header->tail = (queue_Header->tail  + 1) % queue_Header->size;
	
	return 0;
}

unsigned char Queue_get(Queue_Header *queue_Header, void *data)
{
	if ( Queue_check_empty(queue_Header) ) {
		return 1;
	}
	
	*((unsigned long *)data) = (unsigned long)queue_Header->queue[queue_Header->head].data;
	queue_Header->head = (queue_Header->head  + 1) % queue_Header->size;
	
	return 0;
}
