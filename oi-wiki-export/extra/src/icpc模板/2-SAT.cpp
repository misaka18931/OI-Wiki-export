//μ's forever
#include <bits/stdc++.h>
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
struct edge{
    int to,nxt;
}e[N*10];
int head[N<<1],cnt;
void add(int u,int v){
    e[++cnt]=(edge){v,head[u]}; head[u]=cnt;
}
int n,m;
int dfn[N<<1],low[N<<1],tim,ins[N<<1],sta[N<<1],top,bl[N<<1],scc;
void tarjan(int x){
    dfn[x]=low[x]=++tim;
    sta[++top]=x,ins[x]=1;
    for(int i=head[x];i;i=e[i].nxt){
        int v=e[i].to;
        if(!dfn[v]){
            tarjan(v);
            low[x]=min(low[x],low[v]);
        }else if(ins[v])
            low[x]=min(low[x],dfn[v]);
    }
    if(low[x]==dfn[x]){
        ++scc;
        do{
            bl[sta[top]]=scc;
            ins[sta[top]]=0;
            --top;
        }while(sta[top+1]!=x);
    }
}
vector<int> ev[N<<1];
int indeg[N<<1],id[N<<1],idc;
int main()
{
    n=read(),m=read();
    for(int i=1;i<=m;++i){
        int a=read()-1,b=read(),c=read()-1,d=read();
        add(a*2+(b^1),c*2+d);
        add(c*2+(d^1),a*2+b);
    }
    for(int i=0;i<n*2;++i)
        if(!dfn[i])
            tarjan(i);
    for(int i=0;i<n;++i)
        if(bl[i*2]==bl[i*2+1]){
            puts("No");
            return 0;
        }
    for(int x=0;x<n*2;++x){
        for(int i=head[x];i;i=e[i].nxt){
            int v=e[i].to;
            if(bl[x]!=bl[v]){
                ev[bl[v]].push_back(bl[x]);
                ++indeg[bl[x]];
            }
        }
    }
    queue<int> q;
    for(int i=1;i<=scc;++i)
        if(indeg[i]==0)
            q.push(i);
    while(!q.empty()){
        int u=q.front(); q.pop();
        id[u]=++idc;
        for(int i=0;i<(int)ev[u].size();++i)
            if(--indeg[ev[u][i]]==0)
                q.push(ev[u][i]);
    }
    puts("Yes");
    for(int i=0;i<n;++i)
        printf("%d ",id[bl[i*2]]>id[bl[i*2+1]]);
    return 0;
}