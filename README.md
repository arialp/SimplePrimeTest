
# Simple Prime Test

This C project provides utilities to determine if a number is prime and to find all prime divisors of a given number. The project is designed to handle integers up to `2^63 - 1` (the maximum value for `long long` in C).

It uses a trial division method of primality test to find the smallest prime factor of a number, or all prime factors of a number, if the user wishes so.

This program does have memory leak(s). I'll fix them after I learn using valgrind.

## Features

- **Primality Test**: Check if a given number is prime.
- **Prime Factorization**: Find all prime divisors of a given number.

## Prerequisites

- A C compiler (e.g., `gcc`).
- Standard C library.

## Building the Project

To compile the project, use the following command:

```sh
gcc -g -std=c99 main.c -o main
```

## Usage

Run the compiled executable and follow the on-screen prompts to select an operation:

```sh
.\main
```

### Operations

1. **Primality Test**: Enter a number to check if it is prime.
2. **Prime Factorization**: Enter a number to list its prime factors.
3. **Quit**: Exit the program.

### Example

```sh
Select an operation:
    1) Primality Test
    2) Find all prime divisors of a number
    3) Quit
1
Enter a number to check if it is prime: 29
29 is prime
```

```sh
Select an operation:
    1) Primality Test
    2) Find all prime divisors of a number
    3) Quit
2
Enter a number to list its prime factors: 28
28 = 2*2*7
```

## Functions

### valueInArray

Determines whether a given value exists in an array.

**Input**:

- `long long val`: Value to check.
- `const long long *arr`: Array to check.
- `size_t size`: Size of the array.

**Output**:

- `bool`: `true` if the value exists in the array, `false` otherwise.

### resizeArray

Resizes a dynamic array to a new size.

**Input**:

- `long long *arr`: Array to resize.
- `size_t newSize`: New size of the array.

**Output**:

- `long long *`: Resized array or `NULL` if reallocation fails.

### isPrime

Finds the smallest prime divisor of a given number to determine its primality.

**Input**:

- `long long n`: Number to check.

**Output**:

- `long long`:
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

## License

This project is licensed under the MIT License.

