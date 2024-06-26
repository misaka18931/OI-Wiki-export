//μ's forever
#include <bits/stdc++.h>
#define db double
#define N 2000005
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
int n;
struct Point{
    db x,y;
    Point(){}
    Point(db _x,db _y){
        x=_x,y=_y;
    }
}P[N];
Point operator - (Point u,Point v){
    return Point(u.x-v.x,u.y-v.y);
}
db len(Point u){
    return sqrt(u.x*u.x+u.y*u.y);
}
bool cmpx(Point u,Point v){
    if(u.x!=v.x) return u.x<v.x;
    return u.y<v.y;
}
bool cmpy(int u,int v){
    return P[u].y<P[v].y;
}
int b[N];
db solve(int l,int r){
    if(r-l<=16){
        db d=1e18;
        for(int i=l;i<=r;++i)
            for(int j=l;j<i;++j)
                d=min(d,len(P[i]-P[j]));
        return d;
    }
    int mid=l+r>>1;
    db d=min(solve(l,mid),solve(mid+1,r));
    while(P[mid].x-P[l].x>=d && l<=mid) ++l;
    while(P[r].x-P[mid].x>=d && r>mid) --r;
    for(int i=l;i<=r;++i) b[i]=i;
    sort(b+l,b+mid+1,cmpy);
    sort(b+mid+1,b+r+1,cmpy);
    int s=mid+1;
    for(int i=l;i<=mid;++i){
        while(P[b[i]].y-P[b[s]].y>=d && s<=r) ++s;
        int t=s;
        while(P[b[i]].y-P[b[t]].y>=-d && t<=r){
            d=min(d,len(P[b[i]]-P[b[t]]));
            ++t;
        }
    }
    return d;
}
int main()
{
    n=read();
    for(int i=1;i<=n;++i) P[i].x=read(),P[i].y=read();
    sort(P+1,P+1+n,cmpx);
    printf("%.9lf\n",solve(1,n));
    return 0;
}