#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;
const int o=4e5+10;
int n,m,ed[o],L[o],b[o];long long c[o],ans[o];char s[o];vector<int> vec[o];
struct SAM{
	int len[o],ch[o][26],lk[o],cnt,lst;
	inline void init(){lk[0]=-1;}
	inline void ins(char c){
		int cur=++cnt,p=lst,q,cln;
		for(len[cur]=len[lst]+1,c-=97,lst=cur;p+1&&!ch[p][c];p=lk[p]) ch[p][c]=cur;
		if(p==-1){lk[cur]=0;return;}
		if(len[p]+1==len[q=ch[p][c]]){lk[cur]=q;return;}
		len[cln=++cnt]=len[p]+1;
		for(int i=0;i<26;++i) ch[cln][i]=ch[q][i];
		for(lk[cln]=lk[q],lk[cur]=lk[q]=cln;p+1&&ch[p][c]==q;p=lk[p]) ch[p][c]=cln;
	}
}sam;
inline int lowbit(int x){return x&-x;}
void modify(int l,int r,int val){
	for(int i=l;i<=n;i+=lowbit(i)) b[i]+=val,c[i]+=val*1ll*l;
	for(int i=r+1;i<=n;i+=lowbit(i)) b[i]-=val,c[i]-=val*(r+1ll);
}
long long query(int l,int r){
	long long res=0;
	for(int i=r;i;i-=lowbit(i)) res+=(r+1ll)*b[i]-c[i];
	for(int i=l-1;i;i-=lowbit(i)) res-=l*1ll*b[i]-c[i];
	return res;
}
struct linkcuttree{
	int f[o],l[o],r[o],v[o],flg[o];
	inline bool isroot(int x){return x-l[f[x]]&&x-r[f[x]];}
	inline bool rel(int x){return x^l[f[x]];}
	inline void assign(int id,int val){if(id) v[id]=flg[id]=val;}
	inline void pushdown(int x){if(flg[x]) assign(l[x],flg[x]),assign(r[x],flg[x]),flg[x]=0;}
	inline void rotate(int x){
		int y=f[x],z=f[y];
		pushdown(z);pushdown(y);
		if(!isroot(y)) if(rel(y)) r[z]=x;else l[z]=x;
		if(rel(x)) f[r[y]=l[x]]=y,f[l[x]=y]=x;
		else f[l[y]=r[x]]=y,f[r[x]=y]=x;
		f[x]=z;
	}
	inline void splay(int x){
		for(int y;!isroot(x);rotate(x)) if(!isroot(y=f[x])) rotate((rel(x)^rel(y))?x:y);
		pushdown(x);
	}
	inline void access(int x,int val){
		int y=0;
		for(;x;r[x]=y,y=x,x=f[x]){
			splay(x);
			if(v[x]) modify(v[x]-sam.len[x-1]+1,f[x]?v[x]-(sam.len[f[x]-1]+1)+1:v[x],-1);
		}
		assign(y,val);modify(1,val,1);
	}
}lct;
int main(){
	scanf("%s%d",s+1,&m);n=strlen(s+1);sam.init();
	for(int i=1;i<=n;++i) sam.ins(s[i]),ed[i]=sam.lst;
	for(int i=1;i<=sam.cnt;++i) lct.f[i+1]=sam.lk[i]+1;
	for(int i=1,r;i<=m;++i) scanf("%d%d",&L[i],&r),vec[r].push_back(i);
	for(int i=1;i<=n;++i){
		lct.access(ed[i]+1,i);
		for(int j=vec[i].size();j--;) ans[vec[i][j]]=query(L[vec[i][j]],i);
	}
	for(int i=1;i<=m;++i) printf("%lld\n",ans[i]);
	return 0;
}