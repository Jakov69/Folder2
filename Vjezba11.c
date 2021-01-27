#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define HASH_MAX 11
#define LENGTH 1024

struct _List;
typedef struct _List* PositionL;
typedef struct _List {
	int ID;
	char name[LENGTH];
	char surname[LENGTH];
	PositionL next;
}List;


int CreateKey(char *);
PositionL CreatStudent(char*, char*, int);
int InHashtable(List*, char*, char*, int);
PositionL FindStudent(PositionL, char*, char*);
int PrintID(PositionL);
int PrintHashtable(List*);
int ReadFromFile(char*, List*);


int main()
{
	List hash[HASH_MAX];
	int i = 0, check = 0, option = 0;
	char FileName[LENGTH] = { 0 };

	for (i = 0; i < HASH_MAX; i++)
		hash[i].next = NULL;

	printf("\nEnter the name of the file from which you want to read list of studens(e.g. zad11.txt):\t");
	scanf(" %s", FileName);

	check = ReadFromFile(FileName, hash);

	if (check == -1)
		return EXIT_SUCCESS;

	while (1)
	{
		system("cls");
		PrintHashtable(hash);
		printf("\n\n\tChoose:\n\n");
		printf("\t1->print ID of student\n");
		printf("\t2->Exit\n");
		printf("Option->");
		scanf(" %d", &option);

		switch (option)
		{
		case 1:
			PrintID(hash);
			puts("");
			system("pause");
			break;
		case 2:
			puts("");
			return EXIT_SUCCESS;
		default:
			puts("Choose only numbers from 1-2!\n");
			puts("");
			system("pause");
			break;
		}
	}

	return EXIT_SUCCESS;
}

int ReadFromFile(char* FileName, List *hash) {
	FILE* dat = NULL;
	int ID = 0, check = 0, i = 0;
	char name[LENGTH] = { 0 };
	char surname[LENGTH] = { 0 };

	dat = fopen(FileName, "r");

	if (!dat)
	{
		printf("File failed to open!!");
		return -1;
	}

	while (!feof(dat))
	{
		fscanf(dat, "%s %s %d", name, surname, &ID);

		check = InHashtable(hash, name, surname, ID);

		if (check == -1)
		{
			printf("\nStudent cannot be added!\n");
			fclose(dat);
			return -1;
		}
	}
	fclose(dat);

	return 0;
}

int CreateKey(char *surname) {
	int sum = 0;

	sum += (*surname++);

	return sum % HASH_MAX;
}

PositionL CreatStudent(char* name, char* surname, int ID)
{
	PositionL Student = NULL;

	Student = (PositionL)malloc(sizeof(List));

	if (!Student)
	{
		printf("Memory allocation failed!!\n");
		return NULL;
	}

	strcpy(Student->name, name);
	strcpy(Student->surname, surname);
	Student->ID = ID;

	Student->next = NULL;

	return Student;
}

int InHashtable(List *hash, char* name, char* surname, int ID) {
	PositionL current = NULL;
	PositionL object = NULL;

	current = &hash[CreateKey(surname)];

	object = CreatStudent(name, surname, ID);

	if (NULL == object)
		return -1;

	while (current->next != NULL && strcmp(object->surname, current->next->surname) > 0)
		current = current->next;

	while (current->next != NULL && strcmp(object->surname, current->next->surname) == 0 && strcmp(object->name, current->next->name) > 0)
		current = current->next;

	object->next = current->next;
	current->next = object;

	return 0;
}

PositionL FindStudent(List *hash, char* name, char* surname) {
	PositionL current_in_list = NULL;

	current_in_list = &hash[CreateKey(surname)];

	while (current_in_list != NULL)
	{
		if (strcmp(current_in_list->name, name) == 0 && strcmp(current_in_list->surname, surname) == 0)
			return current_in_list;
		current_in_list = current_in_list->next;
	}
	return current_in_list;

}

int PrintID(List *hash) {
	char name[LENGTH] = { 0 };
	char surname[LENGTH] = { 0 };
	PositionL object = NULL;

	printf("\n\nEnter the name and surname of the student to whom you want to print the ID number:\t");
	scanf(" %s %s", name, surname);

	object = FindStudent(hash, name, surname);

	if (!object)
		printf("\nStudent does not exist in the list!\n");
	else
		printf("\n\t%s %s -> ID=%d\n", object->name, object->surname, object->ID);

}

int PrintHashtable(List *hash) {
	int i = 0;
	PositionL current_in_list = NULL;

	printf("\tHash table:\n");

	for (i = 0; i < HASH_MAX; i++)
	{
		if (hash[i].next != NULL)
		{
			current_in_list = hash[i].next;

			printf("\n\t%d. kljuc:\n\n", i + 1);

			while (current_in_list != NULL)
			{
				printf("\tName:  %-15s\tSurname:  %-15s\tID: %d\n", current_in_list->name, current_in_list->surname, current_in_list->ID);
				current_in_list = current_in_list->next;
			}
			puts("--------------------");
		}
	}
	puts("******************************************");

	return 0;
}