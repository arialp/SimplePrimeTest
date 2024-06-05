## A simple and quick primality test. Uses a modified [trial division](https://en.wikipedia.org/wiki/Trial_division) method. 

By checking for divisors of an input number `n` up to its square root, we can find all divisors of said number `n`.

To find the prime divisors, we can use the form `6k + i` for positive `k` and where `i = {0,1,2,3,4,5}`.

We can disregard forms where `i = {0,2,3,4}` because they are divisible by 2 or 3. So we can get away with just `i = {1,5}`.

Note that prime numbers don't follow a general rule, this is already efficient and accurate without diving into more complex algorithms.

_I'm still learning C, I'm sure there are much better algorithms out there._

Sources for the informations: 
[Primality test](https://en.wikipedia.org/wiki/Primality_test#Simple_methods),
[Trial division](https://en.wikipedia.org/wiki/Trial_division)
