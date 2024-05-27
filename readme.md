queues.c is an implementation which uses tagged unions to distinquish empty and non-empty lists. It's a bit too verbose.

Both queues.c and queues2.c use two linked lists to work. Enqueues are done to the back. Dequeues are done from the front if front is non-empty. If front is empty, dequeue reverses the back and puts it to the front and then tries to dequeue from the front.

queues2.c, unlike the previuous implementation, uses a conventional way to represent empty lists, by using a pointer to null as a signifier of that.

queues3.c uses one linked list instead of two. The back is used to point to the end of the list, where the enqueues are made to. Dequeues are made from the front.

queues4.c uses an array and allocates memory by itself, unlike previous implementations. The enqueue_at and dequeue_at indicies are used for corresponding purposes. Initially, capacity of the queue is zero. When enqueueing, if the queue is full, a reallocation happens. Old backing array is freed and a new one is created. New size is calculated by the following formula: old array's capacity * 2 + 1. The old backing array is freed. Furthermore, if all elements are dequeued from the queue, the array is freed and the queue is reset to zero. Dequeue returns false if the queue is empty. Enqueue returns false in case of an allocation failure during resizing, without modifying the queue.
