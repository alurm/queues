#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct queue {
	int enqueue_at;
	int dequeue_at;
	int capacity;
	int *array;
} queue;

_Bool enqueue(queue *q, int value) {
	if (q->enqueue_at == q->capacity) {
		int new_capacity = q->capacity * 2 + 1;
		int *new_array = malloc(new_capacity * sizeof(int));
		if (new_array == 0)
			return 0;
		memcpy(new_array, q->array + q->dequeue_at, q->capacity * sizeof(int));
		free(q->array);

		q->capacity = new_capacity;
		q->array = new_array;
		q->enqueue_at -= q->dequeue_at;
		q->dequeue_at = 0;
	}

	q->array[q->enqueue_at] = value;
	q->enqueue_at++;

	return 1;
}

_Bool dequeue(queue *q, int *value) {
	if (q->enqueue_at == q->dequeue_at)
		return 0;

	*value = q->array[q->dequeue_at];
	q->dequeue_at++;

	if (q->enqueue_at == q->dequeue_at) {
		free(q->array);
		*q = (queue){ 0 };
	}

	return 1;
}

// Queue q is passed as a pointer in case of an allocation failure.
// In that case caller can inspect modified fields of original queue.
// Caller can save the value that was failed to get enqueued in the corresponding field.
// If moving is successful, value of failed_to_enqueue will be unchanged.
// Success of the call can be verified by checking that original's queue's
queue print_and_move_queue(queue *q, int *failed_to_enqueue) {
	queue q2 = { 0 };
	for (;;) {
		int value;
		if (!dequeue(q, &value))
			break;
		printf("%d\n", value);
		if (!enqueue(&q2, value)) {
			*failed_to_enqueue = value;
			break;
		}
	}
	return q2;
}

int main(void) {
	queue q = { 0 };
	enqueue(&q, 1);
	enqueue(&q, 2);
	enqueue(&q, 3);

	dequeue(&q, &(int){ 0 });
	dequeue(&q, &(int){ 0 });
	dequeue(&q, &(int){ 0 });

	enqueue(&q, 3);
	enqueue(&q, 4);
	enqueue(&q, 5);

	q = print_and_move_queue(&q, &(int){ 0 });

	dequeue(&q, &(int){ 0 });

	q = print_and_move_queue(&q, &(int){ 0 });
}
