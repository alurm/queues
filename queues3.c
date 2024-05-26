#include <stdio.h>

typedef struct list_node {
	int value;
	struct list_node *list;
} list_node;

typedef struct queue {
	list_node *front; // Dequeue from here.
	list_node *back; // Enqueue to here.
} queue;

// When we enqueue,
// we grow the back by one if it's non null and shift the back to point to the new node,
// otherwise we set the front and the back to the given node.
void enqueue(queue *q, list_node *node) {
	if (q->back) {
		q->back->list = node;
		q->back = node;
	} else {
		q->back = node;
		q->front = node;
	}
}

// When we dequeue,
// we move the front by one if it's non null and return the node we shifted,
// otherwise we return null (since the queue is empty).
list_node *dequeue(queue *q) {
	if (q->front) {
		list_node *node = q->front;
		q->front = q->front->list;
		return node;
	} else {
		return 0;
	}
}

queue print_and_reverse_queue(queue q) {
	queue q2 = { 0 };
	for (;;) {
		list_node *node = dequeue(&q);
		if (!node) break;
		printf("%d\n", node->value);
		enqueue(&q2, node);
	}
	return q2;
}

int main(void) {
	queue q = { 0 };

	enqueue(&q, &(list_node){ 3 });
	enqueue(&q, &(list_node){ 4 });
	enqueue(&q, &(list_node){ 5 });

	q = print_and_reverse_queue(q);

	q = print_and_reverse_queue(q);
}
