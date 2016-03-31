/* Kevin Cai
   COEN 12L Thurs
   Project 4 - radix.c
   Takes in a list of numbers and sorts using radix sort. This utilizes an array of deques
   (one for each digit) and sort the list by each digit.
*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "deque.h"

# define r 10

int main(void)
{
	int i, input, m, digits, exp;
	DEQUE *list, *dp[r]; //1 deque for each digit

	//make a deque to hold a list of numbers
	m = 0;
	list  = createDeque();

	//make an array of deques to sort by digit
	for(i = 0; i < r; i++)
		dp[i] = createDeque();

	//read in non-negative intergers
	while(scanf("%d", &input) == 1)
	{
		if(input >= 0)
		{
			addLast(list, input);

			//keep track of max
			if(input > m)
				m = input;
		}
		else
		{
			printf("List cannot contain negative numbers.\n");
			return -1;
		}
	}

	exp = 1;
	//number of iterations through loop
	digits = ceil(log(m + 1)/log(r));

	//Sort list into separate deques by digit
	while(digits > 0)
	{
		//place in respective buckets
		while(numItems(list) > 0)
		{
			input = removeFirst(list);
			addLast(dp[(input/exp) % r], input);
		}

		//Take sorted numbers and place back into list
		for(i = 0; i < r; i++)
		{
			while(numItems(dp[i]) > 0)
			addLast(list, removeFirst(dp[i]));
		}

		exp *= r; //increase exp to check next digit		
		digits--; //decrease after check each digit
	}

	//Print the list
	while(numItems(list) > 0)
	printf("%d\n", removeFirst(list));

	return 1;
}
