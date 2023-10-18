#include<stdio.h> 
int main(){
	int n,k;
	scanf("%d %d",&n,&k);
	int ret[n];
	scanf("%d",&ret[0]);
	int l=0,r=1;
	n--;
	while(n--){
		if(r-l == k) {
			printf("%d ",ret[l++]);
		}
		scanf("%d",&ret[r++]);
		if(r-l>=3 && ret[r-1] == ret[r-2] && ret[r-1] == ret[r-3]) {
			r-=3;
		}
	}
	while(l<r){
		printf("%d ",ret[l++]);
	}
	return 0;
} 
