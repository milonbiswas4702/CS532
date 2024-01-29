#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// A function to read n strings from the user and store them in a dynamically allocated array
char **read_strings(int N)
{
    char **arr = (char **)malloc(N * sizeof(char *)); // allocate memory for n pointers to strings
    if (arr == NULL)
    {
        printf("Memory allocation failed\n");
        exit(1);
    }
    for (int i = 0; i < N; i++)
    {
        char tempStr[100]; // a temporary buffer to store the input string
        printf("Enter string %d: ", i + 1);
        scanf("%s", tempStr); // read the input string
        int len = strlen(tempStr); // get the length of the input string
        arr[i] = (char *)malloc((len + 1) * sizeof(char)); // allocate memory for the string plus the null terminator
        if (arr[i] == NULL)
        {
            printf("Memory allocation failed\n");
            exit(1);
        }
        strcpy(arr[i], tempStr); // copy the input string to the array
    }
    return arr; // return the array of strings
}


// A function to sort an array of strings using insertion sort algorithm
void sort_strings(char **arr, int N)
{
    for (int i = 1; i < N; i++)
    {
        char *temp = arr[i]; // the current string to be inserted
        int currLoc  = i - 1; // the index of the previous string
        while (currLoc >= 0 && strcmp(arr[currLoc], temp) > 0)   // while the previous string is lexicographically larger than the key
        {
            arr[currLoc + 1] = arr[currLoc]; // move the previous string to the right
            currLoc--; // decrement the index
        }
        arr[currLoc + 1] = temp; // insert the key at the correct position
    }
}


// A function to display an array of strings
void display_strings(char **arr, int N)
{
    printf("The sorted strings are:\n");
    for (int i = 0; i < N; i++)
    {
        printf("%s\n", arr[i]); // print each string
    }
}



int main()
{
    int N; // the number of strings to be sorted
    printf("Enter the number of strings: ");
    scanf("%d", &N);

    char **arr = read_strings(N); // read the strings from the user and store them in a dynamically allocated array
    sort_strings(arr, N); // sort the array of strings using insertion sort algorithm
    display_strings(arr, N); // display the sorted array of strings

    return 0;
}
