#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include<string.h>

typedef struct post* Position;
struct post {
	int el;
	Position next;
};

void ispis(Position);
void push(int, Position);
int pop(Position);
int PostRacun(Position);


int main() {

	struct post Head;
	Head.next = NULL;
	int n = 0;


	n = PostRacun(&Head);
	printf("\nRezultat :%d", n);




	return 0;
}

void ispis(Position p) {
	p = p->next;
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

	q = (Position)malloc(sizeof(struct post));
	q->el = x;

	q->next = s->next;
	s->next = q;
	ispis(s);
}

int pop(Position s) {
	Position temp;
	temp = s->next;
	int x = 0;

	if (temp != NULL) {
		x = temp->el;
		s->next = temp->next;
		free(temp);
		return x;
	}
	ispis(s);
}

int PostRacun(Position p) {

	int rezultat = 0;
	int integer, brojac, n;
	int a = 0, b = 0;
	char* buffer;
	char c;

	buffer = (char*)malloc(1000 * sizeof(char));

	FILE* ulz;
	ulz = fopen("postfix.txt", "r");

	if (NULL == ulz) {
		puts("\nGreska pri alokaciji!");
		return 1;
	}


	fgets(buffer, 1000, ulz);

	while (*buffer != '\0') {
		n = sscanf(buffer, "%d %n", &integer, &brojac);


		if (n == 1) {
			push(integer, p);
		}
		if (n == 0) {
			sscanf(buffer, " %c", &c);


			switch (c) {

			case '+':
				a = pop(p);
				b = pop(p);

				rezultat = a + b;
				push(rezultat, p);

				break;

			case '*':
				a = pop(p);
				b = pop(p);

				rezultat = b * a;
				push(rezultat, p);

				break;

			case '-':
				a = pop(p);
				b = pop(p);

				rezultat = b - a;
				push(rezultat, p);
				break;

			default: break;
			}
		}

		buffer += brojac;
	}

	fclose(ulz);
	rezultat = p->next->el;

	return rezultat;
}