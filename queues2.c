#include <stdio.h>

typedef struct list_node {
	int value;
	struct list_node *list;
} list_node;

void add_node_to_list(list_node **list, list_node *node) {
	node->list = *list, *list = node;
}

list_node *remove_node_from_list(list_node **list) {
	list_node *node = *list;
	*list = (*list)->list;
	return node;
}

void print_list(list_node *list) {
	while (list) printf("%d\n", list->value), list = list->list;
}

typedef struct queue {
	list_node *front;
	list_node *back;
} queue;

void enqueue(queue *q, list_node *node) {
	add_node_to_list(&q->back, node);
}

list_node *dequeue(queue *q) {
	if (q->front) return remove_node_from_list(&q->front);
	else {
		while (q->back) add_node_to_list(&q->front, remove_node_from_list(&q->back));
		if (q->front == 0) return 0;
		return dequeue(q);
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
	list_node *list = 0;

	add_node_to_list(&list, &(list_node){ 1 });
	add_node_to_list(&list, &(list_node){ 2 });

	print_list(list);

	remove_node_from_list(&list);
	remove_node_from_list(&list);

	print_list(list);

	queue q = { 0 };

	enqueue(&q, &(list_node){ 3 });
	enqueue(&q, &(list_node){ 4 });
	enqueue(&q, &(list_node){ 5 });

	q = print_and_reverse_queue(q);

	q = print_and_reverse_queue(q);
}
