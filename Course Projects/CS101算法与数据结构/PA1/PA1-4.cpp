#include <bits/stdc++.h>
using namespace std;
const int N = 5e6 + 10;
int n, k, a[N];

signed main() {
 cin.tie(0) -> ios::sync_with_stdio(false);

 int n, k;
 cin >> n >> k;
 for (int i = 1; i <= n; i++) cin >> a[i];
 for (int i = n; i >= 1; i--) {
  if (a[i] > k) continue;
  else if (a[i] < k) k--;
  else {
   cout << i << endl;
   break;
  }
 }
 return 0;
}