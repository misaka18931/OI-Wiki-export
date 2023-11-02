//μ's forever
#include <bits/stdc++.h>
#define mod 998244353
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
inline void add(int &x,int y){
    x+=y;
    if(x>=mod) x-=mod;
}
inline void sub(int &x,int y){
    x-=y;
    if(x<0) x+=mod;
}
int n,m;
// int a[N],b[N],c[N];
void fwt_or(int *a,int f){
    for(int i=2,p=1;i<=m;i<<=1,p<<=1)
        for(int j=0;j<m;j+=i)
            for(int k=0;k<p;++k)
                if(f==1) add(a[j+p+k],a[j+k]);
                else sub(a[j+p+k],a[j+k]);
}
void fwt_and(int *a,int f){
    for(int i=2,p=1;i<=m;i<<=1,p<<=1)
        for(int j=0;j<m;j+=i)
            for(int k=0;k<p;++k)
                if(f==1) add(a[j+k],a[j+p+k]);
                else sub(a[j+k],a[j+p+k]);
}
void fwt_xor(int *a,int f){
    for(int i=2,p=1;i<=m;i<<=1,p<<=1)
        for(int j=0;j<m;j+=i)
            for(int k=0;k<p;++k){
                int x=a[j+k],y=a[j+p+k];
                a[j+k]=1ll*(x+y)*f%mod;
                a[j+p+k]=1ll*(x+mod-y)*f%mod;
            }
}
int a[20][N],b[20][N],c[20][N];
inline int p(int x){
    return __builtin_popcount(x);
}
int main()
{
    n=read(); m=1<<n;
    // for(int i=0;i<m;++i) a[i]=read();
    // for(int i=0;i<m;++i) b[i]=read();
    // fwt_or(a,1);
    // fwt_or(b,1);
    // for(int i=0;i<m;++i) c[i]=1ll*a[i]*b[i]%mod;
    // fwt_or(c,-1);
    // for(int i=0;i<m;++i)
    //     printf("%d ",c[i]);
    // fwt_and(a,1);
    // fwt_and(b,1);
    // for(int i=0;i<m;++i) c[i]=1ll*a[i]*b[i]%mod;
    // fwt_and(c,-1);
    // for(int i=0;i<m;++i)
    //     printf("%d ",c[i]);
    // fwt_xor(a,1);
    // fwt_xor(b,1);
    // for(int i=0;i<m;++i) c[i]=1ll*a[i]*b[i]%mod;
    // fwt_xor(c,(mod+1)>>1);
    // for(int i=0;i<m;++i)
    //     printf("%d ",c[i]);
    for(int i=0;i<m;++i) a[p(i)][i]=read();
    for(int i=0;i<m;++i) b[p(i)][i]=read();
    for(int i=0;i<=n;++i) fwt_or(a[i],1),fwt_or(b[i],1);
    for(int i=0;i<m;++i)
        for(int j=0;j<=n;++j)
            for(int k=0;k<=j;++k)
                c[j][i]=(0ll+c[j][i]+1ll*a[k][i]*b[j-k][i])%mod;
    for(int i=0;i<=n;++i) fwt_or(c[i],-1);
    for(int i=0;i<m;++i) printf("%d ",c[p(i)][i]);
    return 0;
}