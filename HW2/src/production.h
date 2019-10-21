/*
 * production.h
 *
 *  Created on: Nov 3, 2018
 *      Author: student
 */

#ifndef PRODUCTION_H_
#define PRODUCTION_H_
bool production(int argc, char* argv[]);
void PlayOne (unsigned int nr, unsigned int nc, char* Old, char* New);
void printBoard(int nc, int nr, char*p);
int doGenerations(unsigned int nr, unsigned int nc, int given_gens, char* A, char* B, char* C, char print, char pause);
bool checkArrayEquals(int nc, int nr, char* A, char* B);
int CountNeighbors(unsigned int r, unsigned int c, int nRows, int nCols, char* Old);

#endif /* PRODUCTION_H_ */
