#include "stdio.h"
#include "stdlib.h"
#include <malloc.h>
int** MagicSquare(int n){
    // YOUR CODE HERE
    int** arr=malloc(n*sizeof(int*));
    for(int i=0;i<n;i++){
        arr[i]=malloc(n*sizeof(int));
    }
    int j,k;
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			arr[i][j]=0;	
		}
	}
	int i=0;
	j=n/2;
	arr[0][j]=1;
	for(k=2;k<=n*n;k++){
		i=i-1;
		j=j+1;
		if((i<0)&&(j>n-1)){
			i=i+2;
			j=j-1;
		}
		else{
			if(i<0)	i=n-1;
			if(j>n-1) j=0;
		}
		if(arr[i][j]==0)
			arr[i][j]=k;
		else{
			i=i+2;
			j=j-1;
			if(i>n-1)
				i=0;
			arr[i][j]=k;
		}
	}
	return arr;
}
void FreeMagicSquare(int** magicSquare, int n){
    // YOUR CODE HERE
    int i;
    for(i=0;i<n+2;i++){
        free(magicSquare[i]);
    }
    free(magicSquare);
}

int main(){
    int n;
    scanf("%d", &n); // Please input a positive odd number.
    int** magicSquare = MagicSquare(n);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            printf("%4d", magicSquare[i][j]);
        }
        printf("\n");
    }
    FreeMagicSquare(magicSquare, n);
    return 0;
}


