#include <stdio.h>

typedef struct list_node {
	int value;
	struct list_node *list;
} list_node;

void enlist(list_node **list, list_node *node) {
	node->list = *list, *list = node;
}

list_node *delist(list_node **list) {
	list_node *node = *list;
	if (node == 0) return 0;
	else {
		*list = (*list)->list;
		return node;
	}
}

void print_list(list_node *list) {
	while (list) printf("%d\n", list->value), list = list->list;
}

typedef struct queue {
	list_node *front;
	list_node *back;
} queue;

void enqueue(queue *q, list_node *node) {
	enlist(&q->back, node);
}

list_node *dequeue(queue *q) {
	if (q->front) return delist(&q->front);
	else {
		while (q->back) enlist(&q->front, delist(&q->back));
		if (q->front == 0) return 0;
		return dequeue(q);
	}
}

queue print_queue(queue q) {
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
	list_node *list = 0;

	enlist(&list, &(list_node){ 1 });
	enlist(&list, &(list_node){ 2 });

	print_list(list);

	delist(&list);
	delist(&list);

	print_list(list);

	queue q = { 0 };

	enqueue(&q, &(list_node){ 3 });
	enqueue(&q, &(list_node){ 4 });
	enqueue(&q, &(list_node){ 5 });

	q = print_queue(q);

	q = print_queue(q);
}
