#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=5e5+10,M=1e6+10;
int n,m,ans[N],tot;
int fst[N][3],nxt[M+M+N],to[M+M+N];
int dfn[N],ord[N],cnt,fth[N];
int idom[N],semi[N],uni[N],mn[N];
inline ll read()
{
	ll s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
	return s*w;
}
inline void add(int u,int v,int id)
{
	nxt[++tot]=fst[u][id];
	to[tot]=v,fst[u][id]=tot;
}
inline void Tarjan(int u)
{
	ord[dfn[u]=++cnt]=u;
	for(int i=fst[u][0];i;i=nxt[i])
	{
		int v=to[i];
		if(!dfn[v])
		{
			fth[v]=u;
			Tarjan(v);
		}
	}
}
inline int uni_query(int u)
{
	if(u==uni[u])return u;
	int tmp=uni_query(uni[u]);
	if(dfn[semi[mn[u]]]>dfn[semi[mn[uni[u]]]])mn[u]=mn[uni[u]];
	return uni[u]=tmp;
}
inline void Lengauer_Tarjan(int s)
{
	Tarjan(s);
	for(int i=1;i<=n;++i)semi[i]=uni[i]=mn[i]=i;
	for(int id=cnt;id>=2;--id)
	{
		int u=ord[id];
		for(int i=fst[u][1];i;i=nxt[i])
		{
			int v=to[i];
			if(!dfn[v])continue;
			uni_query(v);
			if(dfn[semi[u]]>dfn[semi[mn[v]]])semi[u]=semi[mn[v]];
		}
		uni[u]=fth[u];
		add(semi[u],u,2);
		u=fth[u];
		for(int i=fst[u][2];i;i=nxt[i])
		{
			int v=to[i];
			uni_query(v);
			idom[v]=(u==semi[mn[v]]?u:mn[v]);
		}
		fst[u][2]=0;
	}
	for(int i=2;i<=cnt;++i)
	{
		int u=ord[i];
		if(idom[u]^semi[u])
		idom[u]=idom[idom[u]];
	}
}
int main()
{
	n=read(),m=read();
	for(int i=1;i<=m;++i)
	{
		int x=read(),y=read();
		add(x,y,0),add(y,x,1);
	}
	Lengauer_Tarjan(1);
	for(int i=cnt;i>=2;--i)ans[idom[ord[i]]]+=(++ans[ord[i]]);
	++ans[1];
	for(int i=1;i<=n;++i)printf("%d ",ans[i]);
	return 0;
}