#include <stdio.h>

void insertion(int arr[], int a) 
{
    int x, key, y;
    for (x = 1; x < a; x++) 
    {
        key = arr[x];
        y = x - 1;
        while (y >= 0 && arr[y] > key) 
        {
            arr[y + 1] = arr[y];
            y = y - 1;
        }
        arr[y + 1] = key;
    }
}

int main() 
{
    int arr[10];
    int x, a;
    printf("User Enter 10 elements here:\n");
    for (x = 0; x < 10; x++) 
    {
        scanf("%d", &arr[x]);
    }
    a = 10;
    insertion(arr, a);
    printf("Sorted array:\n");
    for (x = 0; x < a; x++) 
    {
        printf("%d ", arr[x]);
    }
    return 0;
}
