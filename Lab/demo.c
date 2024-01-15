#include <stdio.h>
int main() 
{
    int given_number;
    printf("Enter number: ");
    scanf("%d", &given_number);

    if (given_number % 2 == 0) 
    {
        printf("The number is an even number\n");
    } 
    else 
    {
        printf("The number is an odd number\n");
    }
    return 0;
}
