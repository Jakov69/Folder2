#define _CRT_SECURE_NO_WARNINGS 

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define M (256)

struct _student;
typedef struct _student* Position;
typedef struct _student {
	char Ime[M];
	char Prezime[M];
	int godina;
	Position next;
} Student;

Position noviStudent(char*, char*, int);
void unesiPoc(Position, Position);
void unesiKraj(Position, Position);
Position pronalazak(char*, Position);
Position pronalazakPret(char *, Position, int);
void Ispis(Position);
void brisi(char, Position);
int IspisPronadenih(char* who, Position where);

int main(void) {
	Student head;
	Position p = NULL;
	char Ime[M] = { 0 };
	char Prezime[M] = { 0 };
	int godina = 0;
	head.next = NULL;
	int i,br,osobe;
	char s;

	printf("Unesite broj studenata:\t");
	scanf("%d", &osobe);

	for (i = 0; i < osobe; i++)
	{
		printf("\nUnesite osobu:\n");

		printf("Ime:\t");
		scanf(" %s", Ime);

		printf("Prezime:\t");
		scanf(" %s", Prezime);

		printf("Godina rodjenja:\t");
		scanf(" %d", &godina);

		p = noviStudent(Ime, Prezime, godina);
		unesiKraj(&head, p);
		puts("\n");
		Ispis(&head);
	}
    while (1)
	{
		printf("\n\nMENU:\nIzaberi neku opciju:\n\tp->Unos na pocetak\n\tk->Unos na kraj\n\tr->Pronadi osobu po prezimenu\n\t");
		printf("b->Izbrisi neku osobu\n\ti->Kraj programa\n\tOpcija:\t");
		scanf(" %c", &s);
		 
		switch (s){
		
		case 'p':
			printf("\nUnesite osobu:\n");

			printf("Ime:\t");
			scanf(" %s", Ime);

			printf("Prezime:\t");
			scanf(" %s", Prezime);

			printf("Godina rodjenja:\t");
			scanf(" %d", &godina);

			
			p = noviStudent(Ime, Prezime, godina);

			unesiPoc(&head, p);
			puts("\n");

			Ispis(&head);
			break;
		case 'k':
			printf("\nUnesite osobu:\n");

			printf("Ime:\t");
			scanf(" %s", Ime);

			printf("Prezime:\t");
			scanf(" %s", Prezime);

			printf("Godina rodjenja:\t");
			scanf(" %d", &godina);

			p = noviStudent(Ime, Prezime, godina);

			unesiKraj(&head, p);
			puts("\n");

			Ispis(&head);
			break;
		case 'r':
			printf("\nUnesite prezime:");
			scanf(" %s", Prezime);
			puts("\n");
			p = pronalazak(Prezime, &head);
			if (p != NULL)
				printf("\t\n1.  %s %s %d\n", p->Ime, p->Prezime, p->godina);
			break;
		case 'b':
			printf("\nUnesite prezime:");
			scanf("%s", Prezime);
			puts("\n");
			brisi(Prezime, &head);
			Ispis(&head);
			break;
		case 'i':
			Ispis(&head);
			return EXIT_SUCCESS;
			break;
		default:
			puts("Greska");
		}
	}

	return EXIT_SUCCESS;
}

Position noviStudent(char* Ime, char* Prezime, int godina) {
	Position p = NULL;

	p = (Position)malloc(sizeof(Student));

	if (!p) {
		printf("Alokacija neuspjesna\n");
		return NULL;
	}
    strcpy(p->Ime, Ime);
	strcpy(p->Prezime, Prezime);
	p->godina = godina;
	p->next = NULL;

	return p;
}

void unesiPoc(Position where, Position what) {
	what->next = where->next;
	where->next = what;
}

void Ispis(Position head) {
	Position p = NULL;
	int i = 0;

	printf("Sadrzaj liste:\n");

	for (p = head->next; p != NULL; p = p->next)
	{
		printf("\t%d.  %s %s %d\n", i + 1, p->Ime, p->Prezime, p->godina);
		i++;
	}

	printf("\n");
}

void unesiKraj(Position where, Position what) {

	while (where->next != NULL)
		where = where->next;

	what->next = where->next;
	where->next = what;
}

Position pronalazak(char *who, Position where)
{
	Position p = NULL;
	int i,br,j = 0;
	i = IspisPronadenih(who, where);

	if (i == 0)
	{
		printf("\nTa osoba ne postoji\n");
        return NULL;
	}
	else if (i > 1)
	{
		printf("\nUnesite redni broj osobe:\t");
		scanf("%d", &br);

		for (p = where; p != NULL; p = p->next)
		{
			if (!strcmp(p->Prezime, who))
			{
				if (j == br - 1)
					return p;

				j++;
			}
		}
	}
	else
		return NULL;
}

Position pronalazakPret(char *who, Position where, int br)
{
	Position p = NULL;
	int i = 0;

	for (p = where; p != NULL; p = p->next)
	{
		if (!strcmp(p->next->Prezime, who))
		{
			if (i == br - 1)
				return p;

			i++;
		}
	}

	if (i == 0)
	{
		printf("\nTa osoba ne postoji!!\n\n");
		return NULL;
	}


}

int IspisPronadenih(char* who, Position where)
{
	Position p = NULL;
	int i = 0;

	for (p = where->next; p != NULL; p = p->next)
	{
		if (!strcmp(p->Prezime, who))
		{
			printf("\t%d.  %s %s %d\n", i + 1, p->Ime, p->Prezime, p->godina);
			i++;
		}
	}
	return i;
}

void brisi(char* who, Position where)
{
	Position prije;
	int i,br;

	i = IspisPronadenih(who, where);

    if (i > 1){
	

		printf("\nKoga zelite izbrisati:\t");
		scanf("%d", &br);

		prije = pronalazakPret(who, where,br);

		 if (prije != NULL){
		    where = prije->next;
			prije->next = where->next;
			free(where);
		}
	}
	else if (i == 1)
	{
	br = 1;
	prije = pronalazakPret(who, where,br);

		 if (prije != NULL)
		 {
		    where = prije->next;
			prije->next = where->next;
			free(where);
		 }
	}
	else
	printf("\nTa osoba ne postoji!!\n\n");
}


