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
char s[N];
int n,m,cnt,las,len[N],fail[N],ch[N][26],val[N];
int ans;
int make(int l){
    len[cnt]=l;
    return cnt++;
}
void init(){
    make(0),make(-1);
    fail[0]=1,fail[1]=0;
    s[0]=0;
}
int getf(int x){
    while(s[m]!=s[m-len[x]-1]) x=fail[x];
    return x;
}
void extend(int c){
    ++m;
    int f=getf(las);
    if(!ch[f][c]){
        int cur=make(len[f]+2);
        fail[cur]=ch[getf(fail[f])][c];
        ch[f][c]=cur;
    }
    las=ch[f][c];
    ans=max(ans,len[las]);
}
int main()
{
    scanf("%s",s+1);
    n=strlen(s+1);
    init();
    for(int i=1;i<=n;++i) extend(s[i]-'a');
    printf("%d\n",ans);
    return 0;
}