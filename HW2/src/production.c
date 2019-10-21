/*
 * production.c
 *
 *  Created on: Nov 3, 2018
 *      Author: Katie Lin
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "production.h"
#include <math.h>

// create 3 different 2-d arrays,
// one for the current generation,
// previous generation
// two generations ago

/**
 *Your production code goes in this function.
 *
 *@param argc Number of words on the command line
 *@param argv Array of pointers to character strings representing the words on the command line.
 * @return true if Program was able to play the game of life
 *         false if User entered bad input.
 */
bool production(int argc, char* argv[])
{
	FILE* input;
	bool results = false;
	bool done = false;
	int nRows=-1;
	int nCols = -1;
	int gens = 0; //number of generations to play
	char print = 'n'; //set print default
	char pause = 'n'; //set pause default

	//etc.
	//get the NR NC gens input [print] [pause], Usage as needed.
	// Must first check if there are at least 4 arguments on the command line
	// Next, check if print and pause are on the command line
	//printf("Argc %d", argc);

	if(argc< 5) { // if there are less than five given arguments
		//done = true; //can't run at all
		printf("Not enough arguments.");
		done = true;
	} else if (argc<6) { //this means it was 5
		//print and pause are set to default

	} else if(argc<7) {  //must be 6 that pause is not included, so give it a default value
		print = argv[5][0];
	} else if (argc == 7){
		print = argv[5][0];  //[0]-since they are given characters
		pause = argv[6][0];
		//printf("The print argument is %c, the pause argument is %c\n", print, pause);
	}	// at this point all the input argument values are established


	//rows
	char* ptr=0;
	long nr_l = strtol(argv[1],&ptr,10);//get the NR
	nRows = (int)nr_l; //user specified rows

	if(nRows<1){
		printf("Usage: Rows should be greater than 0, received %d.\n",nRows);
		done = true;
	} else {
		printf("The number of rows is %d\n", nRows);
	}

	//columns
	long nc_l = strtol(argv[2],&ptr,10);//get the NC
	nCols = (int)nc_l; //user specified columns

	if(nCols<1) {
		printf("Usage: Columns should be greater than 0, received %d.\n",nCols);
		done = true;
	} else {
		printf("The number of columns is %d\n", nCols);
	}

	//gens
	long n_gens = strtol(argv[3], &ptr,10); //get the gens
	gens = (int)n_gens; //user specified columns

	if(gens<1) {
		printf("Usage: Generations should be greater than 0, received %d.\n",gens);
		done = true;
	} else {
		printf("The number of generations is %d\n", gens);
	}

	/*printf("The input variables are nRows: %d, nCols: %d, print: %c, pause: %c. \n", nRows, nCols, print, pause);
	// print out all the current arguments */

	//import file contents
	input = fopen(argv[4], "r"); //read this file, r stands for read

	if (!input){
		printf("Can't read file.");
		done = false;
	} else {
		char A[nRows][nCols];  //3 Multidimensional array created
		char B[nRows][nCols];
		char C[nRows][nCols];

		//need to find out how many lines the file has in it and it has to be less than or equal to nRows
		char temp_String[100]; //have a temporary array that reads the file and counts the rows
		int howManyLines = 0;
		bool notdone = true;
		int max_Width = 0;

		while(notdone){
			temp_String[0]='\0';
			int count = fscanf(input, "%s", temp_String);
			int howManyChars = strlen(temp_String);
			//printf("The number of characters is : %d \n", howManyChars);

			if (strlen(temp_String) > max_Width){
				max_Width = strlen(temp_String);
			}

			howManyLines++;
			if(count<=0){
				howManyLines--;
				notdone = false;
			}
		} // the variable, howManyLines knows how many lines are in the file, && know max_Width

		fclose(input); // close the file
		fopen(argv[4], "r"); //open it again to read the content

		for(int r = 0; r<nRows;r++){
			for(int c = 0; c<nCols;c++){
				A[r][c] = 'o';  // fill the entire multi-array A, with o's
				B[r][c] = 'o';  // fill the entire multi-array B, with o's
				C[r][c] = 'o';  // fill the entire multi-array C, with o's
			}
		}

		int dest_r; //row destination
		//put file content into a array
		printf("good lines in file is %d\n",howManyLines);
		for(int r = 0; r<howManyLines;r++){

			int count =  fscanf(input, "%s", temp_String); //the name of the array serves as a pointer

			//puts(temp_String); //temp_string is currently okay
			int howManyChars = strlen(temp_String);
			//printf("number of chars in line %d is %d\n", r, howManyChars);

			for(int j=0; j<howManyChars; j++){
				// get the character out of temp_String and put it into A, and
				//calculate where in A it needs to be put
				int dest_c = ((nCols-max_Width)/2 ) + j; //calculate the destination and put the character //centers in array
				dest_r = ((nRows-howManyLines)/2 )+r; //center in array , want to make sure null characters aren't being copied into A

				//printf("%c", temp_String[j]); //print out temp_String[j]

				A[dest_r][dest_c] = temp_String[j];
				//printf("%c || %c on row %d, and col %d\n", A[dest_r][dest_c], temp_String[j],r,j);
			}//all cols in file are read
		}  //all rows in the file have been read

		//3 char pointers that point to the first element of each given multidimensional array
		char* old_p;
		char* new_p;
		char* other_p;

		//Initial: at this time A is playing the role of old, B is playing new
		old_p= (char*) A;
		new_p=(char*) B;
		other_p=(char*) C;

		int playGens = doGenerations(nRows, nCols, gens, (char*) old_p, (char* ) new_p, (char*) other_p, print, pause);


		/*if(allDead){
			printf("All the organisms died.", gens);
		}*/ //check how all organisms die

		if(playGens == gens ){
			printf("The generations, %d, was reached.\n", playGens);
			results = true;
		} else if(playGens< gens){ //gen count was terminated early
			printf("The pattern was repeating %d.\n", playGens);
			results = true;
		}

	}

	return results;
}

/**
 *Prints out the board.
 *
 *@param nRows The rows of the playing field.
 *@param nCols The columns of the Playing field.
 */
void printBoard(int nRows, int nCols, char* L){
	printf("in print board with nRows = %d, and nCols = %d\ and L is %p\n", nRows, nCols, L);
	for(int r = 0; r<nRows; r++){
		//printf("r is %d\n",r);
		for(int c= 0; c< nCols; c++){
			//printf("c is %d\n", c);
			printf("%c", *(L+(r*nCols)+c));
		}
		printf("\n");
	}
}

/**
 *Checks to see if the arrays are equal.
 *
 *@param nr The rows of the playing field.
 *@param nc The columns of the playing field.
 *@param A The character pointer to the first array, A, being compared.
 *@param B The character pointer to the second array, B, being compared.
 *@return areEqual true if all the characters in the array are the same,
 *                 false if any of the characters in the array are different.
 */
bool checkArrayEquals(int nc, int nr, char* A, char* B)
{
	bool areEqual = true; //empty arrays are true

	//keeps going as long as the arrays are equal at that point
	for(int r =  0; (r<nr)&& areEqual; r++){
		for(int c=0; (c<nc)&& areEqual; c++){
			//A[r][c] == B[r][c];
			if(*(A+(r*nc)+c)!=*(B+(r*nc)+c)){
				areEqual = false;
			}
		}
	}

	return areEqual;
}

/**
 *Calls PlayOne for the input amount of generations given, unless 1) All organisms die.
 * 2) The pattern of organisms from the previous generation repeats itself. 3) The predefined
 * number of given generations is reached.
 *
 *@param nr Row coordinate of cell
 *@param nc Column coordinate of cell
 *@param A The character pointer to the (Old) array, A.
 *@param B The character pointer to the (New) array, B.
 *@param C The character pointer to the (Other, grandfather) array, C.
 *@param print An optional argument with the value of 'y' or 'n' indicating whether a each generation
 *		       (including generation 0), should be displayed or printed before proceeding to the
 *		       next generation.
 *@param pause An optional argument with the value of 'y' or 'n' indicating whether a keystroke is needed
 *			   between generations. Defaults to 'n'.
 *@return occupied The number of occupied neighbors.
 */
int doGenerations(unsigned int nr, unsigned int nc, int given_gens, char* A, char* B, char* C, char print, char pause)
//char Old[][nc], char New[][nc], char Other[][nc])
{
	//generations is arg 3
	int count_g; //g is the count of generations
	char* Old = A;
	char* New = B;
	char* Other = C;
	bool noDuplicates = true;

	printf("The print argument is %c, the pause argument is %c\n", print, pause);

	for(count_g=0; (count_g<given_gens) && (noDuplicates); count_g++){
		//set new, set old, set other

		//PlayOne(nRows, nCols,(char*) old_p, (char* ) new_p);
		if(print == 'y'){
			//printf("Calling printBoard %d \n,", count_g);
			printBoard(nr, nc, (char* ) Old); //try to print board every time to see what I'm getting so far
		}

		if(pause == 'y'){
			printf("The pause was 'y'. Press Enter to continue:");
			getchar();
		}

		//call playOne
		PlayOne(nr, nc,(char*) Old, (char* ) New); //invoke play one on A, results go to B, A is the old

		//detect a fixed point
		if(checkArrayEquals(nr, nc, New, Old)){
			//static
			puts("Quitting because no change.");
			noDuplicates = false;}
		if(checkArrayEquals(nr, nc, Other,  New)){
			//static
			puts("Oscillation.");
			noDuplicates = false;
		}

		char* temp = Old; //the grandad old
		Old = New;
		New = Other;
		Other = temp; //sets the other to the old old
	}

	printf("count of generations is: %d\n", count_g);
	return count_g;
}


/**
 * Function that counts the neighbors, on all eight sides, of the cell being examined.
 *
 * @param r Row coordinate of cell.
 * @param c Column coordinate of cell.
 * @param nRows The rows of the playing field.
 * @param nCols The columns of the Playing field.
 * @return occupied The number of occupied neighbors.
 */
int CountNeighbors(unsigned int r, unsigned int c, int nRows, int nCols, char* Old)
{
	int occupied=0;
	// use loops to check neighbors, row loop, one before same, after column loop
	//neighbors above
	if (r > 0) {
		if (c> 0) {
			if((*( ((char*) Old) + ((r-1) * nCols) + (c-1)))== 'x'){			//check upper left, r-1, c-1
				occupied++;
				//printf("Found, %d, occupied at upper left(r-1, c-1)\n", occupied);
			}
		}

		if ((*( ((char*) Old) + ((r-1) * nCols) + (c)))== 'x'){		//check upper mid , r-1, c
			occupied++;
			//printf("Found, %d, occupied at upper mid(r-1,c)\n", occupied);
		}

		if(c< nCols-1){
			if ((*( ((char*) Old) + ((r-1) * nCols) + (c+1)))== 'x'){	//check upper right, r-1, c+1
				occupied++;
				//printf("Found, %d, occupied at upper right(r-1,c+1)\n", occupied);
			}
		}
	}
	//neighbors left and right
	if(c>0){
		if ((*( ((char*) Old) + ((r) * nCols) + (c-1)))== 'x'){		//check mid left , r, c-1
			occupied++;
			//printf("Found, %d, occupied at mid left(r,c-1)\n", occupied);
		}
	}

	if(c<nCols-1){
		if ((*( ((char*) Old) + ((r) * nCols) + (c+1)))== 'x'){		//check mid right , r, c+1
			occupied++;
			//printf("Found, %d, occupied at mid right(r,c+1)\n", occupied);
		}
	}
	//neighbors below
	if(r<nRows-1){
		if(c>0) {
			if ((*( ((char*) Old) + ((r+1) * nCols) + (c-1)))== 'x'){	//check lower left r+1, c-1
				occupied++;
				//printf("Found, %d, occupied at lower left(r+1,c-1)\n", occupied);
			}
		}

		if ((*( ((char*) Old) + ((r+1) * nCols) + (c)))== 'x'){		//check lower mid r+1, c
			occupied++;
			//printf("Found, %d, occupied at lower mid(r+1,c)\n", occupied);
		}

		if(c< nCols-1){
			if ((*( ((char*) Old) + ((r+1) * nCols) + (c+1)))== 'x'){	//check lower right r+1, c+1
				occupied++;
				//printf("Found, %d, occupied at lower right(r+1,c+1)\n", occupied);
			}
		}
	}
	return occupied;
}

/**
 * Plays the game of life: If an occupied cell, 'x', has less than 2, or greater than 3 neighbors,
 * the organism and becomes an, 'o'. If an occupied cell, 'x' has 2 or 3 neighbors, the organism survives
 * to the next generation. If an unoccupied cell, 'o', has precisely 3 occupied neighbors,
 * it becomes occupied by a new organism, 'x'.
 *
 *@param nr The rows of the playing field.
 *@param nc The columns of the playing field.
 *@param Old The character pointer to the Old array.
 *@param New The character pointer to the new array.
 */
void PlayOne (unsigned int nr, unsigned int nc, char* Old, char* New)
{
	int nRows = nr;
	int nCols = nc;

	/*for(int row = 0;row < nRows;row++)
	{
		for(int col=0; col < nCols; col++)
		{
			//look at old and decide what goes into new
			//current just copies old and puts into new

	 *( ((char*) New) + (row * nCols) + col) = *( ((char*) Old) + (row * nCols) + col); //nCol is a whole row
			//this line of code copies the data from the old array to the new array by
			// going into the old array, and going directly to the element that needs to be copied
			// the row is multiplied by how many columns (nCol which is a whole row) there are
			// column to find right column, and the number
			//columns is then added to find the correct column

			// *( ((char*) Old) is  the character pointer to the old array
		}
	}*/

	//maybe calc neighbors is wrong

	for(int r=0; r< nRows; r++ ){
		for(int c= 0; c< nCols; c++){

			//*( ((char*) New) + (r * nCols) + c) = 'o';

			int neighbors = CountNeighbors(r, c, nRows, nCols, (char*) Old); 	//counts the neighbors of the old
			// now we know how many neighbors there are, we can implement the 'rules of life'

			char currChar = *( (char*)Old + (r * nCols) + c); 		//the current character being looked at

			int occupied = (currChar == 'x'); 						//if death condition is being met // if it is alive

			//printf("Letter: %c, Occupied: %d\n", currChar, occupied);


			if(occupied && ((neighbors> 3)|| (neighbors<2))){ 				//death condition
				*( ((char*) New) + (r * nCols) + c) = 'o';						 //in new array, an 'o' would be in that spot //death
			} else if((occupied) && ((neighbors ==3)||(neighbors ==2))){    //survival
				*( ((char*) New) + (r * nCols) + c) = 'x'; 						//in new array, an 'x' would be in that spot //survival
			} else if(!(occupied) && (neighbors == 3)){						//birth
				*( ((char*) New) + (r * nCols) + c) = 'x'; 						//in new array, an 'x' would be in that spot //birth
			} else {
				*( ((char*) New) + (r * nCols) + c) = 'o';
			}

		}
	}

	// this function goes through every row and then checks all of the columns within the row.

}
