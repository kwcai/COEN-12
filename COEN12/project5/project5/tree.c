#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include "tree.h"

struct tree
{
	int data;
	struct tree *left, *right, *parent;
};

void detach(struct tree *root)
{
	assert(root != NULL);

	if(root->parent != NULL) 
	{
		if (root->parent->left == root)
			root->parent->left = NULL;
		else
			root->parent->right = NULL;														
	}
}

/*
 * Function: createTree
 *
 * Complexity: O(1)
 *
 * Description: Creates a new tree. Allocates memory for a root that points to two children.
 */

struct tree *createTree(int data, struct tree *left, struct tree *right)
{
	struct tree *root;
	root = malloc(sizeof(struct tree));
	assert(root != NULL);
	/*Place the data received into the root, make parent pointer point to NULL, and point to children
	  designated by left and right.*/
	root->data = data;
	root->parent = NULL;
	root->left = left;
	root->right = right;

	//Check if left has value
	if(left != NULL) 
	{
		/*Check if left is the right or left child of parent. Change the pointers to break
		connection between left and old parent.*/
		detach(left);
		//Have left point back to root.
		root->left->parent = root;
	}

	//Check if right has value
	if(right != NULL)
	{
		/*Check if right is the right or left child of parent. Change the pointers to break
		connect between left and old parent.*/
		detach(right);
		//Have right point back to root.
		root->right->parent = root;
	}

	return root;
}

/*
 * Function: destroyTree
 *
 * Complexity: O(h)
 *
 * Description: Deallocates memory for subtree pointed to by root
 */

void destroyTree(struct tree *root)
{
	if(root != NULL)
	{
		destroyTree(root->right);
		destroyTree(root->left);
		free(root);
	}
}

/*
 * Function: getData
 *
 * Complexity: O(1)
 *
 * Description: Returns the data from the root of the subtree pointed to by root
 */

int getData(struct tree *root)
{
	assert(root != NULL);
	return root->data;
}

/*
 * Function: getLeft
 *
 * Complexity: O(1)
 *
 * Description: Return the left subtree of the subtree pointed to by root
 */

struct tree *getLeft(struct tree *root)
{
	assert(root != NULL);
	return root->left;
}

/*
 * Function: getRight
 *
 * Complexity: O(1)
 * 
 * Description: Return the right subtree of the subtree pointed to by root
 */

struct tree *getRight(struct tree *root)
{
	assert(root != NULL);
	return root->right;
}

/*
 * Function: getParent
 *
 * Complexity: O(1)
 *
 * Description: Returns the parent tree of the subtree pointed to by root
 */

struct tree *getParent(struct tree *root)
{
	assert(root != NULL);
	return root->parent;
}

/*
 *Function: setLeft
 *
 *Complexity: Expected - O(n log n), Worst - O(n^2) 
 *
 *Description: Makes left the left subtree of root
 */

void setLeft(struct tree *root, struct tree *left)
{
	assert(root != NULL);
	// Checks if root has a left child
	if(root->left != NULL)
		root->left->parent = NULL;

	// Make left the left child of root
	root->left = left;

	// If left already has parent, remove from that subtree
	detach(left);
	root->left->parent = root;
}

/*
 *Function: setRight
 *
 *Complexity: Expected - O(n log n), Worst - O(n^2) 
 *
 *Description: Makes right the right child of root
 */

void setRight(struct tree *root, struct tree *right)
{
	assert(root != NULL);
	// Checks if root has a right child
	if(root->right != NULL)
		root->right->parent = NULL;

	// Make right the right child of root
	root->right = right;

	// If right already has a parent, remove ties to old subtree
	detach(right);

	root->right->parent = root;
}
	



