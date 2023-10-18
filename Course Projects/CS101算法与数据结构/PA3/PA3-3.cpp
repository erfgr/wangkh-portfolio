#include<bits/stdc++.h>
#define int long long
#define PI 3.1415926
using namespace std;
typedef pair<int,int>vt;
typedef pair<vt,vt>PII;
const int N=2e6+10;
const int M=2*N;
const int mod=1e9+7;
const int INF  = 0x3f3f3f3f3f3f3f3f;

//优先对列
//priority_queue <int,vector<int>,less<int> > q;//递减
//priority_queue <vt,vector<vt>,greater<vt> > q;//递增

struct Node{
    int x,y;
    bool box;
    bool operator<(const Node &a)const
    {
        if(a.x == x)return a.box < box;
        return a.x < x;
    }
}a[N];

multiset<int> st;

//将信息跟空间放在一起排序
//用结构体存储数据

/*将信息和空间放在一起，并指定a为关键值并对其排序，用multiset存储空间的数据
  若要使得尽可能多的信息被保存，则相当于空间被充分利用
  则若指定一个信息x1，那么最适合他放置的地方则是 a值尽量靠近x1，d值同样尽量靠近x1
*/
void solve()
{
    int n,m;
    cin>>n>>m;
    for(int i = 1 ; i <= n ; i++)//读入信息
    {
        int x,y;
        cin>>x>>y;
        a[i].x = x;
        a[i].y = y;
        a[i].box = false;
    }
    for(int i = n + 1 ; i <= m + n; i++)//读入空间数据
    {
        int x,y;
        cin>>x>>y;
        a[i].x = x;
        a[i].y = y;
        a[i].box = true;
    }
    sort(a+1,a+1+n+m);//排序
    int ans=0;
    for(int i = 1 ; i <= n + m; i++)
    {
        if(a[i].box)//如果这个位置是空间，则其插入multiset
        {
            st.insert(a[i].y);
        }
        else//如果当前是信息，则要处理掉这条信息
        {
            if(!st.empty()){//如果不为空
            auto it = st.lower_bound(a[i].y);//找到第一个大于当前所需空间的空间
            if(it!=st.end())//找到的话，ans++，并将已经装了短信的空间移开
            {
                st.erase(it);
                ans++;
            }//没找到的话，就继续循环
            }
        }
    }
    cout<<ans<<endl;
}

signed main()
{
    cin.tie(0);
    cout.tie(0);
    cin.sync_with_stdio(false);
    //Init();
    /*多组案例初始化*/
    //int t;cin>>t;while(t--)
    solve();
}
