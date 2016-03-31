#include <cassert>
#include "deque.h"

/*
 * Class declaration for node
 */

class Node {
	public:
	int data;
	Node *next;
	Node *prev;
};

/*
 * Function: Deque
 *
 * Complexity: O(1)
 *
 * Description: Constructer to make a circularly doubly linked list
 */

Deque::Deque(void)
{
	count = 0;
	head = new Node;
	
	head->next = head;
	head->prev = head;
}

/*
 * Function: ~Deque
 *
 * Complexity: O(n)
 *
 * Description: Destructer that deallocates memory use by a deque 
 */


Deque::~Deque()
{
	Node *np, *next;

	np = head;
	
	//delete all others nodes before dummy node
	do {
	next = np->next;
	delete np;
	np = next;
	} while (np != head);

}

/*
 * Function: size
 *
 * Complexity: O(1)
 *
 * Description: Returns the number of items in the deque.\
 */

int Deque::size()
{
	return count;
}

/*
 * Function: addFirst
 *
 * Complexity: O(1)
 *
 * Description: Adds x into a node at the beginning of the deque
 */

void Deque::addFirst(int x)
{
	Node *np, *sentinel;
	
	/*Place data in new node and rearrange pointers so that it is in between
	 the dummy node and the previous first node*/

    np = new Node;
	np->data = x;
	
    count++;
    sentinel = head;

	np->prev = sentinel;
	np->next = sentinel->next;
	
    sentinel->next->prev = np;
    sentinel->next = np;
}

/*
 * Function: addLast
 *
 * Complexity: O(1)
 *
 * Description: Adds x into a node at the end of the deque
 */

void Deque::addLast(int x)
{
    Node *np, *sentinel;
	
	/*Place data in new node and rearrange pointers so that it is before the
	 dummy node and after the last node.*/
	
    np = new Node;
    np->data = x;
	
    sentinel = head;
    count++;

	np->prev = sentinel->prev;
	np->next = sentinel;
	
    sentinel->prev->next = np;
    sentinel->prev = np;
}

/*
 * Function: removeFirst
 *
 * Complexity: O(1)
 *
 * Description: Returns the data in the first node in the deque and removes the node.
 */

int Deque::removeFirst()
{
    int x;
    Node *np, *sentinel;
	
	
    assert(count > 0);
    sentinel = head;
    count--;
	
	/*Place data from first node in x, which gets returned. Then change pointers
	 on dummy node and the second node before deleting the first node.*/
	
    np = sentinel->next;
    sentinel->next = np->next;
    np->next->prev = sentinel;
	
    x = np->data;
    delete np;
    return x;
}

/*
 * Function: removeLast
 *
 * Complexity: O(1)
 *
 * Description: Returns the data in last node in the deque and deletes the node.
 */


int Deque::removeLast()
{
    int x;
    Node *np, *sentinel;
	
	
    assert(count > 0);
    sentinel = head;
    count--;
	
	
	/*Place data from last node in x, which gets returned. Then change pointers
	 so that the dummy node and second to last node point to each other before
	 deleting the last node.*/
	
    np = sentinel->prev;
    sentinel->prev = np->prev;
    np->prev->next = sentinel;
	
    x = np->data;
    delete np;
    return x;
}

/*
 * Function: getFirst
 *
 * Complexity: O(1)
 *
 * Description: Returns the data in the first node in the deque
 */

int Deque::getFirst()
{
    assert(count > 0);
    return head->next->data;
}

/*
 * Function: getLast
 *
 * Complexity: O(1)
 *
 * Description: Returns the data in the last node in the deque
 */

int Deque::getLast()
{
	assert(count > 0);
    return head->prev->data;
}

