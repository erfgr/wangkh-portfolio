#include "stdio.h"
#include "stdlib.h"
#include<malloc.h>
int** MagicSquare(int n){
    // YOUR CODE HERE
    int** arr=malloc(n*sizeof(int*));
    for(int i=0;i<n;i++){
        arr[i]=malloc(n*sizeof(int));
    }
    int a[101][101],i,j,k;
	for(i=0;i<=n;i++){
		for(j=0;j<=n;j++){
			a[i][j]=0;	
		}
	}
	j=n/2+1;
	a[1][j]=1;
	for(k=2;k<=n*n;k++){
		i=i-1;
		j=j+1;
		if((i<1)&&(j>n)){
			i=i+2;
			j=j-1;
		}
		else{
			if(i<1)	i=n;
			if(j>n) j=1;
		}
		if(a[i][j]==0)
			a[i][j]=k;
		else{
			i=i+2;
			j=j-1;
			a[i][j]=k;
		}
	}
	for(i=1;i<=n;i++){
		for(j=1;j<=n;j++){
			arr[i-1][j-1]=a[i][j];
		}
	}
	return arr;
}
void FreeMagicSquare(int** magicSquare, int n){
    // YOUR CODE HERE
    int i;
    for(i=1;i<=n;i++){
        free(magicSquare[i]);
    }
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