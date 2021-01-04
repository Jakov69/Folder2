#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define M 100

typedef struct dir *Position;
typedef struct dir {
	char naziv[M];
	Position Next;		// BRAT
	Position Prev;		// PRETHODNI DIREKTORIJ
	Position Child;		// DJETE
} Dir;


int MakeDir(Position, char *);
Position FindDir(Position, char *);
int Ispis(Position);
int DeleteAll(Position);

int main() {

	Position root = NULL;
	Position TrDir = NULL;
	Position temp = NULL;
	char s;
	char name[M] = { '\0' };
	char pom[M] = { '\0' };


	root = (Position)malloc(sizeof(Dir));
	root->Next = NULL;
	root->Prev = NULL;
	root->Child = NULL;


	strcpy(root->naziv, "root\0");

	if (root != NULL) {

		TrDir = root;
		strcat(pom, "root:\\");

		while (1) {
			printf("\n\nTrenutna putanja: %s\n", pom);
			printf("\nOdaberite:\n-A md\n-B cd_dir\n-C cd\n-D dir\n-E izl\n");
			scanf(" %c", &s);


			switch (s)
			{

			case 'A':
				printf("\nUnesite naziv direktorija kojeg zelite dodat: ");
				scanf("%s", name);
				if (MakeDir(TrDir, name) == 0)
				{
					printf("Datoteka dodana: %s%s", pom, name);
				}
				break;

			case 'B':

				printf("\nUnesite naziv direktorija na kojeg zelite pokazat: ");
				scanf("%s", name);
				if ((temp = FindDir(TrDir, name)) != NULL)
				{
					printf("Datoteka pronadena. Trenutna putanja: %s%s", pom, name);
					TrDir = temp;
					strcat(pom, temp->naziv);
					strcat(pom, "\\");
				}
				else {
					printf("Datoteka nije pronadena.");
				}
				break;

			case 'C':
				if (TrDir->Prev == NULL)
				{
					printf("Nalazite se u root-u!");
				}
				else {
					pom[strlen(pom) - strlen(TrDir->naziv) - 1] = '\0';
					TrDir = TrDir->Prev;
				}


				break;

			case 'D':
				printf("\n");
				printf("%s\n", TrDir->naziv);
				printf("-");
				Ispis(TrDir->Child);
				break;

			case 'E':
				break;

			default:
				puts("\nGreska\n");


			}
		}
	}
	return EXIT_SUCCESS;
}

int MakeDir(Position root, char naziv[M]) {
	if (root != NULL) {
		Position q = (Position)malloc(sizeof(Dir));

		if (q != NULL)
		{
			q->Child = NULL;

			q->Prev = root;
			q->Next = root->Child;
			root->Child = q;

			strcpy(q->naziv, naziv);
			return 0;
		}
	}
	return -1;
}


Position FindDir(Position root, char naziv[M]) {
	if (root != NULL) {
		root = root->Child;
		if (root != NULL)
		{
			while (root != NULL && strcmp(root->naziv, naziv) != 0)
			{
				root = root->Next;
			}
			return root;
		}
	}
	return NULL;
}


int Ispis(Position root)
{
	if (root != NULL)
	{
		printf("%s", root->naziv);

		if (root->Child != NULL)
		{
			printf("\\");
		}
		printf("\n");
		printf("-");
		Ispis(root->Next);
	}
	return -1;
}

int DeleteAll(Position root) {

	if (root != NULL)
	{
		DeleteAll(root->Child);
		DeleteAll(root->Next);
		free(root);
	}
	return -1;
}