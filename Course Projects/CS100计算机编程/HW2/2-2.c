#include <stdio.h>
void add(int a, int b){
    // YOUR CODE HERE
    if(a+b<10){
    printf("%3d\n", a);
    printf("+%2d\n", b);
    printf("---\n");
    printf("%3d\n", a+b);}
    else if(a+b>=10&&a+b<100){
    printf("%4d\n", a);
    printf("+%3d\n", b);
    printf("----\n");
    printf("%4d\n", a+b);}
    else if(a+b>=100&&a+b<1000){
    printf("%5d\n", a);
    printf("+%4d\n", b);
    printf("-----\n");
    printf("%5d\n", a+b);}
    else if(a+b>=1000&&a+b<10000){
    printf("%6d\n", a);
    printf("+%5d\n", b);
    printf("------\n");
    printf("%6d\n", a+b);}
    else if(a+b>=10000&&a+b<100000){
    printf("%7d\n", a);
    printf("+%6d\n", b);
    printf("-------\n");
    printf("%7d\n", a+b);}
    else if(a+b>=100000&&a+b<1000000){
    printf("%8d\n", a);
    printf("+%7d\n", b);
    printf("--------\n");
    printf("%8d\n", a+b);}
    else if(a+b>=1000000&&a+b<10000000){
    printf("%9d\n", a);
    printf("+%8d\n", b);
    printf("---------\n");
    printf("%9d\n", a+b);}
    else if(a+b>=10000000&&a+b<100000000){
    printf("%10d\n", a);
    printf("+%9d\n", b);
    printf("----------\n");
    printf("%10d\n", a+b);}
    else if(a+b>=100000000&&a+b<1000000000){
    printf("%11d\n", a);
    printf("+%10d\n", b);
    printf("-----------\n");
    printf("%11d\n", a+b);}
}


void subtract(int a, int b){
    // YOUR CODE HERE
    int a_len=0,b_len=0,len=0,a1=a,b1=b,a2=a,b2=b,d1=a1-b1,d2=a2-b2;
    while(a>0){
        a_len++;
        a=a/10;
    }
    while(b>0){
        b_len++;
        b=b/10;
    }
    while(d1!=0){
        len++;
        d1=d1/10;
    }
    if(a2-b2<0){
        len+=1; 
    }
    else{
        len+=0;
    }
    if((a_len>=b_len&&b_len>=len)||(a_len>=len&&len>=b_len)){
        printf("%*d\n",a_len+2,a2);
        printf("-%*d\n",a_len+1,b2);
        for(int i=0;i<a_len+1;i++){
            printf("-");
        }
        printf("-\n");
        printf("%*d\n",a_len+2,d2);
    }
    else if((b_len>=a_len&&a_len>=len)||(b_len>=len&&len>=a_len)){
        printf("%*d\n",b_len+2,a2);
        printf("-%*d\n",b_len+1,b2);
        for(int i=0;i<b_len+1;i++){
            printf("-");
        }
        printf("-\n");
        printf("%*d\n",b_len+2,d2);
    }
    else if((len>=a_len&&a_len>=b_len)||(len>=b_len&&b_len>=a_len)){
        printf("%*d\n",len+2,a2);
        printf("-%*d\n",len+1,b2);
        for(int i=0;i<len+1;i++){
            printf("-");
        }
        printf("-\n");
        printf("%*d\n",len+2,d2);
    }
}

void multiply(int a, int b){
    // YOUR CODE HERE
    int b_len=0,len=0,a1=a,b1=b,a2=a,b2=b,a3=a,b3=b,d1=a1*b1,d2=a2*b2,d3=a3*b3,d4=0,p=0,p1=0,p_len=0;;
    while (d1!=0) {
        len++;
        d1=d1/10;
    }
    while(b>0){
        b_len++;
        b=b/10;
    }
    printf("%*d\n",len+2,a2);
    printf("x%*d\n",len+1,b2);
    for(int i=0;i<len+1;i++){
        printf("-");
    }
    printf("-\n");
    for(int i=0;i<b_len;i++){
        d4=b2%10;
        b2=(b2-b2%10)/10;
        p=d4*a;
        p1=p;
        while(p>0){
            p_len++;
            p=p/10;
            }
        if(p1>0){
            printf("%*d\n",len+2-i,p1);
        }
        else{continue;}
        
    }
    for(int i=0;i<len+1;i++){
        printf("-");
    }
    printf("-\n");
    printf("%*d\n",len+2,d3);
}

int main(){
    int a, b;
    char op;
    scanf("%d %c %d", &a, &op, &b);
    switch (op) {
        case '+':
            add(a, b);
            break;
        case '-':
            subtract(a, b);
            break;
        case 'x':
            multiply(a, b);
            break;
        default:
            printf("Sample input: 12 + 34");
    }
    return 0;
}