#include<bits/stdc++.h>
using namespace std;
struct edge{
    int u,v,w;
    bool operator < (const edge &x)const{return w < x.w;}
};
int main(){
    iso::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, m; cin>>n>>m;
    vector<edge> e;
    for(int i = 1; i <= n; ++i) {
        int x; cin>>x;
        e.push_back((edge){0,i,x});
    }
    while(m--){
        int u,v,w; cin>>u>>v>>w; e.push_back((edge){u,v,w});
    }
    sort(e.begin(), e.end());
    vector<int> fa(n+1); for(int i = 1; i <= n; ++i) fa[i] = i;
    function<int(int)> fnd = [&](int x){return x==fa[x]?x:fa[x] = fnd(fa[x]);};
    long long ans = 0;
    for(auto [u,v,w]:e){
        if(fnd(u)!=fnd(v)){
            ans += w; fa[fnd(u)] = fnd(v);
        }
    }
    cout<<ans<<endl;
    return 0;
}