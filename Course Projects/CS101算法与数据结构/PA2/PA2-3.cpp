#include <bits/stdc++.h>
#define for0(i,n) for(i=0;i<(n);i++)
#define for1(i,n) for(i=1;i<=(n);i++)
#define forlr(i,l,r) for(i=(l);i<=(r);i++)
using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N=1000005,M=8388615,D=8388607,S=1145141;
int n,m,t,d[N],cp=0,a[N],c[N],ct,q[N];
ll w[N];
ull h[N],g[M],p[N];
struct pir{
	int x;
	unsigned char y;
};
vector<int> v[N];
vector<pir> s[N];
struct node{
	ll x;
	ull h;
	int fa,o;
	bool operator<(const node &nd)const{
		return x<nd.x;
	}
}tem[N<<1];
bool pd(){
	if(n<m) return 1;
	int i,w=min(m,n-m);
	ll x=1;
	for1(i,w){
		x=x*(n-i+1)/i;
		if(x>=t) return 0;
	}
	return 1;
}
void pus(){
	q[ct]=ct;
	int i;
	for(i=ct;i>1;i>>=1){
		if(tem[q[i]].x<=tem[q[i>>1]].x) break;
		swap(q[i],q[i>>1]);
	}
}
void change(){
	int i=1,ls,rs,s;
	ll w=tem[q[1]].x;
	while(i<=ct){
		ls=i<<1;rs=ls|1;
		if(rs<=ct){
			s=tem[q[ls]].x>tem[q[rs]].x?ls:rs;
			if(tem[q[s]].x>w) swap(q[s],q[i]),i=s;
			else break;
		}else{
			if(ls<=ct&&tem[q[ls]].x>w) swap(q[ls],q[i]);
			break;
		}
	}
}
void add(ull x){
	int i=x&D;
	while(g[i]) i=(i+S)&D;
	g[i]=x;
}
bool fin(ull x){
	int i=x&D;
	while(g[i]&&g[i]!=x) i=(i+S)&D;
	return g[i];
}
void ins(int x,bool bx){
	int ss=s[x].size(),y;
	while(c[x]<ss){
		y=s[x][c[x]].x;
		if(!fin(h[x]-p[y-1]+p[y])){
			if(bx) tem[++ct]={w[x]-d[y],h[x]-p[y-1]+p[y],x,s[x][c[x]].y},pus();
			else tem[q[1]]={w[x]-d[y],h[x]-p[y-1]+p[y],x,s[x][c[x]].y},change();
			add(h[x]-p[y-1]+p[y]);
			c[x]++;
			return ;
		}
		c[x]++;
	}
	if(!bx) tem[q[1]]={},change();
}
int main(){
	int i,j,sv,sum,x,o;
	node nd;
	scanf("%d%d%d",&n,&m,&t);
	if(pd()){
		printf("-1\n");
		return 0;
	}
	p[0]=1;
	for1(i,n) scanf("%d",&a[i]),p[i]=p[i-1]*3;
	sort(a+1,a+n+1,[](int xx,int yy){return xx>yy;});
	for1(i,m) w[1]+=a[i],h[1]+=p[i];
	forlr(i,2,n) d[i]=a[i-1]-a[i];
	v[1].push_back(m+1);
	v[1].push_back(n-m+1);
	tem[++ct]={w[1],h[1],0,0};
	pus();
	for1(j,t){
		nd=tem[q[1]];
		vector<int> &V=v[++cp];
		if(j!=1){
			V=v[nd.fa];w[cp]=nd.x;o=nd.o;
			h[cp]=nd.h;
			if(V[o]==1){
				if(V[o-1]==1){
					V[o-2]++;V[o+1]++;
					V.erase(V.begin()+o);
					V.erase(V.begin()+o-1);
				}else V[o-1]--,V[o+1]++;
			}else{
				if(V[o-1]==1) V[o-2]++,V[o]--;
				else{
					V[o-1]--;V[o]--;
					V.insert(V.begin()+o,1);
					V.insert(V.begin()+o+1,1);
				}
			}
		}
		sv=V.size();sum=0;
		for(i=0;i<sv;i+=2){
			x=sum+V[i];
			if(x>1&&x<=n) s[cp].push_back({x,(unsigned char)(i+1)});
			sum+=V[i]+V[i+1];
		}
		sort(s[cp].begin(),s[cp].end(),[](const pir &px,const pir &py){return d[px.x]<d[py.x];});
		ins(cp,1);ins(nd.fa,0);
	}
	printf("%lld\n",nd.x);
	return 0;
}

