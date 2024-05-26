#include <stdio.h>

typedef struct list list;
typedef struct list_node list_node;

struct list {
	enum {
		is_list_end,
		is_list_node,
	} is;
	union {
		list_node *node; // Cannot be null.
		struct {} end;
	};
};

struct list_node {
	int value;
	list next;
};

void enlist(list *l, list_node *node) {
	node->next = *l;
	*l = (list){ is_list_node, node };
}

list_node *delist(list *l) {
	if (l->is == is_list_end) return 0;
	list_node *node = l->node;
	*l = l->node->next;
	return node;
}

void print_list(list l) {
	while (l.is == is_list_node) {
		list_node *node = l.node;
		printf("%d\n", node->value);
		l = node->next;
	}
}

typedef struct queue {
	list front;
	list back;
} queue;

void enqueue(queue *q, list_node *node) {
	enlist(&q->back, node);
}

list_node *dequeue(queue *q) {
	switch (q->front.is) {
	case is_list_node:
		return delist(&q->front);
	break;
	case is_list_end:
		if (q->back.is == is_list_end)
			return 0;
		while (q->back.is == is_list_node)
			enlist(&q->front, delist(&q->back));
		return dequeue(q);
	break;
	}
}

_Bool is_queue_empty(queue q) {
	return q.front.is == is_list_end && q.back.is == is_list_end;
}

queue print_queue(queue q) {
	queue q2 = { 0 };
	while (1) {
		list_node *node = dequeue(&q);
		if (node == 0)
			break;
		printf("%d\n", node->value);
		enqueue(&q2, node);
	}
	return q2;
}

int main(void) {
	list l = { 0 };

	enlist(&l, &(list_node){ 1 });
	enlist(&l, &(list_node){ 2 });
	enlist(&l, &(list_node){ 3 });

	print_list(l);

	delist(&l);
	delist(&l);
	delist(&l);

	print_list(l);

	queue q = { 0 };

	enqueue(&q, &(list_node){ 1 });
	enqueue(&q, &(list_node){ 2 });
	enqueue(&q, &(list_node){ 3 });

	q = print_queue(q);
	q = print_queue(q);
}
