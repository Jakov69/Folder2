#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct polinom;
typedef struct polinom* Position;
typedef struct polinom {
	int coef;
	int exp;
	Position next;
}Pol;

void sumaPol(Position, Position, Position);
Position stvoriPol(int, int);
void citajPol(char*, Position);
void ispisPol(Position);
void unos(Position, Position);
Position nm(Position, Position);
void sortPol(int, int, Position);


int main() {
	Pol head1, head2, head3;
	head1.next = NULL;
	head2.next = NULL;
	head3.next = NULL;

	citajPol("Prvi.txt", &head1);
	citajPol("Drugi.txt", &head2);

	printf("\nPrvi polinom:\n");
	ispisPol(&head1);

	printf("\nDrugi polinom:\n");
	ispisPol(&head2);

	printf("\nSuma polinoma:\n");
	sumaPol(&head1, &head2, &head3);
	ispisPol(&head3);

	return 0;
}
void citajPol(char*d, Position x) {

	int coef = 0, exp = 0;
	FILE *ulz;
	ulz = fopen(d, "r");

	if (NULL == ulz) printf("Greska pri alokaciji! ");

	while (feof(ulz) == 0) {

		fscanf(ulz, "%d %d", &coef, &exp);
		sortPol(exp, coef, x);

	}
	fclose(ulz);
}
void sortPol(int exp, int coef, Position x) {
	Position p;
	while (x->next != NULL && x->next->exp < exp)
		x = x->next;

	p = stvoriPol(coef, exp);

	p->next = x->next;
	x->next = p;
}

Position stvoriPol(int coef, int exp) {
	Position p = NULL;

	p = (Position)malloc(sizeof(Pol));

	p->coef = coef;
	p->exp = exp;

	return p;

}

void ispisPol(Position head) {
	Position p = NULL;

	for (p = head->next; p != NULL; p = p->next)
	{
		if (p->coef != 0)
			printf("+"); printf("%dx^%d", p->coef, p->exp);

	}

	printf("\n");

}

void unos(Position x, Position y) {

	while (x->next != NULL)
		x = x->next;

	y->next = x->next;
	x->next = y;
}

Position nm(Position p, Position q) {

	if (p->exp < q->exp)
		return p;
	else
		return q;

}

void sumaPol(Position p, Position q, Position head) {
	Position a = NULL;
	Position b = NULL;

	int coef = 0, exp = 0;

	p = p->next;
	q = q->next;

	while (p != NULL && q != NULL)
	{
		if (p->exp == q->exp)
		{
			coef = p->coef + q->coef;
			if (coef == 0)
			{
				p = p->next;
				q = q->next;
			}
			else
			{
				exp = p->exp;
				b = stvoriPol(coef, exp);
				unos(head, b);

				p = p->next;
				q = q->next;
			}
		}
		else
		{
			a = nm(p, q);
			if (a->coef == 0);
			else
			{
				b = stvoriPol(a->coef, a->exp);
				unos(head, b);
			}
			if (a == p)
				p = p->next;
			else
				q = q->next;
		}
	}
	if (p == NULL)
	{
		while (q != NULL)
		{
			if (q->coef == 0)
				q = q->next;
			else
			{
				b = stvoriPol(q->coef, q->exp);
				unos(head, b);
				q = q->next;
			}
		}
	}
	else
	{
		while (p != NULL)
		{
			if (p->coef == 0)
				p = p->next;
			else
			{
				b = stvoriPol(p->coef, p->exp);
				unos(head, b);
				p = p->next;
			}
		}
	}
}