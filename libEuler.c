#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "libEuler.h"

//Problem 3

uint_fast64_t leastPrimeFactor(uint_fast64_t n, uint_fast64_t countFrom)
{
	assert( n >= 2 );
	assert( countFrom >= 2 );
	// factor by two
	if (n%2 == 0) return 2;
	/* factor by odd numbers up to √𝑛

	 “[T]he smallest prime factor [of 𝑛] is less than or equal to √𝑛, unless 𝑛
	   is prime. […] Suppose 𝑛 = 𝑎𝑏 and 𝑎 is the smallest prime factor of 𝑛,
	   and 𝑛 is not prime. Since 𝑛 is not prime, we have 𝑏 ≠ 1. Since 𝑎 is the
	   smallest prime factor of 𝑛, we have 𝑎 ≤ 𝑏. If 𝑎 were bigger than √𝑛,
	   then 𝑏 would also be bigger than √𝑛, so 𝑎𝑏 would be bigger than (√𝑛)(√𝑛).
	   But 𝑎𝑏 = 𝑛.”

	  ~Michael Hardy on http://math.stackexchange.com/a/102760, 26 Jan 2012 */
	if (countFrom%2 == 0) ++countFrom; // sanitize input
	for (uint_fast64_t i=countFrom; i*i <= n; i+=2) {
		if (n%i==0) return i;
	}
	// n is prime
	return n;
}
uint_fast64_t greatestPrimeFactor(uint_fast64_t remainder)
{
	uint_fast64_t lastFactor = 2;
	while (remainder > 1) {
		lastFactor = leastPrimeFactor(remainder, lastFactor);
		remainder /= lastFactor;
	}
	return lastFactor;
}

// Problem 4

int intPow(int base, unsigned exponent)
{
	// special cases
	if      (exponent == 0) return 1;    // 0^0 = 1
	else if (base == 0)     return 0;    // 0^e = 0
	else if (exponent == 1) return base; // b^1 = b
	// exponentiation by recursive squaring
	int root = intPow(base, exponent/2);
	if (exponent%2 == 0) return root*root;
	else return base*root*root;
}
bool palindromeInBase(unsigned forward, unsigned base)
{
	assert(base >= 2);
	unsigned temp = forward, reverse = 0;
	while (temp > 0) {
		reverse *= base;
		reverse += temp%base;
		temp /= base;
	}
	return (forward == reverse);
}
int greatestPalindrome(unsigned base, unsigned digits)
{
	int upperBound = intPow(base,digits)-1;
	int lowerBound = intPow(base,digits-1);
	unsigned greatestPalindrome = 0;
	for (int x = upperBound; x >= lowerBound; --x) {
		for (int y = upperBound; y >= x; --y) {
			if (palindromeInBase(x*y, base) && x*y > greatestPalindrome) {
				greatestPalindrome = x*y;
			}
		}
	}
	return greatestPalindrome;
}

// Problem 5

// Debugging function
// Call like this: printUnsignedArray(array, sizeof(array));
void printUnsignedArray(unsigned* array, size_t size)
{
	unsigned elementsInArray = size/sizeof(array[0]);
	for (int i=0; i < elementsInArray; ++i) printf("[%u]",array[i]);
	printf ("\n");
}
void allPrimeFactorsOfN(unsigned remainder, unsigned* factors)
{
	unsigned lastFactor = 2;
	// 0 and 1 bypass this block and won't trigger leastPrimeFactor's assert()
	while (remainder >= 2) {
		lastFactor = leastPrimeFactor(remainder, lastFactor);
		remainder /= lastFactor;
		++factors[lastFactor];
	}
}
void allPrimeFactorsFromNtoN (unsigned lowerBound,
	                          unsigned upperBound,
	                          unsigned *totalFactorCount)
{
	assert(lowerBound < upperBound);
	for (int j=lowerBound; j <= upperBound; ++j) {
		// Allocating on the stack. Would this benefit from wider scope?
		unsigned thisFactorCount[upperBound+1];
		/* Initialize only the cells we'll use. Since 0 and 1 are not primes,
		   we don't care about thisFactorCount[0] and thisFactorCount[1], and
		   we don't need to count past j when we loop. */
		for (int i=2; i <= j; ++i) thisFactorCount[i] = 0;
		allPrimeFactorsOfN(j, thisFactorCount);
		for (int i=2; i <= j; ++i) {
			if (totalFactorCount[i] < thisFactorCount[i]) {
				totalFactorCount[i] = thisFactorCount[i];
			}
		}
	}
}
unsigned leastCommonMultipleFromNtoN(unsigned lowerBound, unsigned upperBound)
{
	unsigned totalFactorCount[upperBound+1];                     // alloc
	for (int i=2; i <= upperBound; ++i) totalFactorCount[i] = 0; // init
	allPrimeFactorsFromNtoN(lowerBound,upperBound,totalFactorCount);
	unsigned leastCommonMultiple = 1;     // multiplicative identity
	for (int i=2; i <= upperBound; ++i) { // ignoring non-primes 0 and 1
		leastCommonMultiple *= intPow(i,totalFactorCount[i]);
	}
	return leastCommonMultiple;
}

// Problem 7

void ordinalSuffix(unsigned n, char *str)
{
	assert(strlen(str) >= 2);
	switch (n%10) {
		case 1:  strcpy(str,"st"); break;
		case 2:  strcpy(str,"nd"); break;
		case 3:  strcpy(str,"rd"); break;
		default: strcpy(str,"th"); break;
	}
}
