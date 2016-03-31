#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include "tree.h"
#include "pack.h"
#define END 256

int count[END];
struct tree *heap[END+1];
struct tree *leaves[END+1];
int heapcounter = 0;

/*
 *Function: Delete
 *
 *Complexity:
 *
 *Description:
 */

struct tree * deleteMin()
{
	int i = 0;
	int child;
	struct tree *min = heap[0];
	struct tree *x = heap[--(heapcounter)];

	while(i * 2 + 1 < heapcounter)
	{
		child = i * 2 + 1;
		if(child + 1 < heapcounter && getData(heap[child]) > getData(heap[child + 1]))
			child++;
		if(getData(x) > getData(heap[child]))
		{
			heap[i] = heap[child];
			i = child;
		}
		else
			break;
	}

	heap[i] = x;
	return min;
}

/*
 *Function: Insert
 *
 *Complexity: O(n log(n)) 
 *
 *Description: Inserts a tree into the priority queue, ensuring that the occurences of the tree parent is less than the tree being inserted
 */

void insert(struct tree *root)
{
	int i;
	i = (heapcounter)++;

	while(i > 0 && getData(heap[(i - 1)/2]) > getData(root))
	{
		heap[i] = heap[(i - 1)/2];
		i = (i - 1)/2;
	}
	heap[i] = root;
}

 /*
  *Function: Print
  *
  *Complexity: O(n log(n))
  *
  *Description: Prints out the bit ecodings of the characters
  */

void print(struct tree *root)
{
	if(getParent(root) != NULL)
	{
		print(getParent(root));
		if(getLeft(getParent(root)) == root)
			printf("0");
		else
			printf("1");
	}
}


/*
 *Function: Main
 *
 *Description: Reads a file and creates a huffman tree for characters. Compresses file and places it in another.
 */

int main(int argc, char *argv[])
{
	FILE *fp;
	int c, i, j, k, m;
	int charcount = 0;
	int check = 0;

	if(argc != 3)
	{
		printf("Missing file\n");
		return -1;
	}

	fp = fopen(argv[1], "r");
	if(fp == NULL)
	{
		printf("File does not exist.\n");
		return -1;
	}

	for(i = 0; i < END + 1; i++)
		count[i] = 0;

	//To count how many times each character occurs 
	while((c = getc(fp)) != EOF)
	{
		charcount++;
		count[c]++;
	}


	for(j = 0; j < END + 1; j++)
		check += count[j];

	if(check != charcount)
	{
		printf("Counting Error\n");
		return -1;
	}

	//Inserts the counts into trees (each is tree is just a leaf), then inserts the trees into a heap
	for(k = 0; k < END + 1; k++)
	{
		if(count[k] > 0)
		{
			leaves[k] = createTree(count[k], NULL, NULL);
			insert(leaves[k]);
		}
		else
			leaves[k] = NULL;
	}

	leaves[END] = createTree(0, NULL, NULL);
	insert(leaves[END]);

	//"while heap has more than one tree in it, remove the two lowest"
	while(heapcounter > 1)
	{
		struct tree *l, *r, *root;
		l = deleteMin();
		r = deleteMin();
		root = createTree(getData(l) + getData(r), l, r);

		insert(root);
	}

	//print the characters along with their number of occurences
	for(m = 0; m < END + 1; m++)
	{
		if(count[m] > 0)
		{
			if(isprint(m) != 0)
				printf(" '%c' : %d ", m, getData(leaves[m]));
			else
				printf(" '0%o': %d ", m, getData(leaves[m]));
			print(leaves[m]);
			printf("\n");
		}
	}

	printf(" '%o' : %d ", END, getData(leaves[END]));
	print(leaves[END]);
	printf("\n");

	//Pack function compresses file
	pack(argv[1], argv[2], leaves);

	destroyTree(heap[0]);
	fclose(fp);

	return 0;
}
