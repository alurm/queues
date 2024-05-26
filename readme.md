queues.c is an implementation which uses tagged unions to distinquish empty and non-empty lists. It's a bit too verbose.

Both queues.c and queues2.c use two linked lists to work. Enqueues are done to the back. Dequeues are done from the front if front is non-empty. If front is empty, dequeue reverses the back and puts it to the front and then tries to dequeue from the front.

queues2.c uses a more conventional way to represent empty lists, by using a pointer to null as a signifier of that.

queues3.c uses one linked list instead of two. The back is used to point to the end of the list, where the enqueues are made to. Dequeues are made from the front.
