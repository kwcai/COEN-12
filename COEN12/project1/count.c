//Kevin Cai
//COEN 12L
//April 4, 2014
//Thurs 2:15pm
//Lab 1: Program to take in a file and count the number of word

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_WORD_LENGTH 30

int main(int argc, char *argv[]){

	int count = 0;
	FILE *fp;
	int size = MAX_WORD_LENGTH;
	char buffer[size];

	//check for the correct number of arguments
	if(argc != 2){
		printf("Error\n");
		return -1;
	}
	
	//open file and check if it exists
	fp = fopen(argv[1], "r");
	if(fp == NULL){
		printf("File does not exist.\n");
		return -1;
	}

	//Read file, counts each word as it is put into buffer. Continues until end of file.
	while(fscanf(fp, "%s", buffer) != EOF){
		count++;
	}

	printf("%d total words\n", count);

	fclose(fp);//close file

	return 0;

}
