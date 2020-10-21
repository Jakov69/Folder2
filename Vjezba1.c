#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 80

typedef struct {
	char ime[MAX];
	char prezime[MAX];
	int bodovi;
}_student;


int main() {
	double tmp;
	double *realbr;
	int maxbr;
	int br = 0, i;

	_student *stud = NULL;

	FILE *ulz = NULL;

	ulz = fopen("lista.txt", "r");
    

	if ((ulz == NULL))
	{
		puts("\nGreška prilikom unosa");
		exit(1);
	}

	

	while (!feof(ulz)) 
		if (fgetc(ulz) == '\n') br++;
	
	stud = (_student*)malloc(br * sizeof(_student));
	rewind(ulz);

	printf("%d\n", br);    //Ovo je samo za provjeru

	printf("\nUnesite ukupan broj bodova na kolokviju: ");
	scanf("%d", &maxbr);

	realbr = (double*)malloc(br * sizeof(double));

	printf("\nStatistika prolaznosti na kolokviju ");
	printf("\nStudent \t       Bodovi          PROSJEK(%%)\n");

	for (i = 0; i < br; i++) {
		fscanf(ulz, "%s %s %d", stud[i].ime,stud[i].prezime, &stud[i].bodovi);
		tmp = (double)stud[i].bodovi / maxbr;

		*(realbr+i) = tmp * 100;
		
		printf("%s\t%s\t\t%d\t\t%.2f\n", stud[i].ime, stud[i].prezime, stud[i].bodovi,*(realbr+i));
	}
	
		
	fclose(ulz);
	
    return 0;
	system("pause");
}
