# Simple Prime Test

This C project provides utilities to determine if a number is prime and to find all prime divisors of a given number.
The project is designed to handle integers up to `2^64 - 1` (the maximum value for `unsigned long long` in C).

It uses a trial division method of primality test to find the smallest prime factor of a number, or all prime factors of
a number, if the user wishes so.

~~This program does have memory leak(s). I'll fix them after I learn using valgrind.~~ Fixed in 1.2.

This program does compile and run on Linux and Windows.
## Features

- **Primality Test**: Check if a given number is prime.
- **Prime Factorization**: Find all prime divisors of a given number.

## Prerequisites

- A C compiler (e.g., `gcc`).
- Standard C library.

## Building the Project

To compile the project, use the following command:

```sh
gcc -g -std=c99 main.c -o primetest -lm
```

## Usage

Run the compiled executable and follow the on-screen prompts to select an operation:

```sh
.\primetest
```

### Operations

1. **Primality Test**: Enter a number to check if it is prime.
2. **Prime Factorization**: Enter a number to list its prime factors.
3. **Benchmark all functions**: Benchmarks `isPrime` and `findAllDivisors` using a very simple iterative method.
4. **Quit**: Exit the program.

### Example

```sh
Select an operation:
    1) Primality Test
    2) Find all prime divisors of a number
    3) Benchmark all functions
    4) Quit
1
Enter a number to check if it is prime: 29
29 is prime
```

```sh
Select an operation:
    1) Primality Test
    2) Find all prime divisors of a number
    3) Benchmark all functions
    4) Quit
2
Enter a number to list its prime factors: 28
28 = 2*2*7
```

## Functions

### removeNonNumeric

Removes all non numeric characters in a given array.

**Input**:

- `const char *in`: Array to check.
- `size_t size`: Used for creating the return array of the same size as `in`.

**Output**:

- `char *out`: An array with only the numeric elements of `in`, with the same size.

### valueInArray

Determines whether a given value exists in an array.

**Input**:

- `unsigned long long val`: Value to check.
- `const unsigned long long *arr`: Array to check.
- `size_t size`: Size of the array.

**Output**:

- `bool`: `true` if the value exists in the array, `false` otherwise.

### resizeArray

Resizes a dynamic array to a new size.

**Input**:

- `unsigned long long *arr`: Array to resize.
- `size_t newSize`: New size of the array.

**Output**:

- `unsigned long long *tmp`: Resized array or `NULL` if reallocation fails.

### isPrime

Finds the smallest prime divisor of a given number to determine its primality.

**Input**:

- `unsigned long long n`: Number to check.

**Output**:

- `unsigned long long`:
	- `0` if `n < 2`.
	- `1` if `n` is prime.
	- Smallest prime divisor of `n` if it is not prime.

### findPrimeDivisors

Finds all prime divisors of a given number.

**Input**:

- `long long n`: Number to factorize.
- `size_t *returnSize`: Pointer to store the size of the returned array.

**Output**:

- `long long *`: Array of prime divisors. Must be freed after use.

## Changelog
## **1.2**:

- Increased the range from `2^63-1` to `2^64-1` by using an unsigned integer type. This is possible since negative numbers cannot be negative.
- Fixed all memory leaks (hopefully).
  - valguard output after testing all operations:
  - ```
    HEAP SUMMARY:
    in use at exit: 0 bytes in 0 blocks
    total heap usage: 12,600,127 allocs, 12,600,127 frees, 1,270,410,275 bytes allocated
    All heap blocks were freed -- no leaks are possible
    ```
- Added a new function: `removeNonNumeric(char *in, size_t size)`:
  - Removes all non numeric characters in a given char array. And returns a new char array pointer.
  - Returned array must be freed after use.
- Added a very basic and primitive benchmark operation. I might improve this later.
- Increased reliability by adding checks for a valid user input. The program will now:
  - Warn the user if the selection choice is invalid.
  - Remove any non numeric characters from the input for the selected operation.
  - Ignore the negative sign.

## **1.1**: 

- Moved the implementation to its own function named `isPrime`.

- Added new functions:
	- `findPrimeDivisors(long long n, size_t *returnSize)`: 	Finds the prime factors of an integer n, and returns these factors in an array.
	- `resizeArray(long long *arr, size_t newSize)`: 		Resizes a given dynamic array using `realloc`. The new size, **as number of entries**, must be passed to this function.
	- `valueInArray(long long val, long long *arr, size_t size)`: 	Checks if a given value is in an array. This function is simply a way to declutter.
- Massively sped up the entire program. Don't ask how its black magic.
- Massively expanded the range. Previously, an input of 9 decimal digits was the practical limit for the `isPrime` function. This has been extended to 19 decimal digits.

## **1.0**: 
- First commit.

## License

This project is licensed under the MIT License.
