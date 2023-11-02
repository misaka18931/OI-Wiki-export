//μ's forever
#include <bits/stdc++.h>
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
char s[N];
int n,sz;
int rak[N],sa[N],tp[N],c[N];
void Rsort(){
    for(int i=0;i<=sz;++i) c[i]=0;
    for(int i=1;i<=n;++i) ++c[rak[i]];
    for(int i=1;i<=sz;++i) c[i]+=c[i-1];
    for(int i=n;i>=1;--i) sa[c[rak[tp[i]]]--]=tp[i];
}
void sa_build(){
    sz=127;
    for(int i=1;i<=n;++i)
        rak[i]=s[i],tp[i]=i;
    Rsort();
    for(int w=1,p=0;p<n;sz=p,w<<=1){
        p=0;
        for(int i=1;i<=w;++i)
            tp[++p]=n-w+i;
        for(int i=1;i<=n;++i)
            if(sa[i]>w)
                tp[++p]=sa[i]-w;
        Rsort();
        swap(tp,rak);
        rak[sa[1]]=p=1;
        for(int i=2;i<=n;++i)
            rak[sa[i]]=(tp[sa[i-1]]==tp[sa[i]]&&tp[sa[i-1]+w]==tp[sa[i]+w])?p:++p;
    }
}
int main()
{
    scanf("%s",s+1);
    n=strlen(s+1);
    sa_build();
    for(int i=1;i<=n;++i) printf("%d ",sa[i]);
    return 0;
}