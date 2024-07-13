#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

/*
 * Determines whether a given value exists in a given array.
 *
 * Input:
 * long val: Value in question,
 * long arr: The array to check for the value,
 * size_t size: The size of the given array, calculate it before
 * passing using `sizeof(arr)/sizeof(arr[0])`
 *
 * Output:
 * bool: true, if val exists in arr, false otherwise.
 * */
static inline bool
valueInArray(long long val, const long long *arr, size_t size){
	for(size_t i = 0; i < size; i++){
		if(arr[i] == val) return true;
	}
	return false;
}

/*
 * Resizes a dynamic array to a new size.
 *
 * Input:
 * long* arr: The array that will be resized.
 * size_t newSize: The size of the new array.
 *
 * Output:
 * long* tmp: The new, resized array.
 * */
static inline long long *resizeArray(long long *arr, size_t newSize){
	long long *tmp = realloc(arr, newSize * sizeof(long long));
	if(!tmp){
		free(arr); // Free the old memory if realloc fails
		return NULL;
	}
	return tmp;
}

/*
 * Finds the smallest prime divisor of a given number to determine
 * whether it is prime or not.
 *
 * Input must be 9 digits or smaller.
 *
 * Input:
 * long integer: n
 *
 * Output
 * int:
 * 0, if n < 2,
 * 1, if n == 2 or n == 3,
 * 2, if n is divisible by 2,
 * 3, if n is divisible by 3,
 * else, smallest prime divisor of n.
 * */
static long long isPrime(long long n){
	/*
	 * smallPrimes and size are used for quickly returning for small
	 * primes
	 * */
	const long long smallPrimes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23};
	const size_t size = sizeof(smallPrimes) / sizeof(smallPrimes[0]);
	
	/*
	 * The first few conditionals are there to quickly return from
	 * small primes and invalid inputs.
	 * */
	if(valueInArray(n, smallPrimes, size)) return 1;
	if(n < 2) return 0;
	if(n % 2 == 0) return 2;
	if(n % 3 == 0) return 3;
	
	/*
	 * Taking the square root of n in order to cut computation time
	 * in half.
	 *
	 * Since the divisor pairs that are less than sqrt(n) are the
	 * same as divisor pairs greater than sqrt(n) reversed.
	 *
	 * Check the wikipedia page for a detailed explanation.
	 * https://en.wikipedia.org/wiki/Primality_test
	 * */
	long long floor_sqrt_n = (long long)sqrt(n);
	
	/*
	 * This loop implements the primality test method.
	 *
	 * This loop only runs when `n >= 25` since earlier cases are
	 * already handled by the if statements.
	 *
	 * It checks divisibility by 5,7,11,13,17,19,... and so on until
	 * the counter `i` exceeds sqrt(n), or n is divisible by a prime
	 * number.
	 * */
	for(long long i = 5; i <= floor_sqrt_n; i += 6){
		if(n % i == 0) return i;
		if(n % (i + 2) == 0) return i + 2;
	}
	
	/*
	 * If the function reached this point, it must be that n is a
	 * prime number.
	 * */
	return 1;
}

/*
 * Finds all prime divisors of a given number.
 *
 * The returned array must be freed after use.
 *
 * Input: long integer: n
 *
 * Output:
 * int[] *divisors: Pointer to a dynamic array consisting of every
 * prime divisor of n. If n is prime, it is `[1,n]`.
 * */
static long long *findPrimeDivisors(long long n, size_t *returnSize){
	long long *divisors;
	long long divisor = 1;
	long long num = n;
	int index = 0;
	size_t currentSize = 1;
	/*
	 * Starting with a dynamic array with size 1.
	 * If n happens to be a prime number, the function does not have
	 * to resize the array.
	 * This array will be resized if n is not a prime number.
	 * */
	divisors = malloc(currentSize * sizeof(long));
	if(!divisors) return NULL;
	
	/*
	 * isPrime function is called to exit early or continue.
	 *
	 * A prime number has no prime divisors except itself.
	 * */
	if(isPrime(n) == 1){
		divisors[0] = n;
		*returnSize = 1;
		return divisors;
	}
	
	/*
	 * This loop determines the smallest prime divisor of n, then it
	 * determines the next smallest by dividing n with the smallest
	 * divisor found.
	 *
	 * This process continues until isPrime returns a 1, in that case
	 * this means that we have found all prime divisors of n.
	 *
	 * Before exiting the loop, we add n itself to the divisors array.
	 * */
	for(; divisor <= n; index++){
		divisor = isPrime(num);
		if(index >= currentSize){
			currentSize *= 2;
			divisors = resizeArray(divisors, currentSize);
			if(!divisors) return NULL;
		}
		if(divisor == 1){
			divisors[index] = num;
			break;
		}
		divisors[index] = divisor;
		num /= divisor;
	}
	
	divisors = resizeArray(divisors, index + 1);
	*returnSize = index + 1;
	return divisors;
}

int main(void){
	long long n;
	long long result;
	long long *divisors;
	int select;
	size_t size;
	do{
		n = 0;
		select = 0;
		
		printf("\n%s\n", "Select an operation:");
		puts("\t1) Primality Test");
		puts("\t2) Find all prime divisors of a number");
		puts("\t3) Quit");
		scanf("%d", &select);
		
		switch(select){
			case 1:
				printf("\n%s", "Enter a number to check if it is prime:");
				scanf("%lld", &n);
				result = isPrime(n);
				switch(result){
					case 0: printf("%lld is not prime, less than 2\n", n);
						break;
					case 2: printf("%lld is not prime, divided by 2\n", n);
						break;
					case 3: printf("%lld is not prime, divided by 3\n", n);
						break;
					case 1: printf("%lld is prime\n", n);
						break;
					default:
						printf("%lld is not prime, divided by %lld\n", n, result);
						break;
				}
				break;
			case 2:
				printf("\n%s", "Enter a number to list its prime factors: ");
				scanf("%lld", &n);
				divisors = findPrimeDivisors(n, &size);
				printf("%lld = ", n);
				for(size_t i = 0; i < size; i++){
					printf("%lld", divisors[i]);
					if(i < size - 1){
						printf("%s", "*");
					}
				}
				printf("\n");
				free(divisors);
				break;
			case 3: puts("Exiting.");
				select = -1;
				break;
			default: puts("Invalid selection!");
				select = 0;
				break;
		}
	} while(select != -1);
	return 0;
}
