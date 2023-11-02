//μ's forever
#include <bits/stdc++.h>
#define N 100005
#define db double
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
struct point{
    db x,y;
    point(){}
    point(db _x,db _y){
        x=_x,y=_y;
    }
    point operator - (const point &b) const{
        return point(x-b.x,y-b.y);
    }
}p[N];
bool cmp(point a,point b){
    return a.x<b.x;
}
db cross(point a,point b){
    return a.x*b.y-a.y*b.x;
}
db dis(point a,point b){
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}
int sta[N],top;
int main()
{
    n=read();
    for(int i=1;i<=n;++i){
        p[i].x=read(),p[i].y=read();
    }
    sort(p+1,p+1+n,cmp);
    top=0;
    for(int i=1;i<=n;++i){
        while(top>=2&&cross(p[i]-p[sta[top-1]],p[i]-p[sta[top]])<=0) --top;
        sta[++top]=i;
    }
    int val=top;
    for(int i=n;i>=1;--i){
        while(top-val>=1&&cross(p[i]-p[sta[top-1]],p[i]-p[sta[top]])<=0) --top;
        sta[++top]=i;
    }
    db ans=0;
    for(int i=1;i<top;++i) ans+=dis(p[sta[i]],p[sta[i+1]]);
    printf("%.8lf\n",ans);
    return 0;
}