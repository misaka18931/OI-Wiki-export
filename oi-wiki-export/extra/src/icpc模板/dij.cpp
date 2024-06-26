//μ's forever
#include <bits/stdc++.h>
#define N 10005
#define ll long long 
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
int n,m,s,t;
struct edge{
    int to,nxt,w;
}e[N<<1];
int head[N],cnt;
void add(int u,int v,int w){
    e[++cnt]=(edge){v,head[u],w}; head[u]=cnt;
}
priority_queue<pair<ll,int> > q;
ll dis[N];
void dij(){
    memset(dis,0x3f,sizeof(dis));
    dis[s]=0;
    q.push(make_pair(0,s));
    while(!q.empty()){
        pair<ll,int> tmp=q.top(); q.pop();
        if(tmp.first!=-dis[tmp.second]) continue;
        int u=tmp.second;
        for(int i=head[u];i;i=e[i].nxt){
            int v=e[i].to;
            if(dis[v]>dis[u]+e[i].w){
                dis[v]=dis[u]+e[i].w;
                q.push(make_pair(-dis[v],v));
            }
        }
    }
}
int main()
{
    n=read(),m=read(),s=read(),t=read();
    for(int i=1;i<=m;++i){
        int u=read(),v=read(),w=read();
        add(u,v,w);
        add(v,u,w);
    }
    dij();
    printf("%lld\n",dis[t]);
    return 0;
}