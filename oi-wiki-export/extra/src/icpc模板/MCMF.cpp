//μ's forever
#include <bits/stdc++.h>
#define N 100005
#define getchar nc
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
    int to,nxt,w,c;
}e[N];
int head[N],cnt=1;
void add(int u,int v,int w,int c){
    e[++cnt]=(edge){v,head[u],w,c}; head[u]=cnt;
}
int n,m,s,t;
int mxfl,cst;
int dis[N],vis[N];
queue<int> q;
bool bfs(){
    for(int i=1;i<=n;++i) dis[i]=2147483647;
    dis[s]=0;
    q.push(s);
    while(!q.empty()){
        int u=q.front(); q.pop();
        for(int i=head[u];i;i=e[i].nxt){
            int v=e[i].to;
            if(e[i].w&&dis[u]+e[i].c<dis[v]){
                dis[v]=dis[u]+e[i].c;
                q.push(v);
            }
        }
    }
    return dis[t]!=2147483647;
}
int dfs(int u,int fl){
    vis[u]=1;
    if(u==t) return fl;
    int usd=0;
    for(int i=head[u];i&&usd!=fl;i=e[i].nxt){
        int v=e[i].to;
        if(e[i].w&&dis[v]==dis[u]+e[i].c&&(vis[v]==0||v==t)){
            int tmp=dfs(v,min(e[i].w,fl-usd));
            if(tmp==0) dis[v]=-1145141919;
            e[i].w-=tmp;
            e[i^1].w+=tmp;
            cst+=tmp*e[i].c;
            usd+=tmp;
        }
    }
    return usd;
}
int main()
{
    n=read(),m=read(),s=read(),t=read();
    for(int i=1;i<=m;++i){
        int u=read(),v=read(),w=read(),c=read();
        add(u,v,w,c);
        add(v,u,0,-c);
    }
    while(bfs()){
        vis[t]=1;
        while(vis[t]){
            for(int i=1;i<=n;++i) vis[i]=0;
            mxfl+=dfs(s,2147483647);
        }
    }
    printf("%d %d\n",mxfl,cst);
    return 0;
}
