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
}e[N<<1];
int head[N],cnt;
void add(int u,int v){
    e[++cnt]=(edge){v,head[u]}; head[u]=cnt;
}
int n,m;
vector<int> ans;
int dfn[N],low[N],tim;
void tarjan(int x,int f){
    dfn[x]=low[x]=++tim;
    int tot=0;
    for(int i=head[x];i;i=e[i].nxt){
        int v=e[i].to;
        if(v==f) continue;
        if(!dfn[v]){
            tarjan(v,x);
            low[x]=min(low[x],low[v]);
            if(low[v]>=dfn[x]) ++tot;
        }else   
            low[x]=min(low[x],dfn[v]);
    }
    if(f==0){
        if(tot>=2) ans.push_back(x);
    }else{
        if(tot>=1) ans.push_back(x);
    }
}
int main()
{
    n=read(),m=read();
    for(int i=1;i<=m;++i){
        int u=read(),v=read();
        add(u,v),add(v,u);
    }
    for(int i=1;i<=n;++i)
        if(!dfn[i])
            tarjan(i,0);
    sort(ans.begin(),ans.end());
    int sz=ans.size();
    printf("%d\n",sz);
    for(int i=0;i<sz;++i) printf("%d ",ans[i]);
    return 0;
}