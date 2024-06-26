//μ's forever
#include <bits/stdc++.h>
#define ll long long 
#define N 500005
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
int n,m;
int fa[N];
int find(int x){
    return x==fa[x]?x:fa[x]=find(fa[x]);
}
struct edge{
    int u,v,w;
}e[N];
bool cmp(edge a,edge b){
    return a.w<b.w;
}
ll ans;
int main()
{
    n=read(),m=read();
    for(int i=1;i<=n;++i) fa[i]=i;
    for(int i=1;i<=m;++i){
        e[i].u=read(),e[i].v=read(),e[i].w=read();
    }
    sort(e+1,e+1+m,cmp);
    for(int i=1;i<=m;++i){
        int u=find(e[i].u),v=find(e[i].v);
        if(u!=v){
            ans+=e[i].w;
            fa[u]=v;
        }
    }
    printf("%lld\n",ans);
    return 0;
}