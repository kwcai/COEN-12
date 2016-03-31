/*
   Kevin Cai
   COEN 12L Thurs

   Stores element in a set. The elements are placed in an array which is sorted using hashing.
   An array of flags is used to keep track of when a location is empty, filled, or an elt was deleted.
   
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include "set.h"

#define EMPTY 0
#define FILLED 1
#define DELETED 2

struct set
{
	int count;
	int length;
	char **elts;
	char *flags; //array of flags to track status of a location
};

/*
 * Function: createSet
 *
 * Complexity: O(n)
 *
 * Description: create a new set with size of maxElts
 *
 */

SET *createSet(int maxElts)
{
	SET *sp;
	int i;

	//allocate memory
	sp = (SET *)malloc(sizeof(SET));
	sp->count = 0;
	sp->length = maxElts;
	sp->elts = malloc(sizeof(char *)*maxElts);
	assert(sp->elts != NULL);
	sp->flags = malloc(sizeof(char)*maxElts);
	assert(sp->flags != NULL);
	//initialize array of flags to empty
	for(i = 0;i < maxElts;i++)
		sp->flags[i] = EMPTY;
	return sp;
}

/*
 * Function: destroySet
 *
 * Complexity: O(n)
 *
 * Description: deallocate memory for set pointed to by sp.
 */

void destroySet(SET *sp)
{
	int i;

	assert(sp != NULL);

	//traverse array
	for(i = 0;i < sp->length;i++)
	{
		if(sp->flags[i] == FILLED)//free each filled element
			free(sp->elts[i]);
	}

	//deallocated array and sp
	free(sp->elts);
	free(sp);
	return;
}

/*
 * Function: hashString
 *
 * Complexity: O(n)
 *
 * Description: The hash function determines the location for given string.
 */

unsigned hashString(char *s)
{
	unsigned hash=0;

	while(*s!='\0')
		hash = 31 * hash + *s ++;
	return hash;
}

/*
 * Function: findElement
 *
 * Complexity: Best case: O(1), Worst case: O(n)
 *
 * Description: Searches for an element in set by checking the location that it should be in.
 */

static int findElement(SET *sp, char *elt, bool *found)
{
	assert(sp != NULL);
	assert(elt != NULL);

	int i;
	int locn;
	int lastlocn;
	int rem;
	int flag = 0;
	locn = hashString(elt) % sp->length; //use the hashing algorithm to determine the initial location
	lastlocn = locn - 1;

	//Loop to traverse through array
	for(i = 0; i < sp->length; i++)
	{
		//See if element matches elt
		if(sp->flags[locn] == FILLED)
		{		
			if(strcmp(sp->elts[locn],elt) == 0)
			{
				*found = true;
				return locn;
			}
		}
		//Remember the location of a deleted element
		else if(sp->flags[locn] == DELETED)
		{
			if(flag == 0)
			{
				rem = locn;
				flag = 1;
			}
		}
		//If location is empty and there are no previous deleted spots, return location
		else
		{
			*found = false;
			if(flag == 1)
				return rem;
			return locn;
		}
		locn++;
		locn = locn % sp->length; //Mod by the length of array so loop can go back to first element
	}

	return -1;

}

/*
 * Function: hasElement
 *
 * Complexity: O(n)
 *
 * Description: checks whether an element is in the set or not
 */

bool hasElement(SET *sp, char *elt)
{
	bool found;

	assert(sp != NULL && elt != NULL);
	//Call findElement to check if elt is in set
	findElement(sp, elt, &found);

	if(found == true)
		return true;
	else
		return false;
}

/*
 * Function: numElements
 *
 * Complexity: O(1)
 *
 * Description: returns the number of elements in the set
 */

int numElements(SET *sp)
{

	assert(sp != NULL);
	return sp->count;
}

/*
 * Function: addElement
 *
 * Complexity: Best case: O(1), Worst case: O(n)
 *
 * Description: add and element to the set
 */

bool addElement(SET *sp, char *elt)
{

	bool found;
	int locn;

	assert(sp != NULL && elt != NULL);

	//obtain the location using findElement
	locn = findElement(sp, elt, &found);

	//makes sure the element is not already in the set
	if(found)
		return false;

	//copy elt into set and change flag of location to FILLED
	sp->elts[locn] = strdup(elt);
	assert(sp->elts[locn] != NULL);
	sp->flags[locn] = FILLED;
	sp->count++;
	return true;
}

/*
 * Function: removeElement
 *
 * Complexity: Best case: O(1), Worst case: O(n)
 *
 * Description: remove elt from set
 */

bool removeElement(SET *sp, char *elt)
{
	int location;
	bool found;

	assert(sp != NULL && elt != NULL);
	
	//obtain the location using findElement
	location=findElement(sp, elt, &found);

	//if elt is not found, return
	if(!found)
		return false;

	//remove elt and change flag of location to DELETED
	sp->flags[location] = DELETED;
	free(sp->elts[location]);
	sp->count--;
	return true;
}
