#pragma GCC optimize(3)
#include <bits/stdc++.h>

using namespace std;

#define ls u<<1
#define rs u<<1|1
const int N = 1e6 + 10;
struct Node {
    int l, r, v;
} tr[N << 2];
int a[N];
int fa[N], dep[N], sz[N], son[N];
int tim, dfn[N], top[N], w[N];
vector<int> e[N];

inline void build(int u, int l, int r) {
  if (l == r) {
    tr[u] = {l, r, w[r]};
  } else {
    tr[u] = {l, r};
    int mid = l + r >> 1;
    build(ls, l, mid);
    build(rs, mid + 1, r);
    tr[u].v = min(tr[ls].v, tr[rs].v);
  }
}

inline int query(int u, int l, int r) {
  if (tr[u].l >= l && tr[u].r <= r) {
    return tr[u].v;
  } else {
    int mid = tr[u].l + tr[u].r >> 1;
    int res = INT_MAX;
    if (l <= mid) res = min(res, query(ls, l, r));
    if (r > mid) res = min(res, query(rs, l, r));
    return res;
  }
}

inline void dfs1(int u, int f) {
  fa[u] = f;
  dep[u] = dep[f] + 1;
  sz[u] = 1;
  int mx = -1;
  for (auto v : e[u]) {
    if (v == f) continue;
    dfs1(v, u);
    sz[u] += sz[v];
    if (sz[v] > mx) {
      son[u] = v;
      mx = sz[v];
    }
  }
}

inline void dfs2(int u, int t) {
  dfn[u] = ++tim;
  w[tim] = a[u];
  top[u] = t;
  if (!son[u]) return;
  dfs2(son[u], t); // t not u
  for (auto v : e[u]) {
    if (v == son[u] || v == fa[u]) continue;
    dfs2(v, v);
  }
}

int qchain(int x, int y) {
  int res = INT_MAX;
  while (top[x] != top[y]) {
    if (dep[top[x]] < dep[top[y]]) {
      swap(x, y);
    }
    res = min(res, query(1, dfn[top[x]], dfn[x]));
    x = fa[top[x]];
  }
  if (dep[x] < dep[y]) {
    swap(x, y);
  }
  return min(res, query(1, dfn[y], dfn[x]));
}

inline char nc() {
  static char buf[1000000], *p1 = buf, *p2 = buf;
  return p1 == p2 && (p2 = (p1 = buf) + fread (buf, 1, 1000000, stdin), p1 == p2) ? EOF : *p1++;
}

//#define nc getchar
inline void rd(int &sum) {
  char ch = nc();
  int tf = 0;
  sum = 0;
  while((ch < '0' || ch > '9') && (ch != '-')) ch = nc();
  tf = ((ch == '-') && (ch = nc()));
  while(ch >= '0' && ch <= '9') sum = sum * 10+ (ch - 48), ch = nc();
  (tf) && (sum =- sum);
}

inline void print(const char* s){
  for(int i=0; s[i]!='\0'; i++) putchar(s[i]);
}

int main() {
  int n, q;
  rd(n);
  rd(q);
  int mn = INT_MAX;
  for (int i = 1; i <= n; i++) {
    rd(a[i]);
    if (a[i] < mn) {
      mn = a[i];
    }
  }
  for (int i = 1; i <= n - 1; i++) {
    int u, v;
    rd(u);
    rd(v);
    e[u].emplace_back(v);
    e[v].emplace_back(u);
  }
  dfs1(1, 1);
  dfs2(1, 1);
  build(1, 1, n);
  while (q--) {
    int u, v;
    rd(u);
    rd(v);
    print(qchain(u, v) == mn ? "Abigail\n" : "David\n");
  }
}