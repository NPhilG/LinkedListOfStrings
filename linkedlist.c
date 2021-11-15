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
	printf("inside newNode() \n");
	node *new = (node*)malloc(sizeof(node));
//	new->string = (char*)malloc(256);
	new->string = "";
	new->next = NULL;
	return new;
}

void printDetails(int len) {
	printf("The linked list has a number of objects put into it\n");
	printf("The elements are number from 0 to %d\n", len);
	printf("Option 1 prints all the items in the linked list\n");
	printf("Option 2 adds items to a node that is put into the linked list\n");
	printf("If the number given to the item placement is higher than the number of items in the linked list\n");
	printf("then it will simply add the node to the end\n");
	printf("Option 3 deletes items to the linked list\n");
}

void printList(node *head) {
	
	if (head == NULL) {
		printf("List is empty\n");
		return;
	}

	while (head != NULL) {
		if (head->string == NULL) {
			printf("node->string == NULL\n");
			break;
			
		}
		if (head->string != NULL) 
			printf(" %s ", head->string);
		head = head->next;
	}
	printf("\n");
}

void deleteList(node *head) {

//	printf("Deleting list\n");
	node *prev;
	prev = NULL;

	while (head != NULL) {
		prev = head;
		head = head->next;
		free(prev->string);
		free(prev);
	}
	free(head);
}

void initList(node** head, char* argv[], int argc) {

	node *t = *head;
	printf("inside initList function\n");

	for (int i = 1; i < argc; i++) {
		//t->string = argv[i];
		
		t->string = (char*)malloc(sizeof(argv[i])+1);
		strncpy(t->string, argv[i], strlen(argv[i]+1));
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
	printf("4. More details\n");
	printf("5. Quit\n");

}

int getMenuVal() {
	int val = 0;
	char buffer[MAX_BUFFER];
	while (1) {
		fgets(buffer, sizeof(buffer), stdin);
		sscanf(buffer, "%d", &val);

		if (val >= 1 && val <= 5)
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

void insertNode(node** head, int position, char* str) {
	node *current = *head;
	node *new = newNode();
	char *string = (char*)malloc(strlen(str)+1);
	strncpy(string, str, strlen(str)+1);

	printf("string = %s\n", string);
	int i = 0;
	if (position == 0) {
		new->next = current;
		//new->string = string;
		new->string = (char*)malloc(strlen(str)+1);
		strncpy(new->string, str, strlen(str)+1);
		
		*head = new;
		free(string);
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
	new->string = (char*)malloc(strlen(str)+1);
	strncpy(new->string, str, strlen(str)+1);
	new->next = prev->next;
	prev->next = new;
	}
	//printList((*head));
	free(string);
}

void deleteNode(node **head, int position) {
	node *prev = NULL;
	node *current = *head;
	node *temp = newNode();
//	int len = linkLen((*head));
	int i = 0;

	while (i < position -1) {
		prev = current;	
		current = current->next;
		i++;
	}
	temp = prev->next;
	prev->next = temp;
}

int main(int argc, char *argv[]) {

	
	printf("the number of elements: %d\n", argc-1);
	for (int i = 1; i < argc; i++) {
		printf("%s ", argv[i]);
	}
	printf("\n"); 

	node *head = NULL;
	head = (node*)malloc(sizeof(node));
	head->string = "";
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
		string = (char*)malloc(256);
		memset(buffer, 0, MAX_BUFFER);
		int len = linkLen(head);
		
		switch (mv) {
			case 1:
				printf("before entering printList(head)\n");
				printList(head);
				break;
			case 2:
				printf("What would like to put: ");
				fgets(string, 256, stdin);

				string[strcspn(string, "\n")] = 0;
				string[strcspn(string, " ")] = 0;
				fflush(stdin);

				while (1) {
					memset(buffer, 0, MAX_BUFFER);
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

				insertNode(&head, position, string);
				//printList(head);
				break;
			case 3:
				while (1) {
					memset(buffer, 0, MAX_BUFFER);
					printf("What item would like to delete, from 0 to %d: ", len-1);
					fgets(buffer, sizeof(buffer), stdin);
					sscanf(buffer, " %d", &position);

					if (position > len) {
						position = len-1;
						break;
					}

					else if (position >= 0)
						break;
				}
				//deleteNode(&head, position);
				break;
			case 5:
				deleteList(head);
				free(string);
				exit(1);
			case 4:
				printDetails(len);
				break;
		}
		free(string);
	}
	return 0;
}
