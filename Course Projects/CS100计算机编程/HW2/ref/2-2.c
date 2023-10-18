#include <stdio.h>
#define MAX(x, y) (((x) > (y)) ? (x) : (y))

int len(int x){
    int length = 0;
    if(x == 0)
        return 1;
    if(x < 0){
        length += 1;
        x = -x;
    }
    while(x > 0){
        x /= 10;
        ++length;
    }
    return length;
}

void printMultiple(int n, char s){
    for(int i = 0; i < n; i++)
        printf("%c", s);
}

void add(int a, int b){
    int c = a + b;
    int len_a = len(a);
    int len_b = len(b);
    int len_c = len(c);
    int max_length = MAX(len_a, MAX(len_b, len_c)) + 2;

    printMultiple(max_length - len_a, ' ');
    printf("%d\n", a);

    printf("+");
    printMultiple(max_length - len_b - 1, ' ');
    printf("%d\n", b);

    printMultiple(max_length, '-');
    printf("\n");

    printMultiple(max_length - len_c, ' ');
    printf("%d\n", c);
}

void subtract(int a, int b){
    int c = a - b;
    int len_a = len(a);
    int len_b = len(b);
    int len_c = len(c);
    int max_length = MAX(len_a, MAX(len_b, len_c)) + 2;

    printMultiple(max_length - len_a, ' ');
    printf("%d\n", a);

    printf("-");
    printMultiple(max_length - len_b - 1, ' ');
    printf("%d\n", b);

    printMultiple(max_length, '-');
    printf("\n");

    printMultiple(max_length - len_c, ' ');
    printf("%d\n", c);
}

void multiply(int a, int b){
    int c = a * b;
    int len_a = len(a);
    int len_b = len(b);
    int len_c = len(c);
    int max_length = MAX(len_a, MAX(len_b, len_c)) + 2;

    printMultiple(max_length - len_a, ' ');
    printf("%d\n", a);

    printf("x");
    printMultiple(max_length - len_b - 1, ' ');
    printf("%d\n", b);

    printMultiple(max_length, '-');
    printf("\n");

    int t1 = b, t2, cnt = 0;
    while(t1 > 0){
        t2 = a * (t1 % 10);
        if(t2 != 0){
            printMultiple(max_length - len(t2) - cnt, ' ');
            printf("%d\n", t2);
        }
        t1 /= 10;
        ++cnt;
    }
    printMultiple(max_length, '-');
    printf("\n");

    printMultiple(max_length - len_c, ' ');
    printf("%d\n", c);
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