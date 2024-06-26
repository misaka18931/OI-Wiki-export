#include<bits/stdc++.h>
#define db double
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
int ans;
int n,m;
int vis[N];
int match[N];
clock_t st ;
mt19937 g_f ;
vector<int> E[N];
void add(int u,int v){
    E[u].push_back(v);
    E[v].push_back(u);
}
inline db now_time(){
    return (double)(clock() - st) / CLOCKS_PER_SEC ;
}
int do_match(int x, mt19937 g_f){
    shuffle(E[x].begin(), E[x].end(), g_f) ; vis[x] = 1 ;
    for (auto y : E[x])
        if (!match[y])
            return vis[y] = 1, match[y] = x, match[x] = y, 1 ;
    for (auto y : E[x]){
        int z = match[y] ;
        if (vis[z]) continue ;
        match[x] = y, match[y] = x, match[z] = 0 ;
        if (do_match(z, g_f)) return 1 ;
        match[y] = z, match[z] = y, match[x] = 0 ;
    }
    return 0 ;
}
int main(){
    random_device seed ;
    mt19937 g_f(seed()) ;
    n=read(),m=read(); int x, y, z ;
    for (int i = 1 ; i <= m ; ++ i)
        x = read()+1, y = read()+1, add(x, y) ; st = clock() ;
    while (now_time() < 0.85){
        for (int i = 1 ; i <= n ; ++ i)
            if (!match[i])
                fill(vis + 1, vis + n + 1, 0), ans += do_match(i, g_f);
    }
    printf("%d\n",ans);
    // for(int i=1;i<=n;++i)
    //     printf("%d ",match[i]);
    for(int i=1;i<=n;++i)
        if(match[i]>i)
            printf("%d %d\n",i,match[i]);
    return 0;
}