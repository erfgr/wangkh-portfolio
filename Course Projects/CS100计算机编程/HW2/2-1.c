#include <stdio.h>
#include <stdlib.h>
void FindSecondMaxAndMin(int numbers[], int size, int* secondMax, int* secondMin){
    // YOUR CODE HERE
    //从小到大排序
    int i,j;
    for(i=0;i<size-1;i++){
        for(j=i+1;j<size;j++){
            if(numbers[i]>numbers[j]){
                int temp=numbers[i];
                numbers[i]=numbers[j];
                numbers[j]=temp;
            }
        }
    }
    *secondMax=numbers[size-2];
    *secondMin=numbers[1];
}
#define SIZE 8

int main(){
    int secondMax, secondMin;
    int numbers[SIZE] = {2, 3, 4, 7, 6, 10, 9, 8};
    FindSecondMaxAndMin(numbers, SIZE, &secondMax, &secondMin);
    printf("%d %d\n", secondMax, secondMin);
    return 0;
}

