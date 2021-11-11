/*
 * NPhilG
 * linkedlist.c
 * C programming basics:
 * command line arguments, I/O, structs, linked list
 */

/*
 * General design:
 * takes in any number of command line arguments
 * if any are given, it adds them to a linked list
 * provides a menu which lets you do the following:
 * print list, insert node, delete node, and quit (deletes list, frees memory, and exits)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUFFER 30


typedef struct Node {
	char *string;
	struct Node *next;
}node;

node *newNode() {
	node *new = (node*)malloc(sizeof(node));
	new->string = "";
	new->next = NULL;
	return new;
}

void printList(node *head) {
	
	if (head == NULL) {
		printf("List is empty\n");
		exit(1);
	}

	while (head != NULL) {
		printf(" %s ", head->string);
		head = head->next;
	}
	printf("\n");
}

void deleteList(node *head) {

	printf("Deleting list\n");
	node *prev;
	prev = NULL;

	while (head != NULL) {
		prev = head;
		head = head->next;
		free(prev);
	}
}

void initList(node** head, char* argv[], int argc) {

	node *t = *head;
	printf("inside initList function\n");

	for (int i = 1; i < argc; i++) {
		t->string = argv[i];
		if (i < argc-1) {
			t->next = newNode();
			t = t->next;
		}
	}
}

void printMenu() {
	printf("1. Print list\n");
	printf("2. Add node\n");
	printf("3. Delete node\n");
	printf("4. Quit\n");

}

int getMenuVal() {
	int val = 0;
	char buffer[MAX_BUFFER];
	while (1) {
		fgets(buffer, sizeof(buffer), stdin);
		sscanf(buffer, "%d", &val);

		if (val == 1 || val == 4 || val == 2)
			break;
		else {
			printf("Please pick a number from 1 to 4\n");
			printMenu();
		}
	}
	return val;
}

int linkLen(node* head) {
	int count = 0;
	node* current = head;
	while (current != NULL) {
		count++;
		current = current->next;
	}
	return count;
}

void insertNode(node** head, int position, char* string) {
	node *current = *head;
	node *new = newNode();

	int i = 0;
	if (position == 0) {
		new->next = current;
		new->string = string;
		*head = new;
		return;
	}

	else {
	current = (*head)->next;
	node *prev = *head;
	
	while (i < position-1) {
		prev = current;
		current = current->next;
		i++;
	}
	new->string = string;
	new->next = prev->next;
	prev->next = new;
	}
}

int main(int argc, char *argv[]) {

	
	printf("the number of elements: %d\n", argc-1);
	for (int i = 1; i < argc; i++) {
		printf("%s ", argv[i]);
	}
	printf("\n"); 

	node *head = NULL;
	head = (node*)malloc(sizeof(node));
	head->next = NULL;

	if (!head) {
		printf("Failed to allocate head node\n");
		exit(1);
	}

	initList(&head, argv, argc);
	
	int mv = -1;
	int i = 1;
	int position = -1;
	char buffer[MAX_BUFFER];
	while (i) {
		position = -1;
		mv = -1;
		printMenu();
		mv = getMenuVal();

		char *string;
		string = malloc(256);
		int len = linkLen(head);
		memset(buffer, 0, MAX_BUFFER);
		
		switch (mv) {
			case 1:
				printList(head);
				break;
			case 2:
				printf("What would like to put: ");
				fgets(string, sizeof(string), stdin);

				string[strcspn(string, "\n")] = 0;
				string[strcspn(string, " ")] = 0;
				fflush(stdin);

				while (1) {
					printf("Where in the list (head is at 0) will you put it: ");
					fgets(buffer, sizeof(buffer), stdin);
					sscanf(buffer, " %d", &position);

					if (position > len) {
						position = len;
						break;
					}

					else if(position >= 0)
						break;
				}

				printf("position = %d\n", position);
				insertNode(&head, position, string);
				break;
			case 4:
				deleteList(head);
				free(string);
				exit(1);
			default:
				break;
		}
		free(string);
	}
	return 0;
}
