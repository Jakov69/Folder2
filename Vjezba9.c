#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct stablo* Position;

typedef struct stablo {

	int El;
	Position L;
	Position D;

} Stablo;

Position Dodaj(Position, int);
Position Trazi(Position, int);
Position TraziMax(Position);
Position TraziMin(Position);
Position Brisi(Position, int);
int Ispisi(Position, int);
int BrisiSve(Position);

int main() {

	int vr = 0;
	int s = 1;

	Position root = (Position)malloc(sizeof(Stablo));

	if (root != NULL)
	{
		root->L = NULL;
		root->D = NULL;

		while (s)
		{
			printf("\nIzaberite: ");
			printf("\n1-Dodaj u stablo\n2-Trazi element\n3-Brisi\n4-Ispis\n");
			scanf("%d", &s);

			switch (s)
			{
			case 1:
			{
				printf("\nUnesite vrijednost koju zelite dodat u stablo:");
				scanf(" %d", &vr);
				if ((root->D = Dodaj(root->D, vr)) == NULL)
				{
					printf("\nGreska pri unosu!");
				}
				else
				{
					printf("\nElement %d uspjesno dodan u stablo.", vr);
				}
				break;
			}
			case 2:
			{
				printf("\nUnesite vrijednost koju zelite traziti u stablu:");
				scanf(" %d", &vr);
				if (Trazi(root->D, vr) == NULL)
				{
					printf("Taj element nije pronaden u stablu.\n");
				}
				else
				{
					printf("Pronasli smo element.\n");
				}
				break;
			}
			case 3:
			{
				printf("\nUnesite vrijednost elementa kojega zelite izbrisati: ");
				scanf(" %d", &vr);
				if ((root->D = Brisi(root->D, vr)) == NULL)
				{
					printf("\nGreska!");
				}
				else
				{
					printf("\nElement %d uspjesno izbrisan iz stabla.", vr);
				}
				break;
			}
			case 4:
			{
				Ispisi(root->D, 0);
				break;
			}
			default:
			{
				s = 0;
				break;
			}
			}
		}
	}
	BrisiSve(root->D);
	return 0;
}

Position Dodaj(Position root, int el)
{
	if (root == NULL)
	{
		root = (Position)malloc(sizeof(Stablo));
		root->El = el;
		root->L = NULL;
		root->D = NULL;
	}
	else
	{
		if (el < root->El)
		{
			root->L = Dodaj(root->L, el);
		}
		else if (el > root->El) {
			root->D = Dodaj(root->D, el);
		}
	}
	return root;
}

Position Trazi(Position root, int el)
{
	if (root != NULL)
	{
		if (el == root->El)
			return root;

		if (el < root->El)
		{
			return Trazi(root->L, el);
		}
		else
		{
			return Trazi(root->D, el);
		}
	}
	return root;
}

Position Brisi(Position root, int el)
{
	if (root == NULL)
		return root;

	if (root->El > el)
		root->L = Brisi(root->L, el);
	else if (root->El < el)
		root->D = Brisi(root->D, el);

	else {

		if (root->L == NULL)
		{
			Position temp = root->D;
			free(root);
			return temp;
		}
		else if (root->D == NULL)
		{
			Position temp = root->L;
			free(root);
			return temp;
		}
		else {
			// IMAMO DVA DJETETA
			Position temp = TraziMax(root->L);
			root->El = temp->El;
			root->L = Brisi(root->L, temp->El);
		}
	}
	return root;
}


Position TraziMax(Position root)
{
	while (root->D != NULL)
	{
		root = root->D;
	}
	return root;
}


Position TraziMin(Position root)
{
	while (root->L != NULL)
	{
		root = root->L;
	}
	return root;
}


int Ispisi(Position root, int razmak)
{
	if (root == NULL)
		return 0;

	razmak += 10;

	Ispisi(root->D, razmak);

	printf("\n");
	printf(" ");
	for (int i = 10; i < razmak; i++)
		printf(" ");

	printf("%d\n", root->El);

	Ispisi(root->L, razmak);
	return 0;
}

int BrisiSve(Position root)
{
	if (root == NULL)
		return 0;
	BrisiSve(root->L);
	BrisiSve(root->D);
	free(root);
	return 0;
}