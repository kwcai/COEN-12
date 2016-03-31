#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include "tree.h"
#include "pack.h"
#define END 256
#define p(x) (((x)-1)/2)
#define l(x) ((x)*2+1)
#define r(x) ((x)*2+2)

int count[];
int test[257];
struct tree *heap[END+1];
struct tree *leaves[END+1];
int size;

/*
 *Function: Insert
 *
 *Complexity: 
 *
 *Description: Inserts a tree into the priority queue, ensuring that the occurences of the tree parent is less than the tree being inserted
 */

void insert(struct tree *leaves)
{
	//int index = count;
	

	/*//Makes sure that the parent of the tree inserted is less than the tree
	while(index > 0 &&  getData(leaf) < getData(heap[p(index)]))
	{
		//Use index to move up the queue
		heap[index] = heap[p(index)];
		index = p(index);
	}

	heap[index] = tr;
	count++;*/

}

//Placeholder function

struct tree *delete(void)
{
	int i, min = 0;
	struct tree *tr;
	for(i = 1; i < size; i++)
	{
		if(getData(heap[i])<getData(heap[min]))
			min = i;
		tr = heap[min];
		heap[min] = heap[--size];
	}
	return tr;
}
		
/*
  *Fucntion: Print
  *
  *Complexity: 
  *
  *Description: Prints out the bit ecodings of the characters
  */

void print(struct tree *tr)
{
	//Move up by recursion until the root is reached
	if(getParent(tr)!=NULL)
		print(getParent(tr));
	//Move back down, printing 0 if it goes down the left path, 1 for right
	if(tr==getLeft(getParent(tr)))
		printf("%d", 0);
	else if(tr==getRight(getParent(tr)))
		printf("%d", 1);
}

/*
 *Function: Main
 *
 *Description: Reads a file and runs creates a huffman tree for characters. Compresses file and places it in another.
 */

int main(int argc, char *argv[])
{
	FILE *fp;
	FILE *fp2;
	int sum;
	int i;
	int k;
	int c;
	struct tree *l, *r;
	struct tree *new;

	fp = fopen(argv[1], "r");
	fp2 = fopen(argv[2], "w");
	assert(fp != NULL);
	assert(fp2 != NULL);

	//To count how many times each character occurs 
	while((c = getc(fp)) != EOF)
		count[c]++;

	//Inserts the counts into trees (each is tree is just a leaf), then inserts the trees into a heap
	for(i = 0;i < END + 1; i++)
	{
		if(count[i] > 0)
		{
			leaves[i] = createTree(count[i], NULL, NULL);
			//insert into a heap
			insert(leaves[i]);
		}
	}

	/*
	while(count > 1)
	{
		//Removes two lowest priority trees, creates new tree with each as subtrees
		l = delete();
		r = delete();
		sum = getData(l) + getData(r);
		new = createTree(sum, l, r);
		insert(new);
	}

	//Prints the characters along with their number of occurences
	for(k = 0; k < END + 1; k++)
	{
		if(counts[k]!=0)
		{
			if(isprint(k)==0)
				printf("%3o: %d", k, counts[k]);			
			else
				printf("'%c': %d", (char)k, counts[k]);
		}
		print(heap[k]);
		printf("\n");
	}*/
	

	//Pack function compresses file
	//pack(fp, fp2, leaves);

	fclose(fp);
	fclose(fp2);

	return 1;
}
