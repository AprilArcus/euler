#pragma once
#include <stdint.h>
#include <stdbool.h>

// Problem 3
uint_fast64_t leastPrimeFactor(uint_fast64_t n, uint_fast64_t countFrom);
uint_fast64_t greatestPrimeFactor(uint_fast64_t remainder);

// Problem 4
int intPow(int base, unsigned exponent);
bool palindromeInBase(unsigned forward, unsigned base);
int greatestPalindrome(unsigned base, unsigned digits);

// Problem 5
void printUnsignedArray(unsigned* array, size_t size);
void allPrimeFactorsOfN(unsigned remainder, unsigned *factors);
void allPrimeFactorsFromNtoN (unsigned lowerBound,
                              unsigned upperBound,
                              unsigned *totalFactorCount);
unsigned leastCommonMultipleFromNtoN(unsigned lowerBound, unsigned upperBound);

// Probem 7
void ordinalSuffix(unsigned n, char *str);
