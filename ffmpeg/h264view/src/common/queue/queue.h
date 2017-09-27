#ifndef __QUEUE_H_
#define __QUEUE_H_

typedef struct {
	void *data;
}Queue;

typedef struct {
	Queue *queue;//queue array
	long size;//usefull size = size - 1
	int head;//get postion
	int tail;//put postion
}Queue_Header;

Queue_Header Queue_Header_malloc(int size);
unsigned char Queue_check_empty(Queue_Header *queue_Header);
unsigned char Queue_check_full(Queue_Header *queue_Header);
unsigned char Queue_put(Queue_Header *queue_Header, void *data);
unsigned char Queue_get(Queue_Header *queue_Header, void *data);

#endif
