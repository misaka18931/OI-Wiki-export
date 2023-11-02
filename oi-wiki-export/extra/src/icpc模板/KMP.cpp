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
int n,nxt[N];
int main()
{
    scanf("%s",s+1);
    n=strlen(s+1);
    nxt[1]=0;
    int p=0;
    for(int i=2;i<=n;++i){
        while(p&&s[p+1]!=s[i]) p=nxt[p];
        if(s[p+1]==s[i]) ++p;
        nxt[i]=p;
    }
    for(int i=1;i<=n;++i) printf("%d ",nxt[i]);
    return 0;
}