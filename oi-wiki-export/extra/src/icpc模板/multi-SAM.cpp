//μ's forever
#include <bits/stdc++.h>
#define ll long long
#define N 1000005
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
char s[N];
int las,cnt,ch[N<<1][26],fa[N<<1],len[N<<1],val[N<<1];
void insert(int c){
    int p=las;
    las=++cnt;
    len[las]=len[p]+1;
    val[las]=1;
    for(;p&&ch[p][c]==0;p=fa[p]) ch[p][c]=las;
    if(p==0) fa[las]=1;
    else{
        int q=ch[p][c];
        if(len[q]==len[p]+1) fa[las]=q;
        else{
            ++cnt;
            len[cnt]=len[p]+1;
            fa[cnt]=fa[q];
            for(int i=0;i<26;++i) ch[cnt][i]=ch[q][i];
            fa[q]=fa[las]=cnt;
            for(;p&&ch[p][c]==q;p=fa[p]) ch[p][c]=cnt;
        }
    }
}
int main()
{
    scanf("%d",&n);
    cnt=1;
    for(int i=1;i<=n;++i){
        las=1;
        scanf("%s",s+1);
        m=strlen(s+1);
        for(int j=1;j<=m;++j)
            insert(s[j]-'a');
    }
    ll ans=0;
    for(int i=1;i<=cnt;++i)
        ans+=len[i]-len[fa[i]];
    printf("%lld\n",ans);
    return 0;
}