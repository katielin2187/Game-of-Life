/*
 ============================================================================
 Name        : HW2.c
 Author      : Katie Lin
 Version     : 1
 Copyright   : Your copyright notice
 Description : Homework 2 Starter Code
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "tests.h"
#include "production.h"

/**
 *The main function that calls production and checks to see if it is working properly.
 *
 *@param argc Number of words on the command line
 *@param argv Array of pointers to character strings representing the words on the command line.
 * @return true if Program was able to play the game of life
 *         false if something went wrong in the tests.
 */
int main(int argc, char*argv[]) {
	bool ok=false;
	puts("!!!Hi all. We're doing HW2!!!");
	if(tests())
	//if(true)
	{
		ok=production(argc, argv);

		if (ok)
		{
			puts("Game of life seems to have worked.");
		}
		else
		{
			puts("Game of life seems not to have worked.");
		}
	}
	else
	{
		puts("Something went wrong in the tests.");
	}
	return EXIT_SUCCESS;
}

