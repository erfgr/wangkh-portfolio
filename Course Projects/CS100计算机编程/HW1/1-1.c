#include<stdio.h>
int main()
{
    int a,b,c; // Store the number of students in classes A, B, and C.
    int max; // Store the maximum number of students in a class.
    printf("How many students are in classes A, B, and C, respectively?\n");
    scanf("%d %d %d", &a, &b, &c);

    if(a >= b && a >= c)
        {
            max = a;
        printf("Class A has the most students, ");
        }
    else 
        if(b > a && b >= c)
        {
            max = b;
        printf("Class B has the most students, ");
        }
    else 
        if(c > a && c > b)
        {
            max = c;
        printf("Class C has the most students, ");
        }
    
    int total = a + b + c;
    // Calculate the average number of students in all three classes.
    float average = (float)total / 2;
    // A class can accept at most half of all students. 
    if(max>average)
        {printf("and is overly enrolled!\n");}
    else
        if(max==average)
        {printf("and is full!\n");}
        if(max<average)
        {printf("and still has open seats!\n");}
        
        

    return 0;
}
