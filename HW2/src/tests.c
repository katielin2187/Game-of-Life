/*
 * tests.c
 *
 *  Created on: Nov 3, 2018
 *      Author: student
 */
#include <stdbool.h>
#include "tests.h"
#include "production.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h> //for strncmp

/**
 * This function calls all the test functions and checks to see if everything is working properly.
 * @return true if Program was able to play the game of life
 *         false if something went wrong in the tests.
 */
bool tests(void)
{
	bool results=false;
	puts("During tests");

	bool ok1 = testReadInput();
	if(ok1)puts("Found and read the file.");

	bool ok2 = testMakeArrays();
	if(ok2)puts("Was able to allocate the arrays ok.");

	bool ok4 = testCountNeighbors();
	if(ok4)puts("CountNeighbors is working");

	bool ok3 = testPlayOne();
	if(ok3)puts("playOne is ok.");


	/////

	bool ok5 = testCheckArrayEquals();
	if(ok5)puts("CheckArrayequals is working");

	bool ok6 = testDoGenerations();
	if(ok6)puts("doGenerations is ok.");

	////

	puts("end of tests");
	results = ok1 && ok2 && ok3;
	return results;
}

/**
 * This function checks to see if the file input is being read properly.
 * @return true if the file input was read properly.
 *         false if file input was not able to be read.
 */
bool testReadInput(void)
{
	//the plan is:
	//create a file
	//make sure it can be opened.
	//try a file that should not exist
	//check that we notice it does not exist

	bool results = false;
	bool ok1 = false;
	bool ok2 = false;
	bool ok3 = false;
	//
	//Here goes: create a file
	FILE* fp;
	fp = fopen("/tmp/LifeInput.txt", "w"); //we write it first for later reading
	if (fp != false)
	{//it opened, yay!
		//file containing a sequence of lines,
		//each consisting of a sequence of 'x' and 'o' characters,
		//indicating the occupied and unoccupied cells
		//of the initial configuration, e.g.
		//oxo
		//xox
		//xox
		//oxo
		int w1 = fprintf(fp, "oxo\n");//returns the number of chars excluding null
		int w2 = fprintf(fp, "xox\n");
		int w3 = fprintf(fp, "xox\n");
		int w4 = fprintf(fp, "oxo\n");
		if ((w1 == w2) && (w2 == w3) && (w3 == w4) && (w4 == 4))
		{
			ok1 = true;
		}
		fclose(fp);
	}
	fp = fopen("/tmp/LifeInput.txt", "r"); //we try to read it
	if (fp != false)
	{//it opened, yay!
		ok2 = true;

		ok3 = true;
		//can we read the correct data?
		char oRow[4]; //test case, we know a string of 3 chars terminated by null
		int count =  fscanf(fp, "%s", oRow);
		//printf("First row is %s\n", oRow);
		if(0 != strncmp(oRow, "oxo", 4))//0 means match
		{//got the right data
			ok3 = false;
		}
		fscanf(fp, "%s", oRow);
		//printf("Second row is %s\n", oRow);
		if(0 != strncmp(oRow, "xox", 4))
		{//got the right data
			ok3 = false;
		}
		fscanf(fp, "%s", oRow);
		//printf("Third row is %s\n", oRow);
		if(0 != strncmp(oRow, "xox", 4))
		{//got the right data
			ok3 = false;
		}
		fscanf(fp, "%s", oRow);
		//printf("Fourth row is %s\n", oRow);
		if(0 != strncmp(oRow, "oxo", 4))
		{//got the right data
			ok3 = false;
		}
	}

	// Still need to try opening a non-existent file for reading.

	results = ok1 && ok2 && ok3;
	return results;
}

/**
 * This function checks to see if the arrays are able to be made properly.
 * @return true if Program was able to create arrays.
 *         false if the arrays are not able to be made.
 */
bool testMakeArrays(void)
{
	bool results = false;
	bool ok1 = false;
	//we need to allocate and populate arrays
	//In this test case we set our arrays to 4 rows x3 columns
	int nRows = 4;
	int nCols = 4;
	char boardBefore[4][4]={
			{'o','x','o','\0'},
			{'x','o','x','\0'},
			{'x','o','x','\0'},
			{'o','x','o','\0'}
	};

	char boardAfter[nRows][nCols];
	//here's the test
	for(int row=0;row<nRows;row++)
	{
		for(int col=0; col<nCols; col++)
		{
			boardAfter[row][col]=boardBefore[row][col];
		}
	}
	ok1 = true;
	for(int row=0;row<nRows;row++)
	{
		for(int col=0; col<nCols; col++)
		{
			if (boardAfter[row][col]!=boardBefore[row][col])
			{
				ok1=false;
			}
		}
	}

	results = ok1;
	return results;
}

/**
 * This function calls PlayOne and checks to see if it is working properly.
 * @return true if PlayOne does what it is supposed to do.
 *         false if PlayOne does not work properly.
 */
bool testPlayOne(void)
{
	bool results = false;
	bool ok1 = false;
	bool ok2 = false;

	puts("test PlayOne:");

	//test set 1A
	int nRows = 4;
	int nCols = 3;

	puts("Testing case 1: same board after.\n");

	char boardBefore[4][3]={
			{'o','x','o'},
			{'x','o','x'},
			{'x','o','x'},
			{'o','x','o'}
	};
	char correctBoardAfter[4][3]={
			{'o','x','o'},
			{'x','o','x'},
			{'x','o','x'},
			{'o','x','o'}
	};

	char boardAfter[nRows][nCols];
	//here's the invocation
	//PlayOne(nRows, nCols, boardBefore, boardAfter);
	PlayOne(nRows, nCols, (char*)boardBefore, (char*)boardAfter);
	//here's the check
	ok1 = true; //no errors found yet
	for(int row=0;row<nRows;row++)
	{
		for(int col=0; col<nCols; col++)
		{
			if(correctBoardAfter[row][col] != boardBefore[row][col]) //being changed to false when I try testing; figure out why
			{//error found
				ok1 = false;
			}
		}
	}


	//test set 1B
	///////////////////////////////////

	puts("Testing board 2: bottom right char is changed.\n");
	char boardBefore2[4][3]={
			{'o','o','o'},
			{'o','o','o'},
			{'o','x','x'},
			{'o','x','o'}
	};
	char correctBoardAfter2[4][3]={
			{'o','o','o'},
			{'o','o','o'},
			{'o','x','x'},
			{'o','x','x'}
	};

	char boardAfter2[nRows][nCols];
	PlayOne(nRows, nCols, (char*)boardBefore2, (char*)boardAfter2);
	for(int row=0;row<nRows;row++)
	{
		for(int col=0; col<nCols; col++)
		{
			if(boardAfter2[row][col] != correctBoardAfter2[row][col]) //being changed to false when I try testing; figure out why
			{//error found
				printf("row: %d, col: %d, should be %c. is %c \n", row, col, correctBoardAfter2[row][col], boardAfter2[row][col]);
				ok1 = false;
			}
		}
	}

	printBoard(nRows, nCols, (char*) boardAfter2); //prints boardAfter2 to check if the result is the same as correctBoardAfter2

	//test set 2A //glider

	int nRows2 = 3;
	int nCols2 = 3;

	puts("\nTesting board 3: glider pattern");
	char boardBefore3[3][3]={
			{'o','o','x'},
			{'x','o','x'},
			{'o','x','x'},
	};
	char correctBoardAfter3[3][3]={
			{'o','x','o'},
			{'o','o','x'},
			{'o','x','x'},
	};

	char boardAfter3[nRows2][nCols2];
	//here's the invocation
	//PlayOne(nRows, nCols, boardBefore, boardAfter);
	PlayOne(nRows2, nCols, (char*)boardBefore3, (char*)boardAfter3);
	//here's the check
	ok1 = true; //no errors found yet


	for(int row=0;row<nRows2;row++)
	{
		for(int col=0; col<nCols2; col++)
		{
			if(correctBoardAfter3[row][col] != boardAfter3[row][col]) //being changed to false when I try testing; figure out why
			{//error found
				printf("row: %d, col: %d, should be %c. is %c \n", row, col, correctBoardAfter3[row][col], boardAfter3[row][col]);
				ok1 = false;
			}
		}
	}




	results = ok1;
	return results;
}

/**
 * This function calls CountNeighbors and checks to see if it counting
 * the right amount of neighbors.
 *
 * @return true if the correct neighbors are counted for a certain cell.
 *         false if the neighbors counted are incorrect.
 */
bool testCountNeighbors(void)
{
	bool ans = false;

	int nRows = 4;
	int nCols = 3;

	puts("test countGenerations:");

	char boardBefore[4][3]={
			{'o','x','o'},
			{'x','o','x'},
			{'x','o','x'},
			{'o','x','o'}
	};

	puts("test 1.\n");
	int n1 = CountNeighbors(0, 0, nRows, nCols, (char*) boardBefore); //row 0 column 0
	printf("Should be 2 and it was %d\n", n1);
	if(n1!= 2){
		puts("could not count test case 1");
	}

	puts("test 2.\n");
	int n2 = CountNeighbors(0, 1, nRows, nCols, (char*) boardBefore); //row 0 column 1
	printf("Should be 2 and it was %d\n", n2);
	if(n2!= 2){
		puts("could not count test case 2");
	}

	puts("test 3.\n");
	int n3 = CountNeighbors(0, 2, nRows, nCols, (char*) boardBefore); //row 0 column 2
	printf("Should be 2 and it was %d\n", n3);
	if(n3!= 2){
		puts("could not count test case 3");
	}

	puts("test 4.\n");
	int n4 = CountNeighbors(1, 0, nRows, nCols, (char*) boardBefore); //row 1 column 0
	printf("Should be 2 and it was %d\n", n4);
	if(n4!= 2){
		puts("could not count test case 4");
	}

	puts("test 5.\n");
	int n5 = CountNeighbors(1, 1, nRows, nCols, (char*) boardBefore); //row 1 column 1
	printf("Should be 5 and it was %d\n", n5);
	if(n5!= 5){
		puts("could not count test case 5");
	}

	puts("test 6.\n");
	int n6 = CountNeighbors(1, 2, nRows, nCols, (char*) boardBefore); //row 1 column 2
	printf("Should be 2 and it was %d\n", n6);
	if(n6!= 2){
		puts("could not count test case 6");
	}

	puts("test 7.\n");
	int n7 = CountNeighbors(2, 0, nRows, nCols, (char*) boardBefore); //row 2 column 0
	printf("Should be 2 and it was %d\n", n7);
	if(n7!= 2){
		puts("could not count test case 7");
	}

	puts("test 8.\n");
	int n8 = CountNeighbors(2, 1, nRows, nCols, (char*) boardBefore); //row 2 column 1
	printf("Should be 5 and it was %d\n", n8);
	if(n8!= 5){
		puts("could not count test case 8");
	}

	puts("test 9.\n");
	int n9 = CountNeighbors(2, 2, nRows, nCols, (char*) boardBefore); //row 2 column 2
	printf("Should be 2 and it was %d\n", n9);
	if(n9!= 2){
		puts("could not count test case 9");
	}

	puts("test 10.\n");
	int n10 = CountNeighbors(3, 0, nRows, nCols, (char*) boardBefore); //row 3 column 0
	printf("Should be 2 and it was %d\n", n10);
	if(n10!= 2){
		puts("could not count test case 10");
	}

	puts("test 11.\n");
	int n11 = CountNeighbors(3, 1, nRows, nCols, (char*) boardBefore); //row 3 column 1
	printf("Should be 2 and it was %d\n", n11);
	if(n11!= 2){
		puts("could not count test case 11");
	}

	puts("test 12.\n");
	int n12 = CountNeighbors(3, 2, nRows, nCols, (char*) boardBefore); //row 3 column 2
	printf("Should be 2 and it was %d\n", n12);
	if(n12!= 2){
		puts("could not count test case 12");
	}


	return ans;
}

/**
 * This function calls checkArrayEquals and checks to see if the given arrays are the same.
 *
 * @return true if the given arrays are equal.
 *         false if the any of the elements in the arrays are different.
 */
bool testCheckArrayEquals(void)
{
	bool ans = true;

	puts("test checkArrayEquals:");

	//test set 1A
	int nRows = 4;
	int nCols = 3;

	puts("Testing case 1: same board after.\n");

	char boardBefore[4][3]={
			{'o','x','o'},
			{'x','o','x'},
			{'x','o','x'},
			{'o','x','o'}
	};
	char boardAfter[4][3]={
			{'o','x','o'},
			{'x','o','x'},
			{'x','o','x'},
			{'o','x','o'}
	};

	//char boardAfter[nRows][nCols];

	bool checkArray = checkArrayEquals(nRows, nCols, (char*)boardBefore, (char*)boardAfter);

	if(checkArray == false){
		ans = false;
		puts("The arrays are not equal.");
	}

	printf("The boards are equal: %s\n", (checkArray) ? "true" : "false"); //print out checkArray boolean

	//////////
	puts("Testing case 2: different board after.\n");

		char boardBefore2[4][3]={
				{'o','x','o'},
				{'x','o','x'},
				{'x','o','x'},
				{'o','x','o'}
		};
		char boardAfter2[4][3]={
				{'o','x','o'},
				{'x','x','x'},
				{'x','o','x'},
				{'o','x','o'}
		};

		//char boardAfter[nRows][nCols];

		bool checkArray2 = checkArrayEquals(nRows, nCols, (char*)boardBefore2, (char*)boardAfter2);

		if(checkArray2 == true){
			ans = false;
			puts("The arrays are equal.");
		}

		printf("The boards are equal: %s\n", (checkArray2) ? "true" : "false"); //print out checkArray boolean


	return ans;
}

/**
 * This function calls doGenerations and checks to see if doGenerations quits when it is supposed to.
 *
 * @return true if doGenerations returns the correct count of generations.
 *         false if doGenerations returns the incorrect count of generations.
 */
bool testDoGenerations(void)
{
	bool ans = true;

	puts("test doGenerations:");

	//int doGenerations(unsigned int nr, unsigned int nc, int given_gens, char* A, char* B, char* C, char print, char pause)

	//test set 1A
		int nRows = 4;
		int nCols = 3;

		puts("Testing case 1: same board after.\n");

		char boardBefore[4][3]={
				{'o','x','o'},
				{'x','o','x'},
				{'x','o','x'},
				{'o','x','o'}
		};
		char boardAfter[4][3]={
				{'o','x','o'},
				{'x','o','x'},
				{'x','o','x'},
				{'o','x','o'}
		};

		char C[4][3];

	int gens_count = doGenerations(nRows, nCols, 3, (char*)boardBefore, (char*)boardAfter, (char*)C, 'y', 'n');

	 if(gens_count>2){
		 ans = false;
		 puts("The generation count was wrong");
	 }

	 printf("The generation count: %d\n", gens_count); //print out gens_count

	return ans;
}


