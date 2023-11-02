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
char s[N];
int n,z[N];
int main()
{
    scanf("%s",s+1);
    n=strlen(s+1);
    z[1]=0; // z[1]==n;
    for(int i=2,l=0,r=0;i<=n;++i){
        if(i<=r) z[i]=min(z[i-l+1],r-i+1);
        while(s[z[i]+1]==s[z[i]+i]) ++z[i];
        if(i+z[i]-1>r) l=i,r=i+z[i]-1;
    }
    for(int i=1;i<=n;++i) printf("%d ",z[i]);
    return 0;
}