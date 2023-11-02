//μ's forever
#include <bits/stdc++.h>
#define mod 998244353
#define N 100005
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
int n,m,U[N],V[N],x[N];
int deg[N],id[N],tg[N];
vector<int> e[N];
int ans;
int main()
{
    n=read(),m=read();
    for(int i=1;i<=n;++i) x[i]=read();
    for(int i=1;i<=m;++i){
        U[i]=read(),V[i]=read();
        ++deg[U[i]],++deg[V[i]];
    }
    for(int i=1;i<=m;++i){
        int u=U[i],v=V[i];
        if(deg[u]>deg[v]||(deg[u]==deg[v]&&u>v)) swap(u,v);
        e[u].push_back(v);
    }
    for(int i=1;i<=n;++i){
        for(int j=0;j<(int)e[i].size();++j)
            tg[e[i][j]]=i;
        for(int j=0;j<(int)e[i].size();++j)
            for(int k=0;k<(int)e[e[i][j]].size();++k)
                if(tg[e[e[i][j]][k]]==i)
                    ans=(0ll+ans+1ll*x[i]*x[e[i][j]]%mod*x[e[e[i][j]][k]])%mod;
    }
    printf("%d\n",ans);
    return 0;
}