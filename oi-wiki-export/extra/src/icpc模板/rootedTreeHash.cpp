//μ's forever
#include <bits/stdc++.h>
#define ll long long 
#define N 100005
#define mod 30741842544899069
//#define getchar nc
using namespace std;
inline char nc(){
    static char buf[100000],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;
}
inline int read()
{
    register int x=0,f=1;register char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9')x=(x<<3)+(x<<1)+ch-'0',ch=getchar();
    return x*f;
}
inline void write(register int x)
{
    if(!x)putchar('0');if(x<0)x=-x,putchar('-');
    static int sta[20];register int tot=0;
    while(x)sta[tot++]=x%10,x/=10;
    while(tot)putchar(sta[--tot]+48);
}
static uint64_t splitmix64(uint64_t x) {
  // http://xorshift.di.unimi.it/splitmix64.c
  x += 0x9e3779b97f4a7c15;
  x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
  x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
  return x ^ (x >> 31);
}
int rnd[N];
struct edge{
    int to,nxt;
}e[N<<1];
int head[N],cnt;
void add(int u,int v){
    e[++cnt]=(edge){v,head[u]}; head[u]=cnt;
}
int T,n;
struct node{
    int cnt;
    int val[2];
};
bool operator == (node a,node b){
    return a.cnt==b.cnt&&a.val[0]==b.val[0]&&a.val[1]==b.val[1];
}
int f[N],sz[N];
void init(){
    cnt=0;
    for(int i=1;i<=n;++i) head[i]=0,f[i]=0;
}
void dfs(int x,int fa){
    sz[x]=1;
    for(int i=head[x];i;i=e[i].nxt){
        int v=e[i].to;
        if(v==fa) continue;
        dfs(v,x);
        sz[x]+=sz[v];
        f[x]=max(f[x],sz[v]);
    }
    f[x]=max(f[x],n-sz[x]);
}
ll g(int x,int fa){
    vector<ll> tmp;
    tmp.clear();
    tmp.push_back(rnd[sz[x]]);
    for(int i=head[x];i;i=e[i].nxt){
        int v=e[i].to;
        if(v==fa) continue;
        tmp.push_back(g(v,x));
    }
    sort(tmp.begin(),tmp.end());
    ll res=0;
    for(int i=0;i<(int)tmp.size();++i)
        res=(1ll*res*67+tmp[i])%mod;
    return splitmix64(res);
}
// map<vector<int>,int> id;
// int idc;
// int g2(int x,int fa){
//     vector<int> tmp;
//     for(int i=head[x];i;i=e[i].nxt){
//         int v=e[i].to;
//         if(v==fa) continue;
//         tmp.push_back(g2(v,x));
//     }
//     sort(tmp.begin(),tmp.end());
//     int &v=id[tmp];
//     if(!v) v=++idc;
//     return v;
// }
node gethash(){
    dfs(1,0);
    node res;
    res.cnt=res.val[0]=res.val[1]=0;
    // for(int i=1;i<=n;++i)
    //     if(f[i]<=n/2){
    //         cerr<<i<<endl;
    //         res.val[res.cnt]=g(i,0);
    //         ++res.cnt;
    //     }
    // res.val[0]=g2(1,0);
    res.val[0]=g(1,0);
    sort(res.val,res.val+1);
    return res;
}
int main()
{
    for(int i=1;i<=100000;++i)
        rnd[i]=rand()*(1<<16)+rand();
    T=read();
    while(T--){
        // idc=0;
        // id.clear();
        n=read();
        init();
        for(int i=1;i<n;++i){
            int u=read(),v=read();
            add(u,v),add(v,u);
        }
        node t1=gethash();
        init();
        for(int i=1;i<n;++i){
            int u=read(),v=read();
            add(u,v),add(v,u);
        }
        node t2=gethash();
        if(t1==t2){
            puts("Isomorphism");
        }else{
            puts("No");
        }
    }
    return 0;
}