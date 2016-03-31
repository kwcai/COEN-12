/*
   Kevin Cai
   COEN 12L Thurs

   Stores elements in a set. The elements are placed in a sorted array.

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include "set.h"

struct set{
	int count;
	int size;
	char **elts;
};

//uses binary search to find the correct location
//O(log n)
static int findElement(SET *sp, char *elt, bool *found){
	int lo, hi, mid, diff;
	
	lo = 0;
	hi = sp->count - 1;

	//Takes midpoints until the correct location is found
	while(lo <= hi){

		mid = (lo + hi)/2;
		//Use strcmp to check if elt is larger, smaller, or equal to
		//the element in location
		diff = strcmp(elt, sp->elts[mid]);

		//change constraints depending on value of diff
		if(diff < 0) //elt is in lower range
			hi = mid - 1;
		else if(diff > 0) //elt is in upper range
			lo = mid + 1;
		else {
			*found = true;
			return mid;
		}
	}

	*found = false;
	return lo;
}

//creates a set containing an array of elts and its count and capacity
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

//deallocate the memory used by the set
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

//returns the number of elements in set
//O(1)
int numElements(SET *sp){
	assert(sp != NULL);
	return sp->count;
}

//checks if elt is in the set
//O(log n)
bool hasElement(SET *sp, char *elt){
	assert(sp != NULL && elt != NULL);
		
	int index;
	bool found;

	index = findElement(sp, elt, &found);
	return found;
}

//adds an element to the set at location determined by the search
//keeps the array sorted by moving all subsequent elements up
//O(n)
bool addElement(SET *sp, char *elt){
	assert(sp != NULL && elt != NULL);

	int i;
	int index;
	bool found;

	//check if array is full
	if(sp->count == sp->size)
		return false;

	index = findElement(sp, elt, &found);

	//check if elt is already in array
	if(found)
		return false;
	//move all elts, starting at the location elt needs to be inserted
	//to the right
	for(i = sp->count; i > index; i--)
		sp->elts[i] = sp->elts[i - 1];
	elt = strdup(elt);
	assert(elt != NULL);
	sp->elts[index] = elt;
	sp->count++;

	return true;
}

//uses findElement to find elt and delete it
//keeps array sorted by moving the subsequent elements down
//O(n)
bool removeElement(SET *sp, char *elt){
	assert(sp != NULL && elt != NULL);

	int i;
	int index;
	bool found;

	//check if array is empty
	if(sp->count == 0)
		return false;

	index = findElement(sp, elt, &found);

	if(!found)
		return false;

	//free elt
	free(sp->elts[index]);

	//move rest of elements to left, filling in space of freed elt
	for(i = index + 1; i < sp->count; i++)
		sp->elts[i - 1] = sp->elts[i];

	sp->count--;
	return true;
}
