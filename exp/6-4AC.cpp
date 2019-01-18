#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
 
 
using namespace std;
 
const int INF=100000000;
const int maxn=1005;
//spfa Ä£°æ
struct node
{
    int v,w,next;
}edge[20005];
int head[maxn],dis[maxn],cnt[maxn];
bool vis[maxn];
int num,n,m1,m2;
void init()
{
    for(int i=1;i<=n;i++)
    head[i]=-1;
    num=0;
}
void add(int u,int v,int w)
{
    edge[num].v=v;
    edge[num].w=w;
    edge[num].next=head[u];
    head[u]=num++;
}
int spfa()
{
    queue<int>Q;
    for(int i=1;i<=n;i++)
    dis[i]=INF;

    dis[1]=0;
    memset(vis,false,sizeof(vis));
    memset(cnt,0,sizeof(cnt));
    vis[1]=true;
    Q.push(1);
    cnt[1]++;
    while(!Q.empty())
    {
        int x=Q.front();
        Q.pop();
        vis[x]=false;
        for(int i=head[x];i!=-1;i=edge[i].next)
        {
            if(dis[edge[i].v]>dis[x]+edge[i].w)
            {
                dis[edge[i].v]=dis[x]+edge[i].w;
                if(!vis[edge[i].v])
                {
                    vis[edge[i].v]=true;
                    if(++cnt[edge[i].v]>n) return -1;//no sol
                    Q.push(edge[i].v);
                }
            }
        }
    }
    if(dis[n]==INF) return -2;// unreach
    return dis[n];
}
int main()
{
    int a,b,c;
    while(scanf("%d%d%d",&n,&m1,&m2)!=EOF)
    {
        init();
        //built graph
        while(m1--)
        {
            scanf("%d%d%d",&a,&b,&c);
            add(a,b,c);
        }
        while(m2--)
        {
            scanf("%d%d%d",&a,&b,&c);
            add(b,a,-c);
        }
        //ouput
        printf("%d\n",spfa());
    }
    return 0;
}
