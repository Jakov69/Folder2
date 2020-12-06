#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct oba* Position;
struct oba {
	int el;
	Position next;
};

void ispis(Position);
void push(int, Position);
int pop(Position);
void brisisvekraj(Position);

int main() {
	srand(time(0));

	struct oba Head;
	Head.next = NULL;

	printf("Stog:  \n");
	push((10 + rand() % (100 - 10 + 1)), &Head);
	ispis(Head.next);
	push(3, &Head);
	ispis(Head.next);
	push(4, &Head);
	ispis(Head.next);


	pop(&Head);
	ispis(Head.next);
	pop(&Head);
	ispis(Head.next);
	printf("\n-----------------------------\n");

	printf("Red:    \n");
	push((10 + rand() % (100 - 10 + 1)), &Head);
	ispis(Head.next);
	push((10 + rand() % (100 - 10 + 1)), &Head);
	ispis(Head.next);

	brisisvekraj(&Head);
	ispis(Head.next);
	brisisvekraj(&Head);
	ispis(Head.next);

	return 1;
}

void ispis(Position p) {

	if (p == NULL) {
		printf("Stog je prazan!\n");
		return;
	}
	while (p != NULL) {
		printf("%d ", p->el);
		p = p->next;
	}
	printf("\n");
}

void push(int x, Position s) {
	Position q;

	q = (Position)malloc(sizeof(struct oba));
	q->el = x;

	q->next = s->next;
	s->next = q;

}

int pop(Position s) {
	Position temp;
	temp = s->next;
	int x = 0;

	if (temp != NULL) {
		x = temp->el;
		s->next = temp->next;
		free(temp);
	}

	return s;
}

void brisisvekraj(Position p) {
	Position temp = p;
	p = p->next;

	while (p->next != NULL) {
		temp = p;
		p = p->next;
	}
	free(p);
	temp->next = NULL;

}