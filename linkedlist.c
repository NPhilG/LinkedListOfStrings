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


/*
char[] getStringVal() {
	printf("inside getStringVal()\n");
	char *string = "";
	char buffer[30];
	while (1) {
		printf("inside while loop\n");
		fgets(buffer, sizeof(buffer), stdin);
//		sscanf(buffer, "%s", string);
//		scanf("%s", string);
		//memcopy(		
		break;
	}
	printf("end of getStringVal()\n");
	return buffer;
}
*/
void insertNode(node** head, int position, char* string) {
	node *current = *head;
	node *new = newNode();

	printf("head->string = %s\n", (*head)->string);
	printf("new->string = %s\n", new->string);

	if (position == 0) {
		new->next = current;
		new->string = string;
		*head = new;
	}
	printf("head->string = %s\n", (*head)->string);

	printList((*head));
	//printList(current);
	//printList(new);

	//return (*head);
	
}


/*int checkNodePosition(node *head) {
	int position;
	int len = linkLen(head);
	char buffer[MAX_BUFFER];
//	printf("inside checkNodePosition()\n");

	while (1) {
		fgets(buffer, sizeof(buffer), stdin);
		sscanf(buffer, "%d", &position);
	

		if (position < 0) { printf("Please enter a position number >= 0 and <= 4 %d\n", len+1);}
		
		else if (position >= len) { position = len; break;}
		else
			break;
	}
	printf("position = %d\n", position);
	return position;
}
*/

node* case2(node* head) {
	char *string;
	string = malloc(256);
	int position = -1;
	char buffer[MAX_BUFFER];

	printf("What would like to put into the list: ");
	scanf("%255s", string);
	fflush(stdin);
	printf("string = %s\n", string);


	printf("Where in the list (first node is at 0) would you like to put it: \n");
	//position = checkNodePosition(head);
	while (1) {
	
		fgets(buffer, sizeof(buffer), stdin);
		sscanf(buffer, "%d", &position);

		if (position > linkLen(head)) {
			position = linkLen(head);
			break;
		}
		else if (position >= 0)
			break;
	}

	printf("position = %d\n", position);

	insertNode(&head, position, string);
	free(string);
	return head;

}

node*  menu(node* head) {
	int mv = 0;
	int i = 1;
	while(i) {
		printMenu();
		mv = getMenuVal();

		switch (mv) {
			case 1:
				printList(head);
				break;
			case 2:
				head = case2(head);
				break;
			case 4:
				deleteList(head);
				exit(1);
				break;
		}
	}
	return head;
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

	//head = menu(head);
	
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
		
		switch (mv) {
			case 1:
				printList(head);
				break;
			case 2:
				//int position = -1;
				//char buffer[MAX_BUFFER];

				
				printf("What would like to put: ");
				scanf("%256s", string);
				fflush(stdin);

				while (1) {
					printf("Where in the list (head is at 0) will you put it: ");
					printf("\n");
					fgets(buffer, sizeof(buffer), stdin);
					sscanf(buffer, "%d", &position);

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
				exit(1);
			default:
				break;
		}
	}



	//printList(head);
	//deleteList(head);

	return 0;
}
