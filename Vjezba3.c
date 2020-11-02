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
Position pronalazakPret(char *, Position);
void Ispis(Position);
void brisi(char*, Position);
int IspisPronadenih(char* who, Position where);
void UnosPosljeElementa(char*, Position, Position);
void UnosPrijeElementa(char*, Position, Position);
void Sort(Position);
void unesiUdat(char*, Position);
void citajIZdat(char*, Position);

int main(void) {
	Student head;
	Position p = NULL;
	char Ime[M] = { 0 };
	char Prezime[M] = { 0 }, Prez[M] = { 0 };
	int godina = 0;
	head.next = NULL;
	int i, osobe, b;
	char s, ime[60];
	int br = 0;
	
	printf("\nOdaberite:\n");
	printf("\n\nMENU:\nIzaberi opciju:\n\t1->Citaj iz datoteke\t\n");
	printf("\t2->Ucitaj u datoteku\n\tOpcija:\t");
	scanf(" %d", &b);

	if (b == 1)
	{
		printf("\nUnesite ime datoteke u koju zelite spremiti listu (Nesto.txt):\t");
		scanf("%s", ime);
		citajIZdat(ime, &head);
		Ispis(&head);
	}
	else if (b == 2)
	{

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
			printf("b->Izbrisi neku osobu\n\ty->Unos prije odredenog elementa\n\tc-Zapis liste u datoteku\n\to->Unos nakon odredenog elem.\n\ts->Sortiraj po prezimenu\n\ti->Kraj programa\n\tOpcija:\t");

			scanf(" %c", &s);

			switch (s) {

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
			case 'o':
				printf("\nUnesite novu osobu:\n");

				printf("Ime:\t");
				scanf(" %s", Ime);

				printf("Prezime:\t");
				scanf(" %s", Prezime);

				printf("Godina rodjenja:\t");
				scanf(" %d", &godina);

				p = noviStudent(Ime, Prezime, godina);

				printf("\nUnesite prezime:\t");
				scanf(" %s", Prez);

				UnosPosljeElementa(Prez, &head, p);

				puts("\n");
				Ispis(&head);
				break;

			case'y':
				printf("\nUnesite novu osobu:\n");

				printf("Ime:\t");
				scanf(" %s", Ime);

				printf("Prezime:\t");
				scanf(" %s", Prezime);

				printf("Godina rodjenja:\t");
				scanf(" %d", &godina);

				p = noviStudent(Ime, Prezime, godina);

				printf("\nUnesite prezime:\t");
				scanf(" %s", Prez);

				UnosPrijeElementa(Prez, &head, p);

				puts("\n");
				Ispis(&head);
				break;
			case'c':
				printf("\nUnesi ime dokumenta iz kojeg oces citat: ");
				scanf("%s", ime);
				unesiUdat(&ime, &head);
				break;

			case 's':
				Sort(&head);
				puts("\n");
				Ispis(&head);
				break;

			default:
				puts("Greska");
			}
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
	int i, br, j = 0;
	i = IspisPronadenih(who, where);

	if (i == 0)
	{
		printf("\nTa osoba ne postoji\n");
		return NULL;
	}
	else if (i == 1)
	{


		for (p = where; p != NULL; p = p->next)
		{
			if (strcmp(p->Prezime, who) == 0)
			{
				if (j == 0)
					return p;

				j++;
			}
		}
	}
	else
		printf("\nUnesi redni broj:\t");
	scanf("%d", &br);

	for (p = where; p != NULL; p = p->next)
	{
		if (strcmp(p->Prezime, who) == 0)
		{
			if (j == br - 1)
				return p;

			j++;
		}
	}
}

Position pronalazakPret(char *who, Position where)
{
	Position p = NULL;
	int i, br, j = 0;
	i = IspisPronadenih(who, where);

	if (i == 0)
	{
		printf("\nTa osoba ne postoji!!\n\n");
		return NULL;
	}

	else if (i == 1)
	{
		for (p = where; p != NULL; p = p->next)
		{
			if (strcmp(p->next->Prezime, who) == 0)
			{
				if (j == 0)
					return p;

				j++;
			}
		}
	}
	else
	{
		printf("\nUnesi redni broj:\t");
		scanf("%d", &br);

		for (p = where; p != NULL; p = p->next)
		{
			if (strcmp(p->next->Prezime, who) == 0)
			{
				if (j == br - 1)
					return p;

				j++;
			}
		}
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
	int i;

	prije= IspisPronadenih(who, where);



	if (prije != NULL) {
		where = prije->next;
		prije->next = where->next;
		free(where);
	}

}
void UnosPosljeElementa(char* who, Position where, Position what)
{
	where = pronalazak(who, where);

	if (where != 0)
	{
		unesiPoc(where, what);
	}
}

void UnosPrijeElementa(char* who, Position where, Position what)
{
	int br = 0;
	where = pronalazakPret(who, where);

	if (where != 0) {
		unesiPoc(where, what);
	}
}
void unesiUdat(char* Imedat, Position head) {
	Position p = NULL;
	int i = 0;
	FILE* dat;
	dat = fopen(Imedat, "w");

	fprintf(dat, "\t  Ime\t\tPrezime\tGodina rod.\n");
	for (p = head->next; p != NULL; p = p->next)
	{
		fprintf(dat, "\t%d. %-15s\t%-15s\t%d\n", i + 1, p->Ime, p->Prezime, p->godina);
		i++;
	}

	fclose(dat);

	printf("\n");

}

void citajIZdat(char* Imedat, Position head) {
	Position p = NULL;
	char Ime[M] = { 0 };
	char Prezime[M] = { 0 };
	int godina = 0;
	int i;
	FILE* dat;
	dat = fopen(Imedat, "r");
	p = head->next;

	while (fgetc(dat) != '\n') {};

	while (1)
	{
		fscanf(dat, "%d. %s %s %d", &i, Ime, Prezime, &godina);

		if (feof(dat))
			break;

		p = noviStudent(Ime, Prezime, godina);
		unesiKraj(head, p);
		p = p->next;

	}
	fclose(dat);
	printf("\n");
}
void Sort(Position where)
{
	Position end = NULL, temp, what, prev;

	while (where->next != end)
	{
		prev = where;
		what = where->next;
		while (what->next != end)
		{
			if (strcmp(what->Prezime, what->next->Prezime) > 0)
			{
				temp = what->next;
				prev->next = temp;
				what->next = temp->next;
				temp->next = what;
				what = temp;
			}
			else if (strcmp(what->Prezime, what->next->Prezime) == 0)
			{
				if (strcmp(what->Ime, what->next->Ime) > 0)
				{
					temp = what->next;
					prev->next = temp;
					what->next = temp->next;
					temp->next = what;
					what = temp;
				}
			}

			prev = what;
			what = what->next;
		}
		end = what;
	}
}
