#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "libEuler.h"

void problem1(unsigned fizz, unsigned buzz, unsigned limit)
{
	unsigned accumulator = 0;
	for (int i=1; i < limit; ++i) {
		if ( i%fizz == 0 || i%buzz == 0 ) accumulator += i;
	}
	printf("Problem 1: The sum of all the multiples of %u or %u below %u is "
	       "%u.\n", fizz, buzz, limit, accumulator);
}

void problem2(bool odd, unsigned limit)
{
	unsigned prev = 0, curr = 1, accumulator = 0;
	for (int i=1; i < limit; ++i) {
		if ( i == prev+curr ) {
			prev = curr;
			curr = i;
			if ( curr%2 == odd ) accumulator += i;
		}
	}
	printf("Problem 2: The sum of the ");
	(odd) ? printf("odd ") : printf("even ");
	printf("fibonacci numbers below %u is %u.\n",limit, accumulator);
}

void problem3(uint_fast64_t number)
{
	printf("Problem 3: The largest prime factor of %llu is %llu.\n",
	       number,greatestPrimeFactor(number) );
}

void problem4(unsigned base, unsigned digits)
{
	printf("Problem 4: The largest ");
	switch (base) {
		case 8:  printf("octal ");         break;
		case 10: printf("decimal ");       break;
		case 16: printf("hexadecimal ");   break;
		default: printf("base-%u ", base); break;
	}
	printf("palindrome made from the product of two %u-digit numbers is ",
	       digits);
	switch (base) {
		case 8:  printf(  "0%o", greatestPalindrome(base,digits) ); break;
		case 16: printf( "0x%X", greatestPalindrome(base,digits) ); break;
		default: printf(   "%d", greatestPalindrome(base,digits) ); break;
	}
	printf(".\n");
}

void problem5(unsigned lowerBound, unsigned upperBound)
{
	printf("Problem 5: The smallest positive number that is evenly divisible "
	       "by all of the numbers from %u to %u is %u.\n",
	       lowerBound,
	       upperBound,
	       leastCommonMultipleFromNtoN(lowerBound, upperBound));
}

void problem6(unsigned limit)
{
	unsigned sumOfSquares = 0;
	unsigned squareOfSums = 0;
	for (int i=1; i <= limit; ++i) sumOfSquares += i*i;
	for (int i=1; i <= limit; ++i) squareOfSums += i;
	squareOfSums *= squareOfSums;
	printf("Problem 6: The difference between the sum of the squares of the "
	       "first %u natural numbers and the square of their sum is %u.\n",
	       limit, squareOfSums-sumOfSquares);
}

void problem7(unsigned limit)
{
	unsigned primes[limit];
	primes[0] = 2;
	primes[1] = 3;
	for (int i=2; i<limit; ++i) {
		primes[i] = primes[i-1]+2;
		for (int j=1; j<i; ++j) {
			if (primes[i]%primes[j]==0) {
				primes[i] += 2;
				j = 0;
			}
		}
	}
	char suffix[3] = "..";
	ordinalSuffix(limit, suffix);
	printf("Problem 7: The %u%s prime number is %u.\n",
	       limit, suffix, primes[limit-1]);
}

void problem8(unsigned window, char *bignum_file_path, int rows, int cols)
{
	FILE* bignum_file = fopen(bignum_file_path, "r");
	if (!bignum_file) {
		fprintf(stderr,
		        "Error: the file \"%s\" could not be opened.",
		        bignum_file_path);
		exit(EXIT_FAILURE);
	}
	char bignum[rows*cols+1];
	for (int i = 0; i < rows; ++i) {
		fgets(&bignum[i*cols],cols+1,bignum_file);
		fgetc(bignum_file); // chew the delimiting linebreak
	}
	fclose(bignum_file);

	unsigned accumulator = 0;
	unsigned length = strlen(bignum);
	for (int i=0; i<=length-window; ++i) {
		unsigned product = 1;
		for (int j=0; j<window; ++j) {
			product *= (bignum[i+j]-'0');
		}
		if (product > accumulator) accumulator = product;
	}
	printf("Problem 8: The greatest product of %u consecutive digits is %u.\n",
	       window, accumulator);
}

void problem9(const unsigned perim)
{
	unsigned a, b, c;
	/* from a near line segment to an equilateral trangle */
	for (c=perim/2; c > perim/3; --c) {
		/* from maximally lopsided to an isoceles triangle */
		for (b=c-1, a=perim-c-b; b > a; --b, ++a) {
			if ((a*a)+(b*b) == (c*c)) { /* match pythagorean triples */
				printf("Problem 9: For the triplet (a=%u,b=%u,c=%u) satisfying"
				       " a\u00B2+b\u00B2=c\u00B2 and a+b+c=%u, a*b*c=%u.\n",
				       a, b, c, perim, a*b*c);
				return; /* we only need one */
			}
		}
	}
	printf("Problem 9: There is no integer triplet (a,b,c) satisfying "
	       "a\u00B2+b\u00B2=c\u00B2 and a+b+c=%u.", perim);
}

void problem11(unsigned window, char *grid_file_path, int grid_height, int grid_width)
{
	FILE *grid_file = fopen(grid_file_path, "r");
	if (!grid_file) {
		fprintf(stderr,
		        "Error: the file \"%s\" could not be opened.",
		        grid_file_path);
		exit(EXIT_FAILURE);
	}
	char charbuffer[3];
	uint_fast8_t grid[grid_height][grid_width]; // values on [0,99]
	for (int row = 0; row < grid_height; ++row) {
		for (int col = 0; col < grid_width; ++col) {
			fgets(charbuffer,3,grid_file);
			grid[row][col] = atoi(charbuffer);
			fgetc(grid_file); // chew the delimiting space
		}
	}
	fclose(grid_file);

	uint_fast32_t accumulator = 0;
	// Case 1: Horizontal
	for (int row = 0; row < grid_height; ++row) {
		for (int col = 0; col < grid_width - window; ++col) {
			uint_fast32_t product = 1;
			for (int i = 0; i < window; ++i) {
				product *= grid[row][col+i];
			}
			if (product > accumulator) accumulator = product;
		}
	}
	// Case 2: Vertical
	for (int row = 0; row < grid_height - window; ++row) {
		for (int col = 0; col < grid_width; ++col) {
			uint_fast32_t product = 1;
			for (int i = 0; i < window; ++i) {
				product *= grid[row+i][col];
			}
			if (product > accumulator) accumulator = product;
		}
	}
	// Case 3: Diagonal NW-SE
	for (int row = 0; row < grid_height - window; ++row) {
		for (int col = 0; col < grid_width - window; ++col) {
			uint_fast32_t product = 1;
			for (int i = 0; i < window; ++i) {
				product *= grid[row+i][col+i];
			}
			if (product > accumulator) accumulator = product;
		}
	}
	// Case 4: Diagonal SW-NE
	for (int row = 0; row < grid_height - window; ++row) {
		for (int col = window-1; col < grid_width; ++col) {
			uint_fast32_t product = 1;
			for (int i = 0; i < window; ++i) {
				product *= grid[row+i][col-i];
			}
			if (product > accumulator) accumulator = product;
		}
	}

	printf("Problem 11: The largest sum of %u colinear integers in the grid "
		   "\"%s\" is %u\n", window, grid_file_path, accumulator);
}

int main()
{
	problem1(3,5,1000);
	problem2(false,4000000);
	problem3(600851475143);
	problem4(10,3);
	problem5(1,20);
	problem6(100);
	problem7(10001);
	problem8(5,"problem8.strings",20,50);
	problem9(1000);
	problem11(4,"problem11.strings",20,20);
}
