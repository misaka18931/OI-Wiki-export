//μ's forever
#include <bits/stdc++.h>
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
struct edge{
    int to,nxt;
}e[N];
int head[N],cnt;
void add(int u,int v){
    e[++cnt]=(edge){v,head[u]}; head[u]=cnt;
}
int n,m;
int dfn[N],low[N],tim,sta[N],top,ins[N],scc;
vector<int> sc[N];
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
            ins[sta[top]]=0;
            sc[scc].push_back(sta[top]);
            --top;
        }while(sta[top+1]!=x);
    }
}
int main()
{
    n=read(),m=read();
    for(int i=1;i<=m;++i){
        int u=read()+1,v=read()+1;
        add(u,v);
    }
    for(int i=1;i<=n;++i)
        if(!dfn[i])
            tarjan(i);
    printf("%d\n",scc);
    for(int i=scc;i>=1;--i){
        int sz=sc[i].size();
        printf("%d ",sz);
        for(int j=0;j<sz;++j)
            printf("%d ",sc[i][j]-1);
        printf("\n");
    }
    return 0;
}