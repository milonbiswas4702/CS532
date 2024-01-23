Github link: https://github.com/milonbiswas4702/CS532/blob/main/Lab/Homework/homework01/mbiswas_HW01.c

# Compilation Instructions

gcc -o mbiswas_HW01 mbiswas_HW01.c
./mbiswas_HW01.c

# My File
mbiswas_HW01.c

### my work

C program that is capable of the following functionality:
1. numberTransformer (n)
2. UABNumber()
3. reverseNum(n3)
4. smallerThanIndex()
5. arrayDetails ()
   

1. numberTransformer
The numberTransformer function is a function that takes a positive integer as input and returns a string based on certain conditions. The conditions are as follows:

If the input is a prime number other than 3 or 5, the function returns: "Go Blazers".
If the input is a power of 2, the function returns the result of adding the input and the nearest prime number below it (as a string).
If the sum of the digits of the input is divisible by 3, the function returns: "CS".
If the input is divisible by both 3 and 5, the function returns: "UAB CS 332&532".
Otherwise, the function returns the square of the sum of the digits of the input (as a string).

Functions
numberTransformer(n)
Input: Positive integer n.
Output: String based on the specified conditions.
is_prime(num): Checks if a given number is prime.
nearest_prime_below(num): Finds the nearest prime number below a given number.
sum_of_digits(num): Calculates the sum of the digits of a given number.
These helper functions contribute to the implementation of the main numberTransformer function.

2. UABNumber Function
The UABNumber function is a function that interacts with the user to input an integer (n2). The function then determines whether the entered number is a UABNumber. A UABNumber is defined as a number whose value is equal to the sum of its positive divisors, excluding itself.
The function prompts the user to enter an integer, calculates the sum of its positive divisors (excluding itself), and returns True if the input is a UABNumber, and False otherwise. The function assumes that the entered integer (n2) is equal to or greater than 0.

3. reverseNum Function
The reverseNum function is a Python function designed to reverse the order of the digits of a positive integer (n3). The function returns a new integer with the reversed digits.The function takes a positive integer as input, reverses the order of its digits, and returns the new integer. The function assumes that the input integer (n3) contains only positive integers.

4. smallerThanIndex Function
The smallerThanIndex function is a function designed to operate on an array of 5 integers (numbers). The function checks each number's value against its index and counts the number of integers in the array whose value is smaller than their index. The function returns the total count of such numbers. The function takes an array of 5 integers as input, checks each number's value against its index, counts the number of integers in the array whose value is smaller than their index, and returns the total count

5. arrayDetails Function
The arrayDetails function is a function designed to take an array of 6 integers as input and print another array containing the minimum value, the minimum value’s index, the mean (rounded to the nearest hundredth), the maximum value, and the maximum value’s index. The function takes an array of 6 integers as input, calculates the specified details, and prints another array containing these values.
The function assumes that the input will always be an array of 6 integers.


# Output screenshots/ logs
https://github.com/milonbiswas4702/CS532/blob/main/Lab/hw01_ouputlogs

# References

