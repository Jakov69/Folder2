#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct skup;
typedef struct skup* Position;
typedef struct skup {
	int coef;
	int exp;
	Position next;
}Pol;

void Presjek(Position, Position, Position);
void Unija(Position, Position, Position);
Position stvoriS(int, int);
void citaj(char*, Position);
void ispis(Position);
void unos(Position, Position);
Position nm(Position, Position);
void sort(int, int, Position);


int main() {
	Pol head1, head2, head3;
	head1.next = NULL;
	head2.next = NULL;
	head3.next = NULL;

	citaj("Skup1.txt", &head1);
	citaj("Skup2.txt", &head2);

	printf("\nPrvi skup:\n");
	ispis(&head1);

	printf("\nDrugi skup:\n");
	ispis(&head2);

	printf("\nPresjek:\n");
	Presjek(&head1, &head2, &head3);
	ispis(&head3);

    printf("\nUnija:\n");
	Unija(&head1, &head2, &head3);
	ispis(&head3);
	
	
	return 0;
}
void citaj(char*d, Position x) {

	int coef = 0, exp = 0;
	FILE *ulz;
	ulz = fopen(d, "r");

	if (NULL == ulz) printf("Greska pri alokaciji! ");

	while (feof(ulz) == 0) {

		fscanf(ulz, "%d %d", &coef, &exp);
		sort(exp, coef, x);

	}
	fclose(ulz);
}
void sort(int exp, int coef, Position x) {
	Position p;
	while (x->next != NULL && x->next->exp < exp)
		x = x->next;

	p = stvoriS(coef, exp);

	p->next = x->next;
	x->next = p;
}

Position stvoriS(int coef, int exp) {
	Position p = NULL;

	p = (Position)malloc(sizeof(Pol));

	p->coef = coef;
	p->exp = exp;

	return p;

}

void ispis(Position head) {
	Position p = NULL;

	for (p = head->next; p != NULL; p = p->next)
	{
		if (p->coef != 0)
			 printf("\t%d %d", p->coef, p->exp);

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

void Presjek(Position p, Position q, Position head) {

      Position b = NULL;

	int coef = 0, exp = 0;

	p = p->next;
	q = q->next;

	while (p != NULL && q != NULL)
	{
		if (p->exp == q->exp)
		{
			
			if (p->coef == q->coef)
			{
			    b = stvoriS(coef, exp);
				unos(head, b);
				p = p->next;
				q = q->next;
			}
			else
			{
		

				p = p->next;
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
				b = stvoriS(q->coef, q->exp);
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
				b = stvoriS(p->coef, p->exp);
				unos(head, b);
				p = p->next;
			}
		}
	}
	}
}	
void Unija(Position p, Position q, Position head){
     Position b = NULL;
 Position a = NULL;
 
	int coef = 0, exp = 0;

	p = p->next;
	q = q->next;

	while (p != NULL && q != NULL)
	{
		if (p->exp == q->exp)
		{
			
			if (coef == 0)
			{
				p = p->next;
				q = q->next;
			}
			else
			{
				exp = p->exp;
				b = stvoriS(coef, exp);
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
				b = stvoriS(a->coef, a->exp);
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
				b = stvoriS(q->coef, q->exp);
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
				b = stvoriS(p->coef, p->exp);
				unos(head, b);
				p = p->next;
			}
		}
	}
}
