#include <stdio.h>
#include <stdlib.h>

void FindSecondMaxAndMin(int numbers[], int size, int* secondMax, int* secondMin)
{
    int max = -10001, min = 10001;
    *secondMax = -10001, *secondMin = 10001;
    for(int i = 0; i < size; i++)
    {
        if(numbers[i] > max){
            *secondMax = max;
            max = numbers[i];
        } else if(numbers[i] > *secondMax){
            *secondMax = numbers[i];
        }

        if(numbers[i] < min){
            *secondMin = min;
            min = numbers[i];
        } else if(numbers[i] < *secondMin){
            *secondMin = numbers[i];
        }
    }
}

int main()
{
    int n;
    scanf("%d", &n);
    int* arr = (int*)malloc(n * sizeof(int));
    for (int i=0; i<n; i++)
        scanf("%d", &arr[i]);
    int secondMax, secondMin;
    FindSecondMaxAndMin(arr, n, &secondMax, &secondMin);
    printf("%d %d\n", secondMax, secondMin);
    return 0;
}