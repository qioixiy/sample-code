#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

#define Printf(s) printf(#s "=%d\n", s)

int main() {

	int queue_size = 100;
	unsigned int data;
	
	Queue_Header queue_Header = Queue_Header_malloc(queue_size);
	Printf(queue_Header.size);
	Printf(queue_Header.head);
	Printf(queue_Header.tail);
	
	for (int i= 0; i < queue_size; i++) {
		if ( 0 != Queue_put(&queue_Header, (void *)i)) {
			printf("Queue_put error %d\n", i);
			Printf(queue_Header.head);
			Printf(queue_Header.tail);
		}
	}
	for (int i = 0; i < queue_size; i++) {
		if ( 0 == Queue_get(&queue_Header, (void *)&data)) {
			printf("Queue_get %d\n", data);
		}
	}
	Printf(queue_Header.head);
	Printf(queue_Header.tail);
	
	Queue_put(&queue_Header, 0);
	Printf(queue_Header.head);
	Printf(queue_Header.tail);
	
	Queue_get(&queue_Header, (void *)&data);
	Printf(queue_Header.head);
	Printf(queue_Header.tail);
	
	return 0;
}