#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <ctype.h>

/*
 * Removes all non numeric characters from a given char array.
 *
 * Input: char *in: Pointer to char array with non numeric characters.
 *
 * Output: char *out: Pointer to a char array without non numeric
 * characters created from '*in'.
 * */
static inline char *removeNonNumeric(const char *in, size_t size){
	unsigned long i = 0;
	unsigned long j = 0;
	char *out = malloc(size);
	char c;
	
	if(out == NULL){
		return NULL;
	}
	
	while((c = in[i++]) != '\0'){
		if(isdigit(c)){
			out[j++] = c;
		}
	}
	out[j] = '\0';
	return out;
}

/*
 * Determines whether a given value exists in a given array.
 *
 * Input:
 * unsigned long long val: Value in question,
 * unsigned long long *arr: Pointer to the array to check for the
 * value,
 * size_t size: The size of the given array, calculate it before
 * passing using `sizeof(arr)/sizeof(arr[0])`
 *
 * Output:
 * bool: true, if val exists in arr, false otherwise.
 * */
static inline bool valueInArray(unsigned long long val,
																const unsigned long long *arr,
																size_t size){
	for(size_t i = 0; i < size; i++){
		if(arr[i] == val) return true;
	}
	return false;
}

/*
 * Resizes a dynamic array to a new size.
 *
 * Input:
 * unsigned long long *arr: Pointer to the array that will be resized.
 * size_t newSize: The size of the new array.
 *
 * Output:
 * unsigned long long *tmp: Pointer to the new, resized array.
 * */
static inline unsigned long long *
resizeArray(unsigned long long *arr, size_t newSize){
	unsigned long long *tmp;
	
	tmp = realloc(arr, newSize * sizeof(long long));
	if(!tmp){
		free(tmp);
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
 * unsigned long long n: The number to be checked.
 *
 * Output
 * unsigned long long:
 * 0, if n < 2,
 * 1, if n == 2 or n == 3,
 * 2, if n is divisible by 2,
 * 3, if n is divisible by 3,
 * else, smallest prime divisor of n.
 * */
static unsigned long long isPrime(const unsigned long long n){
	unsigned long long floor_sqrt_num;
	unsigned long long num = n;
	const unsigned long long
			smallPrimes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23};
	const size_t size = sizeof(smallPrimes) / sizeof(smallPrimes[0]);
	
	/*
	 * The first few conditionals are there to quickly return from
	 * small primes and invalid inputs.
	 * */
	if(valueInArray(num, smallPrimes, size)) return 1;
	if(num < 2) return 0;
	if(num % 2 == 0) return 2;
	if(num % 3 == 0) return 3;
	
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
	floor_sqrt_num = sqrt(num); // NOLINT(*-narrowing-conversions)
	
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
	for(long long i = 5; i <= floor_sqrt_num; i += 6){
		if(num % i == 0) return i;
		if(num % (i + 2) == 0) return i + 2;
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
 * Input:
 * unsigned long long n: The number to be factorized.
 * size_t *returnSize: A pointer that is used for printing the
 * divisors array.
 *
 * Output:
 * unsigned long long *divisors: Pointer to a dynamic array
 * consisting of every prime divisor of n. If n is prime, it is
 * `[n]`.
 * */
static unsigned long long *
findPrimeDivisors(const unsigned long long n, size_t *returnSize){
	unsigned long long *divisors;
	unsigned long long divisor;
	unsigned long long num = n;
	int index = 0;
	size_t currentSize = 1;
	
	/*
	 * Starting with a dynamic array with size 1.
	 * If n happens to be a prime number, the function does not have
	 * to resize the array.
	 * This array will be resized if n is not a prime number.
	 * */
	divisors = malloc(currentSize * sizeof(long long));
	if(!divisors){
		free(divisors);
		return NULL;
	}
	
	/*
	 * isPrime function is called to exit early or continue.
	 *
	 * A prime number and '1' have no prime divisors.
	 * */
	divisor = isPrime(num);
	if(divisor == 0 || divisor == 1){
		divisors[0] = num;
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
	for(; divisor <= num; index++){
		divisor = isPrime(num);
		if(index >= currentSize){
			currentSize *= 2;
			
			divisors = resizeArray(divisors, currentSize);
			
			if(!divisors){
				free(divisors);
				return NULL;
			}
		}
		if(divisor == 1){
			divisors[index] = num;
			break;
		}
		divisors[index] = divisor;
		num /= divisor;
	}
	
	divisors = resizeArray(divisors, currentSize);
	*returnSize = index + 1;
	return divisors;
}

int main(void){
	char buf[27];
	char *outBuf;
	char *ptr;
	unsigned long long n;
	unsigned long long result;
	unsigned long long *divisors;
	double sum;
	int ch;
	int select;
	size_t size;
	do{
		printf("\n%s\n", "Select an operation:");
		puts("\t1) Primality Test");
		puts("\t2) Find all prime divisors of a number");
		puts("\t3) Benchmark all functions");
		puts("\t4) Quit");
		
		fflush(stdin);
		
		ch = getchar();
		select = (isdigit(ch) > 0) ? ch - '0' : -1;

		// EAT '\n' YUMMY!
		select = (getchar() == '\n') ? select : -2;
		if(select == -2){
			while (getchar() != '\n') continue;
		}
		
		switch(select){
			case 1:
				printf("\n%s", "Enter a number to check if it is prime:");
				if(!fgets(buf, sizeof(buf), stdin)){
					fprintf(stderr, "fgets failed\n");
					return 1;
				}
				
				outBuf = removeNonNumeric(buf, sizeof(buf));
				if(outBuf == NULL){
					fprintf(stderr, "Memory allocation failed\n");
					free(outBuf);
					return 1;
				}
				
				if(outBuf[0] == '\0'){
					fprintf(stderr, "Invalid input\n");
					free(outBuf);
					break;
				}
				
				n = strtoull(outBuf, &ptr, 10);
				free(outBuf);
				
				result = isPrime(n);
				switch(result){
					case 0: printf("%llu is not prime, less than 2\n", n);
						break;
					case 2: printf("%llu is not prime, divided by 2\n", n);
						break;
					case 3: printf("%llu is not prime, divided by 3\n", n);
						break;
					case 1: printf("%llu is prime\n", n);
						break;
					default:
						printf("%llu is not prime, divided by %llu\n", n, result);
						break;
				}
				break;
			
			case 2:
				printf("\n%s", "Enter a number to list its prime factors: ");
				if(!fgets(buf, sizeof(buf), stdin)){
					fprintf(stderr, "fgets failed\n");
					return 1;
				}
				
				outBuf = removeNonNumeric(buf, sizeof(buf));
				if(outBuf == NULL){
					fprintf(stderr, "Memory allocation failed\n");
					free(outBuf);
					return 1;
				}
				
				if(outBuf[0] == '\0'){
					fprintf(stderr, "Invalid input\n");
					free(outBuf);
					break;
				}
				
				n = strtoull(outBuf, &ptr, 10);
				free(outBuf);
				
				divisors = findPrimeDivisors(n, &size);
				printf("%llu = ", n);
				for(size_t i = 0; i < size; i++){
					printf("%llu", divisors[i]);
					if(i < size - 1){
						printf("%s", "*");
					}
				}
				printf("\n");
				free(divisors);
				break;
			
			case 3: sum = 0;
				unsigned long long samples[] =
						{0, 1, 2, 3, 5, 10, 100, 1000, 10000, 100000, 1000000,
						 10000000, 100000000, 1000000000, 10000000000,
						 100000000000, 1000000000000, 10000000000000,
						 100000000000000, 1000000000000000, 10000000000000000,
						 100000000000000000, 1000000000000000000,
						 10000000000000000000U};
				size_t sample_size = sizeof(samples) / sizeof(samples[0]);
				
				/*--------------TESTING isPrime()--------------*/
				for(int i = 0; i <= 19; i++){
					// Largest i digit number
					n = (unsigned long long)(pow(10, i) - 1);
					
					clock_t t = clock();
					isPrime(n);
					t = clock() - t;
					
					double time_taken = ((double)t) / CLOCKS_PER_SEC;
					sum += time_taken;
				}
				printf("isPrime() with every largest number from 1 - 19 "
							 "digits took %.6f seconds.\n", sum);
				
				/*--------------------TEST2--------------------*/
				sum = 0;
				for(size_t i = 0; i < sample_size; i++){
					n = samples[i];
					double local_sum = 0;
					int runs = 100000; // Number of runs for averaging
					
					for(int j = 0; j < runs; j++){
						clock_t t = clock();
						isPrime(n);
						t = clock() - t;
						
						double time_taken = ((double)t) / CLOCKS_PER_SEC;
						local_sum += time_taken;
					}
					sum += local_sum / runs;
				}
				printf("isPrime() with representative samples took %.6f "
							 "seconds.\n", sum);
				/*------------END TESTING isPrime()------------*/
				
				/*---------TESTING findPrimeDivisors()---------*/
				sum = 0;
				for(int i = 1; i <= 19; i++){
					// Largest i digit number
					n = (unsigned long long)(pow(10, i) - 1);
					
					clock_t t = clock();
					divisors = findPrimeDivisors(n, &size);
					t = clock() - t;
					free(divisors);
					
					double time_taken = ((double)t) / CLOCKS_PER_SEC;
					sum += time_taken;
				}
				printf("findPrimeDivisors() with every largest number from "
							 "1 - 19 digits took %.6f seconds.\n", sum);
				
				/*--------------------TEST2--------------------*/
				sum = 0;
				for(size_t i = 0; i < sample_size; i++){
					n = samples[i];
					double local_sum = 0;
					int runs = 100000;
					
					for(int j = 0; j < runs; j++){
						clock_t t = clock();
						divisors = findPrimeDivisors(n, &size);
						t = clock() - t;
						free(divisors);
						
						double time_taken = ((double)t) / CLOCKS_PER_SEC;
						local_sum += time_taken;
					}
					sum += local_sum / runs;
				}
				printf("findPrimeDivisors() with representative samples "
							 "took %.6f seconds.\n", sum);
				/*-------END TESTING findPrimeDivisors()-------*/
				break;
			
			case 4: puts("Exiting.");
				select = -1;
				break;
			
			default: puts("Invalid selection!");
				select = 0;
				break;
		}
	} while(select != -1);
	return 0;
}
