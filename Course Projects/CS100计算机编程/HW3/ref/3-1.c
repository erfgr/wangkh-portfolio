#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

enum { maxn = 6000 };
char string[maxn];
char stmp[maxn];

/* gets is not supported since C11 */
void get_line(char *restrict buffer) {
  int c = getchar();
  while (c != '\n' && c != EOF) {
    *buffer++ = c;
    c = getchar();
  }
  *buffer = '\0';
}

bool is_palindrome(int l, int r) {
  for (int i = l, j = r; i < j; ++i, --j) {
    while (!isalpha(string[i]) && i < j)
      ++i;
    while (!isalpha(string[j]) && i < j)
      --j;
    if (i >= j)
      break;
    if (tolower(string[i]) != tolower(string[j])) {
      return false;
    }
  }
  return true;
}

int main() {
  get_line(string);
  int m;
  scanf("%d", &m);
  while (m--) {
    int q;
    scanf("%d", &q);
    switch (q) {
      case 0: {
        int l, r;
        scanf("%d%d", &l, &r);
        puts(is_palindrome(l, r) ? "Yes" : "No");
        break;
      }
      case 1: {
        int k;
        scanf("%d", &k);
        getchar();
        string[k] = getchar();
        break;
      }
      case 2: {
        get_line(stmp);
        strcat(string, stmp + 1);
        break;
      }
    }
  }
  return 0;
}
