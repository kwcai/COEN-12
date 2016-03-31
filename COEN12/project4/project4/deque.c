/* Kevin Cai
   COEN 12L Thurs
   Project 4 - deque.c
   This program sorts data in a double ended queue, allowing access to the first and last
   elements
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "deque.h"

struct node
{
	int data;
	struct node *prev;
	struct node *next;
};

struct deque
{
	int count;
	struct node *head;
};

/*
 * Function: createDeque
 *
 * Complexity: O(1)
 *
 * Description: Create a circularly, doubly linked list
 */

DEQUE *createDeque(void)
{
	struct deque *dp;

	//allocate memory for deque and dummy node
	dp = malloc(sizeof(struct deque));
	assert(dp != NULL);
	dp->count = 0;
	dp->head = malloc(sizeof(struct node));
	assert(dp->head != NULL);
	//intialize dummy node
	dp->head->next = dp->head;
	dp->head->prev = dp->head;

	return dp;
}

/*
 * Function: destroyDeque
 *
 * Complexity: O(n)
 *
 * Description: Deallocate memory associated with deque pointed to by dp.
 */

void destroyDeque(DEQUE *dp)
{
	
	assert(dp!=NULL);
	struct node *del;

	//free all others nodes before dummy node
	while(dp->head->next != dp->head)
	{
		del = dp->head->next;
		dp->head->next = del->next;
		free(del);
	}

	free(dp);
}

/*
 * Function: numItems
 *
 * Complexity: O(1)
 *
 * Description: Returns the number of items in the deque.
 */

int numItems(DEQUE *dp)
{
	assert(dp != NULL);
	return dp->count;
}

/*
 * Function: addFirst
 *
 * Complexity: O(1)
 *
 * Description: Adds x into a node at the beginning of the deque pointed to by dp.
 */

void addFirst(DEQUE *dp, int x)
{
	struct node *newnode; 
	struct node *temp;

	assert(dp!=NULL);


	//create a new node
	newnode = malloc(sizeof(struct node));
	assert(newnode != NULL);

	/*Place data in new node and rearrange pointers so that it is in between
	  the dummy node and the previous first node*/

	newnode->data = x;
	dp->count++;

	temp = dp->head; //use temp to rearrange pointers of newnode and the dummy node

	newnode->next = temp->next;
	newnode->prev = temp;
	temp->next->prev = newnode;
	temp->next = newnode;
}

/*
 * Function: addLast
 *
 * Complexity: O(1)
 *
 * Description: Adds x into a node at the end of the deque pointed to by dp.
 */

void addLast(DEQUE *dp, int x)
{
	struct node *newnode;
	struct node *temp;

	assert(dp != NULL);
	newnode = malloc(sizeof(struct node));
	assert(newnode != NULL);

	/*Place data in new node and rearrange pointers so that it is before the
	  dummy node and after the last node.*/

	newnode->data = x;
	dp->count++;

	temp = dp->head; //use temp to reaarange pointers of newnode and the dummy node

	newnode->next = dp->head;
	newnode->prev = dp->head->prev;
	temp->prev->next = newnode;
	temp->prev = newnode;
}

/*
 * Function: removeFirst
 *
 * Complexity: O(1)
 *
 * Description: Returns the data in the first node in the deque pointed to by dp and removes the node.
 */

int removeFirst(DEQUE *dp)
{
	int x;
	struct node *np;
	struct node *temp;

	assert(dp != NULL && dp->count > 0);

	temp = dp->head;
	dp->count--;
	np = temp->next;

	/*Place data from first node in x, which gets returned. Then change pointers
	  on dummy node and the second node before deleting the first node.*/

	temp->next = np->next;
	np->next->prev = temp;
	x = np->data;
	free(np);

	return x;
}

/*
 * Function: removeLast
 *
 * Complexity: O(1)
 *
 * Description: Returns the data in last node in the deque pointed to by dp and deletes the node.
 */

int removeLast(DEQUE *dp)
{
	int x;
	struct node *np;
	struct node *temp;

	assert(dp != NULL && dp->count > 0);
	temp = dp->head;
	dp->count--;
	np = temp->prev;

	/*Place data from last node in x, which gets returned. Then change pointers
	  so that the dummy node and second to last node point to each other before
	  deleting the last node.*/

	temp->prev = np->prev;
	np->prev->next = temp;
	x = np->data;
	free(np);
	return x;
}

/*
 * Function: getFirst
 *
 * Complexity: O(1)
 *
 * Description: Returns the data in the first node in the deque pointed to by dp.
 */

int getFirst(DEQUE *dp)
{
	assert(dp != NULL && dp->count > 0);
	return dp->head->next->data;
}

/*
 * Function: getLast
 *
 * Complexity: O(1)
 *
 * Description: Returns the data in the last node in the deque pointed to by dp.
 */

int getLast(DEQUE *dp)
{
	assert(dp != NULL && dp->count > 0);
	return dp->head->prev->data;
}
