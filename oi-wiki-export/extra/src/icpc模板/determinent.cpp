//μ's forever
#include <bits/stdc++.h>
#define mod 998244353
#define N 505
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
int power(int a,int b){
    int res=1;
    while(b){
        if(b&1) res=1ll*res*a%mod;
        a=1ll*a*a%mod,b>>=1;
    }
    return res;
}
int n,a[N][N];
int ans=1;
int main()
{
    n=read();
    for(int i=1;i<=n;++i)
        for(int j=1;j<=n;++j)
            a[i][j]=read();
    for(int i=1;i<=n;++i){
        if(a[i][i]==0){
            int cnt=0;
            for(int j=i+1;j<=n;++j)
                if(a[j][i]!=0){
                    cnt=j;
                    break;
                }
            if(cnt==0){
                puts("0");
                return 0;
            }
            swap(a[i],a[cnt]);
            ans=(mod-ans)%mod;
        }
        int inv=power(a[i][i],mod-2);
        for(int j=i+1;j<=n;++j){
            int mul=1ll*inv*a[j][i]%mod;
            for(int k=i;k<=n;++k){
                a[j][k]=(0ll+a[j][k]-1ll*mul*a[i][k]%mod+mod)%mod;
            }
        }
        ans=1ll*ans*a[i][i]%mod;
    }
    printf("%d\n",ans);
    return 0;
}