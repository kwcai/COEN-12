/*
  Kevin Cai
  COEN 12L Thurs

  This program stores elements in a set. The array used is unsorted.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include "set.h"

//Set containing an array with the number of elements and length
//O(n)
struct set{
	int count;
	int size;
	char **elts;
};

//traverses through the array for an element and returns its location if
//it is in the array
//O(n)
static int findElement(SET *sp, char *elt){
	int i;

	//search
	for(i = 0; i < sp->count; i++){
		if(strcmp(sp->elts[i], elt) == 0)
			return i;
	}

	return -1;
}

//Creates the set and initializes array or elements
//O(1)
SET *createSet(int maxElts){	

	SET *sp;

	//allocate memory
	sp = malloc(sizeof(SET));
	assert(sp != NULL);
	sp->elts = malloc(sizeof(char *) *maxElts);
	assert(sp->elts != NULL);

	sp->count = 0;
	sp->size = maxElts;
	return sp;

}

//deallocate memory used by set
//O(n)
void destroySet(SET *sp){
	assert(sp != NULL);

	int i;
	//traverse array, freeing each element
	for(i = 0; i < sp->count; i++)
		free(sp->elts[i]);

	//deallocate array and sp
	free(sp->elts);
	free(sp);
}

//returns number of elements in set
//O(1)
int numElements(SET *sp){
	assert(sp != NULL);
	return sp->count;
}

//checks if elt is in the set
//O(n)
bool hasElement(SET *sp, char *elt){
	assert(sp != NULL && elt != NULL);

	if(findElement(sp, elt) != -1)
		return true;
	else
		return false;
}

//adds elt to the set and returns if the set has changed
//O(n)
bool addElement(SET *sp, char *elt){
	assert(sp != NULL && elt != NULL);

	//check if the array is full or the elt is already in array
	if(sp->count == sp->size || findElement(sp, elt) != -1)
		return false;

	//add elt to the end of array
	elt = strdup(elt);
	assert(elt != NULL);
	sp->elts[sp->count] = elt;
	sp->count++;
	return true;
}

//removes elt from the set and returns if the set has changed
//O(n)
bool removeElement(SET *sp, char *elt){
	assert(sp != NULL && elt != NULL);

	int index;

	//use findELement to obatin index of elt
	index = findElement(sp, elt);

	if(index == -1)
		return false;

	//delete elt and rplace it with the last element in the set
	free(sp->elts[index]);
	sp->elts[index] = sp->elts[sp->count - 1];
	sp->count--;
	return true;
}
