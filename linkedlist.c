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
	char* string;
	struct Node *next;
}node;

node *newNode() {
	node *new = (node*)malloc(sizeof(node));
	new->string = "";
	new->next = NULL;
	return new;
}

void printList(node *head) {
	//head = head->next;
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

		if (val == 1 || val == 4)
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



char* getStringVal() {
	char* string = "";
	char buffer[MAX_BUFFER];
	while (1) {
		fgets(buffer, sizeof(buffer), stdin);
		sscanf(buffer, "%s", string);

		if (string[0] == '\0')
			printf("Please put something in \n");
		else
			break;
	}
	return string;
}

void insertNode(node** head, int position, char* string) {
	node *current = *head;
	node *new = newNode();


}

int checkNodePosition(node* head) {
	int position;
	int len = linkLen(head);
	char buffer[MAX_BUFFER];
	while (1) {
		fgets(buffer, sizeof(buffer), stdin);
		sscanf(buffer, "%d", &position);

		if (position < 0) { printf("Please enter a position number of 0 or less than %d\n", len);}
		
		else if (position >= len) { position = len-1; break;}
		else
			break;
	}
	return position;
}


void case2(node* head) {
	char* string = "";
	int position = 0;

	printf("What would like to put into the list: ");
	string = getStringVal();

	printf("Where in the list (first node is at 0) would you like to put it: \n");
	position = checkNodePosition(head);

	insertNode(&head, position, string);


}

void menu(node* head) {
	int mv = 0;
	while(1) {
		printMenu();
		mv = getMenuVal();

		switch (mv) {
			case 1:
				printList(head);
				break;
			case 2:
				case2(head);
				break;
			case 4:
				deleteList(head);
				exit(1);
				break;
		}
	}
}


int main(int argc, char* argv[]) {

	
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

	menu(head);
	//printList(head);
	//deleteList(head);

	return 0;
}
