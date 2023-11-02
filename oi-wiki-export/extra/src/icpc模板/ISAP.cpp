//μ's forever
#include <bits/stdc++.h>
#define N 5005
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
struct edge{
    int to,nxt,w;
}e[N<<1];
int head[N],cnt=1;
void add(int u,int v,int w){
    e[++cnt]=(edge){v,head[u],w}; head[u]=cnt;
}
int n,m,s,t;
int cur[N],dep[N],gap[N];
ll mxfl=0;
queue<int> q;
void bfs(){
    for(int i=0;i<=n+5;++i) dep[i]=-1,gap[i]=0;
    dep[t]=0,gap[0]=1;
    q.push(t);
    while(!q.empty()){
        int u=q.front(); q.pop();
        for(int i=head[u];i;i=e[i].nxt){
            int v=e[i].to; if(dep[v]!=-1) continue;
            dep[v]=dep[u]+1; ++gap[dep[v]];
            q.push(v);
        }
    }
}
int dfs(int x,int fl){
    if(x==t){
        mxfl+=fl;
        return fl;
    }
    int usd=0;
    for(int i=cur[x];i;cur[x]=i=e[i].nxt){
        int v=e[i].to;
        if(e[i].w==0||dep[x]!=dep[v]+1) continue;
        int tmp=dfs(v,min(fl-usd,e[i].w));
        e[i].w-=tmp,e[i^1].w+=tmp;
        usd+=tmp;
        if(usd==fl) return fl;
    }
    --gap[dep[x]++]==0?dep[s]=n+1:++gap[dep[x]];
    return usd;
}
void ISAP(){
    bfs();
    while(dep[s]<=n){
        for(int i=1;i<=n;++i) cur[i]=head[i];
        dfs(s,1145141919);
    }
}
int main()
{
    n=read(),m=read(),s=read(),t=read();
    for(int i=1;i<=m;++i){
        int u=read(),v=read(),w=read();
        add(u,v,w);
        add(v,u,0);
    }
    ISAP();
    printf("%lld\n",mxfl);
    return 0;
}