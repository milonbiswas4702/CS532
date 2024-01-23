#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>
#include <stdbool.h>

// Function to Check prime for numberTransformer function
int checkPrime(int p)
{
    int i, isPrime = 1;

    if (p == 0 || p == 1)
    {
        isPrime = 0;
    }
    else
    {
        for (i = 2; i < p; ++i)
        {
            if (p % i == 0)
            {
                isPrime = 0;
                break;
            }
        }
    }

    return isPrime;
}
// Function 1
char *numberTransformer(int num)
{
    int sum = 0, rem, propTwo, propTwo2, divTwo = 1, propThree, sum2 = 0, flag2 = 1, proplast, sumlast = 0, sumlastsq = 0, remlast, nstpm, nstpm2 = 0;
    char str[100];
    char strsum2[5];

    // For property 2
    propTwo = num;
    propTwo2 = num;
    while (propTwo != 1)
    {
        if (propTwo % 2 != 0)
        {
            divTwo = 0;
        }

        propTwo /= 2;
    }
    // For property 3
    propThree = num;
    while (propThree != 0)
    {
        rem = propThree % 10;
        sum = sum + rem;
        propThree = propThree / 10;
    }

    // If n is divisible by both 3 and 5, the function should return: "UAB CS 332&532"
    if (num % 3 == 0 && num % 5 == 0)
        return "UAB CS 332&532\n";
    // If the sum of the digits of n is divisible by 3, the function should return: "CS"
    else if (sum % 3 == 0)
        return "CS\n";
    // If n is a prime number other than 3 or 5, the function should return: "Go Blazers"
    else if (checkPrime(num) == 1 && num != 3 && num != 5)
        return "Go Blazers\n";
    // If n is a power of 2 (e.g., 1, 2, 4, 8, ...), the function should return the result of adding n
    // and the nearest prime number below n
    else if (divTwo)
    {
        for (int j = 2; j < propTwo2; j++)
        {
            if (checkPrime(j) == 1)
            {
                nstpm = j;
                // Finding neares prime number
                if (nstpm > nstpm2)
                {
                    nstpm2 = nstpm;
                }
            }
            sum2 = num + nstpm2;
        }
        sprintf(strsum2, "%d", sum2);
        printf("%s", strsum2);
        return "\n";
    }
    // Otherwise, the function should return the square of the sum of the digits of n
    else
    {
        proplast = num;
        // sum of all the digits
        while (proplast != 0)
        {
            remlast = proplast % 10;
            sumlast = sumlast + remlast;
            proplast = proplast / 10;
        }
        // square of the sum
        sumlastsq = sumlast * sumlast;
        printf("%d", sumlastsq);
        return "\n";
    }
}

// Function 2
bool UABNumber(int n2)
{
    int sumFunc2 = 0;
    // sum of divisors
    for (int i = 1; i < n2; i++)
    {
        if (n2 % i == 0)
        {
            sumFunc2 = sumFunc2 + i;
        }
    }
    // Check if sum eqal to n2
    return (sumFunc2 == n2);
}

// Function 3
int reverseNum(int n3)
{
    int n3rev = 0;
    while (n3 != 0)
    {
        // starting from last digit making it first
        n3rev = (n3rev * 10) + (n3 % 10);
        n3 /= 10;
    }
    return n3rev;
}

// Function 4
int smallerThanIndex(int *numbers, int sz)
{
    int cnt = 0;
    // Loop through the array using a pointer
    for (int *p = numbers; p < numbers + sz; p++)
    {
        // Get the index of the current element by subtracting the base address of the array
        int index = p - numbers;
        if (*p < index)
        {
            // increment count if element smaller than index
            cnt = cnt + 1;
        }
    }
    return cnt;
}

// Function 5
float *arrayDetails(int arr[], int sz5)
{
    float minEle = INT_MAX, maxEle = INT_MIN, minInd, maxInd, sumArr = 0, mean;
    // Memory allocation
    float *arrRes = (float *)malloc(sz5 * sizeof(float));
    // Finding minimum index and minimum
    for (int i = 0; i < sz5; i++)
    {
        if (arr[i] < minEle)
        {
            minEle = arr[i];
            minInd = i;
        }
        // Finding maximum index and maximum
        if (arr[i] > maxEle)
        {
            maxEle = arr[i];
            maxInd = i;
        }
        sumArr = sumArr + arr[i];
    }
    // finding mean
    mean = sumArr / sz5;
    for (int j = 0; j < 6; j++)
    {
        arrRes[0] = (float)sz5;
        arrRes[1] = minEle;
        arrRes[2] = minInd;
        arrRes[3] = mean;
        arrRes[4] = maxEle;
        arrRes[5] = maxInd;
    }

    return arrRes;
}

int main()
{
    int n, op, n2, n3, sz, numbers[100], arr[100], sz5;
    char *ch;
    int func3, func4;
    bool func2;
    float *func5;
    // Switch case taking Option as input that represent different functions
    printf("List of Functions:\n");
    printf("1.numberTransformer()\n2.UABNumber()\n3.reverseNum(n3)\n4.smallerThanIndex()\n5.arrayDetails()\n");
    printf("Enter a number from above list to try out that function: ");
    scanf("%d", &op);
    switch (op)
    {
    case 1:
        // Continue taking input until positive integer
        do
        {
            printf("Enter a positive integer number n: ");
            scanf("%d", &n);
        } while (n < 0);

        ch = numberTransformer(n);
        printf("%s", ch);
        break;
    case 2:
        printf("Enter an Integer n2: ");
        scanf("%d", &n2);
        func2 = UABNumber(n2);
        printf("%s\n", func2 ? "True" : "False");
        break;
    case 3:
        // Continue taking input until positive integer
        do
        {
            /* Positive Integer only */
            printf("Enter a positive Integer n3: ");
            scanf("%d", &n3);
        } while (n3 < 0);
        func3 = reverseNum(n3);
        printf("%d\n", func3);
        break;
    case 4:
        printf("Enter The size of the array: ");
        scanf("%d", &sz);
        printf("Enter Elements of the array numbers: \n");
        for (int i = 0; i < sz; i++)
        {
            printf("element%d: ", i + 1);
            scanf("%d", &numbers[i]);
        }
        func4 = smallerThanIndex(numbers, sz);
        printf("%d\n", func4);
        break;
    case 5:
        printf("Enter The size of the array: ");
        scanf("%d", &sz5);
        printf("Enter Elements of the array arr: \n");
        for (int i = 0; i < sz5; i++)
        {
            
            scanf("%d", &arr[i]);
        }
        func5 = arrayDetails(arr, sz5);
        printf("[");
        printf("%.0f", func5[0]);
        printf(", ");
        printf("%.0f", func5[1]);
        printf(", ");
        printf("%.0f", func5[2]);
        printf(", ");
        printf("%.2f", func5[3]);
        printf(", ");
        printf("%.0f", func5[4]);
        printf(", ");
        printf("%.0f", func5[5]);
        printf("]\n");
        break;
    default:
        printf("Not a valid selection of function number. Enter a number from 1 to 5.");
        break;
    }

    return 0;
}
