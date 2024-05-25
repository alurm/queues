#include <stdio.h>
#include <assert.h>

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

void add_node_to_list(list *l, list_node *node) {
	node->next = *l;
	*l = (list){ is_list_node, node };
}

list_node *remove_node_from_list(list *l) {
	assert(l->is == is_list_node);
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
	add_node_to_list(&q->back, node);
}

list_node *dequeue(queue *q) {
	switch (q->front.is) {
	case is_list_node:
		return remove_node_from_list(&q->front);
	break;
	case is_list_end:
		assert(q->back.is == is_list_node);
		while (q->back.is == is_list_node)
			add_node_to_list(&q->front, remove_node_from_list(&q->back));
		return dequeue(q);
	break;
	}
}

_Bool is_queue_empty(queue q) {
	return q.front.is == is_list_end && q.back.is == is_list_end;
}

queue print_and_reverse_queue(queue q) {
	queue q2 = { 0 };
	while (!is_queue_empty(q)) {
		list_node *node = dequeue(&q);
		printf("%d\n", node->value);
		enqueue(&q2, node);
	}
	return q2;
}

int main(void) {
	list l = { 0 };

	add_node_to_list(&l, &(list_node){ 1 });
	add_node_to_list(&l, &(list_node){ 2 });
	add_node_to_list(&l, &(list_node){ 3 });

	print_list(l);

	remove_node_from_list(&l);
	remove_node_from_list(&l);
	remove_node_from_list(&l);

	print_list(l);

	queue q = { 0 };

	enqueue(&q, &(list_node){ 1 });
	enqueue(&q, &(list_node){ 2 });
	enqueue(&q, &(list_node){ 3 });

	q = print_and_reverse_queue(q);
	q = print_and_reverse_queue(q);
}