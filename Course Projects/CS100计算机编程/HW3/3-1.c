#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#define MAstr3_SIZE 6000

int main()
{
    char str1[MAstr3_SIZE];
    char str2[MAstr3_SIZE];
    char str3[MAstr3_SIZE];
    char str4[MAstr3_SIZE];
    char str5[MAstr3_SIZE];
    char c;
    char s[MAstr3_SIZE];
    char x[MAstr3_SIZE];
    int l, r, k, i, j,m ,n,p,len,q;  
    gets(str1);
    scanf("%d\n", &m);
    for(int k = 0; k < m ; k++)
    {
        scanf("%d",&n);
        if(n==0)
        {
            scanf("%d %d",&l,&r);
            memset(str5,0,sizeof(str5));
            len=0;
            
            for(i = l; i <= r; i++)
            {
                if(isalpha(str1[i])!=0)
                {
                    str5[len] = str1[i];
                    len++;
                }
            }
            
            
            for(i = 0; i < strlen(str5); i++)
            {
                str5[i] = tolower(str5[i]);
            }
           
            if(len  == 2)
            {
                if(str5[0] == str5[1])
                    printf("Yes\n");
                else
                    printf("No\n");
            }
            else
            {
                for(q = 0; q < len ; q++)
                {
                    if(str5[q] == str5[len - 1 - q])
                        continue;
                    else
                        break;
                }
                if(q == len)
                    printf("Yes\n");
                else
                    printf("No\n");
            }
        }

        if(n==1)
        {
        scanf("%d",&p);
        getchar();
        c=getchar();
        str1[p] = c;
        }
        if(n == 2)
        {
        getchar();
        
        gets(x);
        
        for(int i = 0 ; i < strlen(x) ; i++)
            str1[strlen(str1)] = x[i];
        
        }
    }
    return 0;
}