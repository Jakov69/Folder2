#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LENGTH 11
#define MAX_DATA 1024

struct _TreeNode;
typedef struct _TreeNode* PositionT;
typedef struct _TreeNode {
	PositionT LeftChild;
	PositionT RightChild;
	char element[LENGTH];
}TreeNode;

struct _Stock;
typedef struct _Stack* PositionS;
typedef struct _Stack {
	PositionT Treenode;
	PositionS next;
}Stack;

PositionT CreateNode(char*);
int Push(PositionT, PositionS);
PositionT Pop(PositionS);
PositionT ReadPostfix(char*);
int Int_Char(char*);
void PrintInorder(PositionT, FILE*);
int WriteInfix(PositionT, char*);
PositionT DeleteAll(PositionT);

int main() {
	PositionT root = NULL;
	char name[MAX_DATA] = { 0 };

	printf("\nEnter the name of the file from which you want to read the postfix(e.g. postfix.txt):\t");
	scanf(" %s", name);

	root = ReadPostfix(name);

	printf("\nEnter the name of the file in which you want to write the infix :\t");
	scanf(" %s", name);

	WriteInfix(root, name);
	DeleteAll(root);

	return EXIT_SUCCESS;
}

int Int_Char(char* element) {
	int number = 0;

	if (sscanf(element, "%d", &number) == 1) return 1;

	return 0;
}

PositionT ReadPostfix(char* FileName) {
	Stack head;
	PositionT result = NULL;
	FILE* dat = NULL;
	char element[LENGTH] = { 0 };

	head.next = NULL;

	dat = fopen(FileName, "r");
	if (!dat)
	{
		printf("File failed to open!!");
		return NULL;
	}

	while (!feof(dat))
	{
		PositionT Node = NULL;

		fscanf(dat, "%s", element);
		Node = CreateNode(element);

		if (!Node)
		{
			fclose(dat);
			return NULL;
		}
		if (Int_Char(element))
			Push(Node, &head);
		else
		{
			Node->RightChild = Pop(&head);

			if (!Node->RightChild)
			{
				printf("\tPostfix expression is incorrect!\n");
				return NULL;
			}

			Node->LeftChild = Pop(&head);

			if (!Node->LeftChild)
			{
				printf("\tPostfix expression is incorrect!\n");
				return NULL;
			}

			Push(Node, &head);
		}
	}
	fclose(dat);

	result = Pop(&head);

	if (!result)
	{
		printf("\tFile is empty\n");
		return NULL;
	}

	return result;
}

PositionT Pop(PositionS head) {
	PositionS First = head->next;
	PositionT result = NULL;

	if (!First)
		return NULL;

	result = First->Treenode;
	head->next = First->next;
	free(First);

	return result;
}

int Push(PositionT Node, PositionS head)
{
	PositionS First = NULL;

	First = (PositionS)malloc(sizeof(Stack));

	if (!First)
	{
		printf("\tMemory allocation failed!!\n");
		return -1;
	}
	First->Treenode = Node;
	First->next = head->next;
	head->next = First;

	return 0;
}

PositionT CreateNode(char* string)
{
	PositionT Node = NULL;

	Node = (PositionT)malloc(sizeof(TreeNode));

	if (!Node)
	{
		printf("\tMemory allocation failed!!\n");
		return NULL;
	}

	strcpy(Node->element, string);
	Node->LeftChild = NULL;
	Node->RightChild = NULL;
}

void PrintInorder(PositionT current, FILE *dat) {
	if (current != NULL)
	{
		fprintf(dat, "( ");
		PrintInorder(current->LeftChild, dat);
		fprintf(dat, "%s ", current->element);
		PrintInorder(current->RightChild, dat);
		fprintf(dat, ") ");
	}
}

int WriteInfix(PositionT root, char* FileName) {
	FILE* dat = NULL;

	dat = fopen(FileName, "w");
	if (!dat)
	{
		printf("File failed to open!!");
		return -1;
	}
	PrintInorder(root, dat);
	fclose(dat);
	puts("");

	return 0;
}

PositionT DeleteAll(PositionT current)
{
	if (current != NULL)
	{
		DeleteAll(current->LeftChild);
		DeleteAll(current->RightChild);
		free(current);
	}
	return NULL;
}