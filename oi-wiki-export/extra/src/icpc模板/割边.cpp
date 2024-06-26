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
int head[N],cnt=1;
void add(int u,int v){
    e[++cnt]=(edge){v,head[u]},head[u]=cnt;
}
int n,m,s[N*5],t[N*5];
int dfn[N],low[N],tim,bl[N],col,sta[N],top;
void tarjan(int x,int id){
    dfn[x]=low[x]=++tim;
    sta[++top]=x;
    for(int i=head[x];i;i=e[i].nxt){
        int v=e[i].to;
        if(i==(id^1)) continue;
        if(!dfn[v]){
            tarjan(v,i);
            low[x]=min(low[x],low[v]);
        }else
            low[x]=min(low[x],dfn[v]);
    }
    if(dfn[x]==low[x]){
        ++col;
        do{
            bl[sta[top]]=col;
            --top;
        }while(sta[top+1]!=x);
    }
}
int main()
{
    n=read(),m=read();
    for(int i=1;i<=m;++i){
        s[i]=read(),t[i]=read();
        add(s[i],t[i]),add(t[i],s[i]);
    }
    for(int i=1;i<=n;++i)
        if(!dfn[i])
            tarjan(i,0);
    for(int i=1;i<=m;++i)
        if(bl[s[i]]!=bl[t[i]])
            printf("%d %d\n",s[i],t[i]);
    return 0;
}